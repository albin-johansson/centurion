#ifndef CENTURION_TEXTURE_HPP_
#define CENTURION_TEXTURE_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#include <cassert>      // assert
#include <cstddef>      // size_t
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "color.hpp"
#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "math.hpp"
#include "surface.hpp"
#include "video.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup texture
/// \{

enum class texture_access {
  non_lockable = SDL_TEXTUREACCESS_STATIC,  ///< Texture changes rarely and isn't lockable.
  streaming = SDL_TEXTUREACCESS_STREAMING,  ///< Texture changes frequently and is lockable.
  target = SDL_TEXTUREACCESS_TARGET         ///< Texture can be used as a render target.
};

/// \name Texture access functions
/// \{

[[nodiscard]] constexpr auto to_string(const texture_access access) -> std::string_view
{
  switch (access) {
    case texture_access::non_lockable:
      return "non_lockable";

    case texture_access::streaming:
      return "streaming";

    case texture_access::target:
      return "target";

    default:
      throw exception{"Did not recognize texture access!"};
  }
}

inline auto operator<<(std::ostream& stream, const texture_access access) -> std::ostream&
{
  return stream << to_string(access);
}

/// \} End of texture access functions

#if SDL_VERSION_ATLEAST(2, 0, 12)

enum class scale_mode {
  nearest = SDL_ScaleModeNearest,
  linear = SDL_ScaleModeLinear,
  best = SDL_ScaleModeBest
};

/// \name Scale mode functions
/// \{

[[nodiscard]] constexpr auto to_string(const scale_mode mode) -> std::string_view
{
  switch (mode) {
    case scale_mode::nearest:
      return "nearest";

    case scale_mode::linear:
      return "linear";

    case scale_mode::best:
      return "best";

    default:
      throw exception{"Did not recognize scale mode!"};
  }
}

inline auto operator<<(std::ostream& stream, const scale_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

/// \} End of scale mode functions

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

template <typename T>
class basic_texture;

using texture = basic_texture<detail::owner_tag>;
using texture_handle = basic_texture<detail::handle_tag>;

template <typename T>
class basic_texture final {
 public:
  /// \name Construction
  /// \{

  explicit basic_texture(maybe_owner<SDL_Texture*> source) noexcept(detail::is_handle<T>)
      : mTexture{source}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mTexture) {
        throw exception{"Cannot create texture from null pointer!"};
      }
    }
  }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_texture(texture& owner) noexcept : mTexture{owner.get()}
  {}

#ifndef CENTURION_NO_SDL_IMAGE

  /* Creates a texture based the image at the specified path. */
  template <typename Renderer, typename TT = T, detail::enable_for_owner<TT> = 0>
  basic_texture(const Renderer& renderer, const char* path)
      : mTexture{IMG_LoadTexture(renderer.get(), path)}
  {
    if (!mTexture) {
      throw img_error{};
    }
  }

  template <typename Renderer, typename TT = T, detail::enable_for_owner<TT> = 0>
  basic_texture(const Renderer& renderer, const std::string& path)
      : basic_texture{renderer, path.c_str()}
  {}

#endif  // CENTURION_NO_SDL_IMAGE

  /* Creates a texture that is a copy of the supplied surface. */
  template <typename Renderer, typename TT = T, detail::enable_for_owner<TT> = 0>
  basic_texture(const Renderer& renderer, const Surface& surface)
      : mTexture{SDL_CreateTextureFromSurface(renderer.get(), surface.get())}
  {
    if (!mTexture) {
      throw sdl_error{};
    }
  }

  /* Creates a texture with the specified size, format, and access. */
  template <typename Renderer, typename TT = T, detail::enable_for_owner<TT> = 0>
  basic_texture(const Renderer& renderer,
                const PixelFormat format,
                const texture_access access,
                const iarea size)
      : mTexture{SDL_CreateTexture(renderer.get(),
                                   to_underlying(format),
                                   to_underlying(access),
                                   size.width,
                                   size.height)}
  {
    if (!mTexture) {
      throw sdl_error{};
    }
  }

  /// \} End of construction

  void set_alpha(const uint8 alpha) noexcept { SDL_SetTextureAlphaMod(mTexture, alpha); }

  void set_color_mod(const color& color) noexcept
  {
    SDL_SetTextureColorMod(mTexture, color.red(), color.green(), color.blue());
  }

  void set_blend_mode(const BlendMode mode) noexcept
  {
    SDL_SetTextureBlendMode(mTexture, static_cast<SDL_BlendMode>(mode));
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  void set_scale_mode(const scale_mode mode) noexcept
  {
    SDL_SetTextureScaleMode(mTexture, static_cast<SDL_ScaleMode>(mode));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto size() const noexcept -> iarea
  {
    int width{};
    int height{};
    SDL_QueryTexture(mTexture, nullptr, nullptr, &width, &height);
    return {width, height};
  }

  [[nodiscard]] auto width() const noexcept -> int
  {
    const auto [width, height] = size();
    return width;
  }

  [[nodiscard]] auto height() const noexcept -> int
  {
    const auto [width, height] = size();
    return height;
  }

  [[nodiscard]] auto format() const noexcept -> PixelFormat
  {
    uint32 format{};
    SDL_QueryTexture(mTexture, &format, nullptr, nullptr, nullptr);
    return static_cast<PixelFormat>(format);
  }

  [[nodiscard]] auto access() const noexcept -> texture_access
  {
    int access{};
    SDL_QueryTexture(mTexture, nullptr, &access, nullptr, nullptr);
    return static_cast<texture_access>(access);
  }

  [[nodiscard]] auto is_target() const noexcept -> bool
  {
    return access() == texture_access::target;
  }

  [[nodiscard]] auto is_static() const noexcept -> bool
  {
    return access() == texture_access::non_lockable;
  }

  [[nodiscard]] auto is_streaming() const noexcept -> bool
  {
    return access() == texture_access::streaming;
  }

  [[nodiscard]] auto alpha() const noexcept -> uint8
  {
    uint8 alpha{};
    SDL_GetTextureAlphaMod(mTexture, &alpha);
    return alpha;
  }

  [[nodiscard]] auto color_mod() const noexcept -> color
  {
    uint8 red{};
    uint8 green{};
    uint8 blue{};
    SDL_GetTextureColorMod(mTexture, &red, &green, &blue);
    return {red, green, blue};
  }

  [[nodiscard]] auto get_blend_mode() const noexcept -> BlendMode
  {
    SDL_BlendMode mode{};
    SDL_GetTextureBlendMode(mTexture, &mode);
    return static_cast<BlendMode>(mode);
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto get_scale_mode() const noexcept -> scale_mode
  {
    SDL_ScaleMode mode{};
    SDL_GetTextureScaleMode(mTexture, &mode);
    return static_cast<scale_mode>(mode);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /* Releases ownership of the associated SDL texture and returns a pointer to it. */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] auto release() noexcept -> owner<SDL_Texture*>
  {
    return mTexture.release();
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Texture* { return mTexture.get(); }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mTexture != nullptr;
  }

 private:
  detail::pointer<T, SDL_Texture> mTexture;
};

/// \name Texture functions
/// \{

template <typename T>
[[nodiscard]] auto to_string(const basic_texture<T>& texture) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("texture(data: {}, width: {}, height: {})",
                     detail::address_of(texture.get()),
                     texture.width(),
                     texture.height());
#else
  return "texture(data: " + detail::address_of(texture.get()) +
         ", width: " + std::to_string(texture.width()) +
         ", height: " + std::to_string(texture.height()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_texture<T>& texture) -> std::ostream&
{
  return stream << to_string(texture);
}

/// \} End of texture functions

/// \} End of group texture

}  // namespace cen

#endif  // CENTURION_TEXTURE_HPP_
