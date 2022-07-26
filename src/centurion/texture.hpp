/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

enum class texture_access
{
  non_lockable = SDL_TEXTUREACCESS_STATIC,  ///< Texture changes rarely and isn't lockable.
  streaming = SDL_TEXTUREACCESS_STREAMING,  ///< Texture changes frequently and is lockable.
  target = SDL_TEXTUREACCESS_TARGET         ///< Texture can be used as a render target.
};

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

#if SDL_VERSION_ATLEAST(2, 0, 12)

enum class scale_mode
{
  nearest = SDL_ScaleModeNearest,  ///< Nearest pixel sampling.
  linear = SDL_ScaleModeLinear,    ///< Linear filtering.
  best = SDL_ScaleModeBest         ///< Anisotropic filtering.
};

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

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

template <typename T>
class basic_texture;

using texture = basic_texture<detail::owner_tag>;
using texture_handle = basic_texture<detail::handle_tag>;

/**
 * Represents a hardware-accelerated image.
 *
 * \see texture
 * \see texture_handle
 */
template <typename T>
class basic_texture final
{
 public:
  /**
   * Creates a texture based on an existing SDL texture.
   *
   * Ownership of the supplied texture is claimed only if the texture is owning!
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

  void set_alpha_mod(const uint8 alpha) noexcept { SDL_SetTextureAlphaMod(mTexture, alpha); }

  void set_color_mod(const color& color) noexcept
  {
    SDL_SetTextureColorMod(mTexture, color.red(), color.green(), color.blue());
  }

  void set_blend_mode(const blend_mode mode) noexcept
  {
    SDL_SetTextureBlendMode(mTexture, static_cast<SDL_BlendMode>(mode));
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  void set_scale_mode(const scale_mode mode) noexcept
  {
    SDL_SetTextureScaleMode(mTexture, static_cast<SDL_ScaleMode>(mode));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 18)

  auto set_user_data(void* data) noexcept -> result
  {
    return SDL_SetTextureUserData(mTexture, data) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

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

  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    uint32 format{};
    SDL_QueryTexture(mTexture, &format, nullptr, nullptr, nullptr);
    return static_cast<pixel_format>(format);
  }

  [[nodiscard]] auto access() const noexcept -> texture_access
  {
    int access{};
    SDL_QueryTexture(mTexture, nullptr, &access, nullptr, nullptr);
    return static_cast<texture_access>(access);
  }

  [[nodiscard]] auto is_static() const noexcept -> bool
  {
    return access() == texture_access::non_lockable;
  }

  [[nodiscard]] auto is_target() const noexcept -> bool
  {
    return access() == texture_access::target;
  }

  [[nodiscard]] auto is_streaming() const noexcept -> bool
  {
    return access() == texture_access::streaming;
  }

  [[nodiscard]] auto alpha_mod() const noexcept -> uint8
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

  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode
  {
    SDL_BlendMode mode{};
    SDL_GetTextureBlendMode(mTexture, &mode);
    return static_cast<blend_mode>(mode);
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto get_scale_mode() const noexcept -> scale_mode
  {
    SDL_ScaleMode mode{};
    SDL_GetTextureScaleMode(mTexture, &mode);
    return static_cast<scale_mode>(mode);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto user_data() noexcept -> void* { return SDL_GetTextureUserData(mTexture); }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  /// Releases ownership of the associated SDL texture, use at your own risk.
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] auto release() noexcept -> owner<SDL_Texture*>
  {
    return mTexture.release();
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Texture* { return mTexture.get(); }

  /// Indicates whether the handle holds a non-null pointer.
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mTexture != nullptr;
  }

 private:
  detail::pointer<T, SDL_Texture> mTexture;
};

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

}  // namespace cen

#endif  // CENTURION_TEXTURE_HPP_
