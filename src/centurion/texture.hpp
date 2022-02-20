#ifndef CENTURION_TEXTURE_HPP_
#define CENTURION_TEXTURE_HPP_

#include <SDL.h>

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

/// \addtogroup render
/// \{

/**
 * \brief Represents different texture access modes.
 *
 * \remarks The `non_lockable` enumerator refers to "static" texture access.
 */
enum class texture_access
{
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

/**
 * \brief Represents different texture scale modes.
 */
enum class scale_mode
{
  nearest = SDL_ScaleModeNearest,  ///< Nearest pixel sampling.
  linear = SDL_ScaleModeLinear,    ///< Linear filtering.
  best = SDL_ScaleModeBest         ///< Anisotropic filtering.
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

using texture = basic_texture<detail::owner_tag>;          ///< An owning texture.
using texture_handle = basic_texture<detail::handle_tag>;  ///< A non-owning texture.

/**
 * \brief Represents a hardware-accelerated image.
 *
 * \ownerhandle `texture`/`texture_handle`
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

  /**
   * \brief Creates a texture based on an existing SDL texture.
   *
   * \details Ownership of the supplied texture is claimed if the texture is owning.
   *
   * \param source the source texture.
   */
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

  /// \} End of construction

  /// \name Setters
  /// \{

  /**
   * \brief Sets the alpha modulation of the texture.
   *
   * \param alpha the new alpha modulation, in the range [0, 255].
   */
  void set_alpha_mod(const uint8 alpha) noexcept { SDL_SetTextureAlphaMod(mTexture, alpha); }

  /**
   * \brief Sets the color modulation of the texture.
   *
   * \note The alpha component of the color is ignored, see `set_alpha_mod()`.
   *
   * \param color the new color modulation.
   */
  void set_color_mod(const color& color) noexcept
  {
    SDL_SetTextureColorMod(mTexture, color.red(), color.green(), color.blue());
  }

  /**
   * \brief Sets the blend mode used by the texture.
   *
   * \param mode the new blend mode.
   */
  void set_blend_mode(const blend_mode mode) noexcept
  {
    SDL_SetTextureBlendMode(mTexture, static_cast<SDL_BlendMode>(mode));
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Sets the scale mode that will be used by the texture.
   *
   * \param mode the new scale mode.
   *
   * \atleastsdl 2.0.12
   */
  void set_scale_mode(const scale_mode mode) noexcept
  {
    SDL_SetTextureScaleMode(mTexture, static_cast<SDL_ScaleMode>(mode));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 18)

  /**
   * \brief Sets the user data associated with the texture.
   *
   * \param data a pointer to the user data.
   *
   * \return `success` if the user data was updated; `failure` otherwise.
   *
   * \atleastsdl 2.0.18
   */
  auto set_user_data(void* data) noexcept -> result
  {
    return SDL_SetTextureUserData(mTexture, data) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  /// \} End of setters

  /// \name Getters
  /// \{

  /**
   * \brief Returns the size of the texture.
   *
   * \return the texture size.
   */
  [[nodiscard]] auto size() const noexcept -> iarea
  {
    int width{};
    int height{};
    SDL_QueryTexture(mTexture, nullptr, nullptr, &width, &height);
    return {width, height};
  }

  /**
   * \brief Returns the width of the texture.
   *
   * \return the texture width.
   *
   * \see `size()`
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    const auto [width, height] = size();
    return width;
  }

  /**
   * \brief Returns the height of the texture.
   *
   * \return the texture height.
   *
   * \see `size()`
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    const auto [width, height] = size();
    return height;
  }

  /**
   * \brief Returns the pixel format used by the texture.
   *
   * \return the texture pixel format.
   */
  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    uint32 format{};
    SDL_QueryTexture(mTexture, &format, nullptr, nullptr, nullptr);
    return static_cast<pixel_format>(format);
  }

  /**
   * \brief Returns the texture access used by the texture.
   *
   * \return the texture access.
   */
  [[nodiscard]] auto access() const noexcept -> texture_access
  {
    int access{};
    SDL_QueryTexture(mTexture, nullptr, &access, nullptr, nullptr);
    return static_cast<texture_access>(access);
  }

  /**
   * \brief Indicates whether the texture has static texture access.
   *
   * \return `true` if the texture has static texture access; `false` otherwise.
   */
  [[nodiscard]] auto is_static() const noexcept -> bool
  {
    return access() == texture_access::non_lockable;
  }

  /**
   * \brief Indicates whether the texture has target texture access.
   *
   * \return `true` if the texture has target texture access; `false` otherwise.
   */
  [[nodiscard]] auto is_target() const noexcept -> bool
  {
    return access() == texture_access::target;
  }

  /**
   * \brief Indicates whether the texture has streaming texture access.
   *
   * \return `true` if the texture has streaming texture access; `false` otherwise.
   */
  [[nodiscard]] auto is_streaming() const noexcept -> bool
  {
    return access() == texture_access::streaming;
  }

  /**
   * \brief Returns the alpha modulation of the texture.
   *
   * \return the texture alpha modulation.
   */
  [[nodiscard]] auto alpha_mod() const noexcept -> uint8
  {
    uint8 alpha{};
    SDL_GetTextureAlphaMod(mTexture, &alpha);
    return alpha;
  }

  /**
   * \brief Returns the color modulation of the texture.
   *
   * \return the texture color modulation.
   */
  [[nodiscard]] auto color_mod() const noexcept -> color
  {
    uint8 red{};
    uint8 green{};
    uint8 blue{};
    SDL_GetTextureColorMod(mTexture, &red, &green, &blue);
    return {red, green, blue};
  }

  /**
   * \brief Returns the blend mode used by the texture.
   *
   * \return the texture blend mode.
   */
  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode
  {
    SDL_BlendMode mode{};
    SDL_GetTextureBlendMode(mTexture, &mode);
    return static_cast<blend_mode>(mode);
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Returns the scale mode used by the texture.
   *
   * \return the texture scale mode.
   *
   * \atleastsdl 2.0.12
   */
  [[nodiscard]] auto get_scale_mode() const noexcept -> scale_mode
  {
    SDL_ScaleMode mode{};
    SDL_GetTextureScaleMode(mTexture, &mode);
    return static_cast<scale_mode>(mode);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 18)

  /**
   * \brief Returns the associated user data.
   *
   * \return a potentially null pointer to the user data.
   *
   * \atleastsdl 2.0.18
   */
  [[nodiscard]] auto user_data() noexcept -> void* { return SDL_GetTextureUserData(mTexture); }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  /// \} End of getters

  /// \name Misc functions
  /// \{

  /**
   * \brief Releases ownership of the associated SDL texture.
   *
   * \warning Think twice before using this function, and make sure you know what you are doing
   * before using it.
   *
   * \return the released SDL texture.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] auto release() noexcept -> owner<SDL_Texture*>
  {
    return mTexture.release();
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Texture* { return mTexture.get(); }

  /**
   * \brief Indicates whether a handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mTexture != nullptr;
  }

  /// \} End of misc functions

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

/// \} End of group render

}  // namespace cen

#endif  // CENTURION_TEXTURE_HPP_
