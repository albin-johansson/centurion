#ifndef CENTURION_TEXTURE_HEADER
#define CENTURION_TEXTURE_HEADER

#include <SDL.h>

#include "../compiler/features.hpp"

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#include <cassert>  // assert
#include <ostream>  // ostream
#include <string>   // string, to_string

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/not_null.hpp"
#include "../core/owner.hpp"
#include "../core/result.hpp"
#include "../core/str.hpp"
#include "../detail/address_of.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../math/area.hpp"
#include "../math/point.hpp"
#include "blend_mode.hpp"
#include "color.hpp"
#include "pixel_format_info.hpp"
#include "scale_mode.hpp"
#include "surface.hpp"
#include "texture_access.hpp"

namespace cen {

/// \addtogroup video
/// \{

template <typename T>
class basic_texture;

using texture = basic_texture<detail::owning_type>;
using texture_handle = basic_texture<detail::handle_type>;

/**
 * \class basic_texture
 *
 * \brief Represents an hardware-accelerated image, intended to be rendered using the
 * `basic_renderer` class.
 *
 * \ownerhandle `texture`/`texture_handle`
 *
 * \since 3.0.0
 *
 * \see `texture`
 * \see `texture_handle`
 */
template <typename T>
class basic_texture final
{
 public:
  /// \name Construction
  /// \{

  // clang-format off

  /**
   * \brief Creates an texture from a pre-existing SDL texture.
   *
   * \param source a pointer to the associated SDL texture.
   *
   * \throws cen_error if the supplied pointer is null *and* the texture is owning.
   *
   * \since 3.0.0
   */
  explicit basic_texture(maybe_owner<SDL_Texture*> source) noexcept(!detail::is_owning<T>())
      : m_texture{source}
  {
    if constexpr (detail::is_owning<T>())
    {
      if (!m_texture)
      {
        throw cen_error{"Cannot create texture from null pointer!"};
      }
    }
  }

  // clang-format on

  /**
   * \brief Creates a handle to texture instance.
   *
   * \param owner the associated owning texture.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit basic_texture(texture& owner) noexcept : m_texture{owner.get()}
  {}

#ifndef CENTURION_NO_SDL_IMAGE

  /**
   * \brief Creates a texture based the image at the specified path.
   *
   * \tparam Renderer the type of the renderer, e.g. `renderer` or `renderer_handle`.
   *
   * \param renderer the renderer that will be used to create the texture.
   * \param path the file path of the texture, can't be null.
   *
   * \throws img_error if the texture cannot be loaded.
   *
   * \since 4.0.0
   */
  template <typename Renderer, typename TT = T, detail::is_owner<TT> = 0>
  basic_texture(const Renderer& renderer, const not_null<str> path)
      : m_texture{IMG_LoadTexture(renderer.get(), path)}
  {
    if (!m_texture) {
      throw img_error{};
    }
  }

  /**
   * \brief Creates a texture based the image at the specified path.
   *
   * \tparam Renderer the type of the renderer, e.g. `renderer` or `renderer_handle`.
   *
   * \param renderer the renderer that will be used to create the texture.
   * \param path the file path of the texture.
   *
   * \throws img_error if the texture cannot be loaded.
   *
   * \since 5.3.0
   */
  template <typename Renderer, typename TT = T, detail::is_owner<TT> = 0>
  basic_texture(const Renderer& renderer, const std::string& path)
      : basic_texture{renderer, path.c_str()}
  {}

#endif  // CENTURION_NO_SDL_IMAGE

  /**
   * \brief Creates an texture that is a copy of the supplied surface.
   *
   * \tparam Renderer the type of the renderer, e.g. `renderer` or `renderer_handle`.
   *
   * \param renderer the renderer that will be used to create the texture.
   * \param surface the surface that the texture will be based on.
   *
   * \throws sdl_error if the texture cannot be loaded.
   *
   * \since 4.0.0
   */
  template <typename Renderer, typename TT = T, detail::is_owner<TT> = 0>
  basic_texture(const Renderer& renderer, const surface& surface)
      : m_texture{SDL_CreateTextureFromSurface(renderer.get(), surface.get())}
  {
    if (!m_texture) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates an texture with the specified characteristics.
   *
   * \tparam Renderer the type of the renderer, e.g. `renderer` or `renderer_handle`.
   *
   * \param renderer the associated renderer instance.
   * \param format the pixel format of the created texture.
   * \param access the access of the created texture.
   * \param size the size of the texture.
   *
   * \throws sdl_error if the texture cannot be created.
   *
   * \since 4.0.0
   */
  template <typename Renderer, typename TT = T, detail::is_owner<TT> = 0>
  basic_texture(const Renderer& renderer,
                const pixel_format format,
                const texture_access access,
                const iarea size)
      : m_texture{SDL_CreateTexture(renderer.get(),
                                    to_underlying(format),
                                    to_underlying(access),
                                    size.width,
                                    size.height)}
  {
    if (!m_texture) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates and returns a texture with streaming access.
   *
   * \details The created texture is based on the image at the specified path with the
   * `streaming` texture access.
   *
   * \tparam Renderer the type of the renderer, e.g. `renderer` or `renderer_handle`.
   *
   * \param renderer the renderer that will be used to create the texture.
   * \param path the path of the image file to base the texture on, can't be null.
   * \param format the pixel format that will be used by the texture.
   *
   * \throws cen_error if something goes wrong.
   *
   * \return a texture with `streaming` texture access.
   *
   * \since 4.0.0
   */
  template <typename Renderer, typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] static auto streaming(const Renderer& renderer,
                                      const not_null<str> path,
                                      const pixel_format format) -> basic_texture
  {
    assert(path);

    constexpr auto blendMode = blend_mode::blend;
    const auto surface = cen::surface::with_format(path, blendMode, format);

    basic_texture texture{renderer, format, texture_access::streaming, surface.size()};
    texture.set_blend_mode(blendMode);

    u32* pixels{};
    if (!texture.lock(&pixels)) {
      throw sdl_error{};
    }

    const auto maxCount =
        static_cast<usize>(surface.pitch()) * static_cast<usize>(surface.height());
    SDL_memcpy(pixels, surface.pixels(), maxCount);

    texture.unlock();

    return texture;
  }

  /**
   * \see streaming()
   * \since 5.3.0
   */
  template <typename Renderer, typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] static auto streaming(const Renderer& renderer,
                                      const std::string& path,
                                      const pixel_format format) -> basic_texture
  {
    return streaming(renderer, path.c_str(), format);
  }

  /// \} End of construction

  /// \name Setters
  /// \{

  /**
   * \brief Sets the color of the pixel at the specified coordinate.
   *
   * \details This function has no effect if the texture access isn't `streaming` or if
   * the coordinate is out-of-bounds.
   *
   * \param pixel the pixel that will be changed.
   * \param color the new color of the pixel.
   *
   * \since 4.0.0
   */
  void set_pixel(const ipoint pixel, const color& color)
  {
    if (access() != texture_access::streaming || (pixel.x() < 0) || (pixel.y() < 0) ||
        (pixel.x() >= width()) || (pixel.y() >= height()))
    {
      return;
    }

    u32* pixels{};
    int pitch{};
    if (!lock(&pixels, &pitch)) {
      return;
    }

    const int nPixels = (pitch / 4) * height();
    const int index = (pixel.y() * width()) + pixel.x();

    if ((index >= 0) && (index < nPixels)) {
      const pixel_format_info info{format()};
      pixels[index] = info.rgba_to_pixel(color);
    }

    unlock();
  }

  /**
   * \brief Sets the alpha value of the texture.
   *
   * \param alpha the alpha value, in the range [0, 255].
   *
   * \since 3.0.0
   */
  void set_alpha(const u8 alpha) noexcept
  {
    SDL_SetTextureAlphaMod(m_texture, alpha);
  }

  /**
   * \brief Sets the blend mode that will be used by the texture.
   *
   * \param mode the blend mode that will be used.
   *
   * \since 3.0.0
   */
  void set_blend_mode(const blend_mode mode) noexcept
  {
    SDL_SetTextureBlendMode(m_texture, static_cast<SDL_BlendMode>(mode));
  }

  /**
   * \brief Sets the color modulation of the texture.
   *
   * \note The alpha component in the color struct is ignored by this function.
   *
   * \param color the color that will be used to modulate the color of the texture.
   *
   * \since 3.0.0
   */
  void set_color_mod(const color& color) noexcept
  {
    SDL_SetTextureColorMod(m_texture, color.red(), color.green(), color.blue());
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Sets the scale mode that will be used by the texture.
   *
   * \param mode the scale mode that will be used.
   *
   * \since 4.0.0
   */
  void set_scale_mode(const scale_mode mode) noexcept
  {
    SDL_SetTextureScaleMode(m_texture, static_cast<SDL_ScaleMode>(mode));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /// \} End of setters

  /// \name Getters
  /// \{

  /**
   * \brief Returns the pixel format that is used by the texture.
   *
   * \return the pixel format that is used by the texture.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    u32 format{};
    SDL_QueryTexture(m_texture, &format, nullptr, nullptr, nullptr);
    return static_cast<pixel_format>(format);
  }

  /**
   * \brief Returns the texture access of the texture.
   *
   * \return the texture access of the texture.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto access() const noexcept -> texture_access
  {
    int access{};
    SDL_QueryTexture(m_texture, nullptr, &access, nullptr, nullptr);
    return static_cast<texture_access>(access);
  }

  /**
   * \brief Returns the width of the texture.
   *
   * \return the width of the texture.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    const auto [width, height] = size();
    return width;
  }

  /**
   * \brief Returns the height of the texture.
   *
   * \return the height of the texture.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    const auto [width, height] = size();
    return height;
  }

  /**
   * \brief Returns the size of the texture.
   *
   * \return the size of the texture.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto size() const noexcept -> iarea
  {
    int width{};
    int height{};
    SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);
    return {width, height};
  }

  /**
   * \brief Indicates whether or not the texture is a possible render target.
   *
   * \return `true` if the texture is a possible render target; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_target() const noexcept -> bool
  {
    return access() == texture_access::target;
  }

  /**
   * \brief Indicates whether or not the texture has static texture access.
   *
   * \return `true` if the texture has static texture access; `false` otherwise.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto is_no_lock() const noexcept -> bool
  {
    return access() == texture_access::no_lock;
  }

  /**
   * \brief Indicates whether or not the texture has streaming texture access.
   *
   * \return `true` if the texture has streaming texture access; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_streaming() const noexcept -> bool
  {
    return access() == texture_access::streaming;
  }

  /**
   * \brief Returns the alpha value of the texture.
   *
   * \return the alpha value of the texture.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto alpha() const noexcept -> u8
  {
    u8 alpha{};
    SDL_GetTextureAlphaMod(m_texture, &alpha);
    return alpha;
  }

  /**
   * \brief Returns the blend mode of the texture.
   *
   * \return the blend mode of the texture.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode
  {
    SDL_BlendMode mode{};
    SDL_GetTextureBlendMode(m_texture, &mode);
    return static_cast<blend_mode>(mode);
  }

  /**
   * \brief Returns the color modulation of the texture.
   *
   * \return the modulation of the texture.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto color_mod() const noexcept -> color
  {
    u8 red{};
    u8 green{};
    u8 blue{};
    SDL_GetTextureColorMod(m_texture, &red, &green, &blue);
    return {red, green, blue, 0xFF};
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Returns the scale mode that is used by the texture.
   *
   * \return the scale mode that is used by the texture.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get_scale_mode() const noexcept -> scale_mode
  {
    SDL_ScaleMode mode{};
    SDL_GetTextureScaleMode(m_texture, &mode);
    return static_cast<scale_mode>(mode);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Releases ownership of the associated SDL texture and returns a pointer to it.
   *
   * \warning Usage of this function should be considered dangerous, since you might run
   * into memory leak issues. You **must** call `SDL_DestroyTexture` on the returned
   * pointer to free the associated memory.
   *
   * \return a pointer to the associated SDL texture.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] auto release() noexcept -> owner<SDL_Texture*>
  {
    return m_texture.release();
  }

  /**
   * \brief Returns a pointer to the associated `SDL_Texture`.
   *
   * \return a pointer to the associated `SDL_Texture`.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Texture*
  {
    return m_texture.get();
  }

  /// \} End of getters

  /// \name Conversions
  /// \{

  /**
   * \brief Indicates whether or not a texture handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return m_texture != nullptr;
  }

  /**
   * \brief Converts to `SDL_Texture*`.
   *
   * \return a pointer to the associated `SDL_Texture`.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator SDL_Texture*() noexcept
  {
    return m_texture;
  }

  /**
   * \brief Converts to `const SDL_Texture*`.
   *
   * \return a pointer to the associated `SDL_Texture`.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator const SDL_Texture*() const noexcept
  {
    return m_texture;
  }

  /// \} End of conversions

 private:
  struct deleter final
  {
    void operator()(SDL_Texture* texture) noexcept
    {
      SDL_DestroyTexture(texture);
    }
  };
  detail::pointer_manager<T, SDL_Texture, deleter> m_texture;

  /**
   * \brief Locks the texture for write-only pixel access.
   *
   * \remarks This function is only applicable if the texture access of the texture is
   * `Streaming`.
   *
   * \param pixels this will be filled with a pointer to the locked pixels.
   * \param pitch This is filled in with the pitch of the locked pixels, can safely be
   * null if it isn't needed.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 4.0.0
   */
  auto lock(u32** pixels, int* pitch = nullptr) noexcept -> result
  {
    if (pitch) {
      return SDL_LockTexture(m_texture, nullptr, reinterpret_cast<void**>(pixels), pitch) == 0;
    }
    else {
      int dummyPitch;
      return SDL_LockTexture(m_texture,
                             nullptr,
                             reinterpret_cast<void**>(pixels),
                             &dummyPitch) == 0;
    }
  }

  /**
   * \brief Unlocks the texture.
   *
   * \since 4.0.0
   */
  void unlock() noexcept
  {
    SDL_UnlockTexture(m_texture);
  }
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a texture.
 *
 * \param texture the texture that will be converted.
 *
 * \return a string that represents the texture.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_texture<T>& texture) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("texture{{data: {}, width: {}, height: {}}}",
                     detail::address_of(texture.get()),
                     texture.width(),
                     texture.height());
#else
  return "texture{data: " + detail::address_of(texture.get()) +
         ", width: " + std::to_string(texture.width()) +
         ", height: " + std::to_string(texture.height()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a texture.
 *
 * \param stream the stream that will be used.
 * \param texture the texture that will be printed
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_texture<T>& texture) -> std::ostream&
{
  return stream << to_string(texture);
}

/// \} End of streaming

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_TEXTURE_HEADER