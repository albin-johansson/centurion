/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file basic_texture.hpp
 *
 * @ingroup input
 *
 * @brief Provides the `basic_texture` class.
 *
 * @author Albin Johansson
 *
 * @copyright MIT License
 *
 * @date 2019-2020
 */

#ifndef CENTURION_BASIC_TEXTURE_HEADER
#define CENTURION_BASIC_TEXTURE_HEADER

#include <SDL_render.h>

#include <utility>  // forward

#include "area.hpp"
#include "blend_mode.hpp"
#include "centurion_api.hpp"
#include "color.hpp"
#include "pixel_format.hpp"
#include "point.hpp"
#include "scale_mode.hpp"
#include "texture_access.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

template <typename T>
class texture_traits;

template <typename T>
class basic_texture
{
 public:
  using storage_type = typename texture_traits<T>::storage_type;

  /**
   * @brief Sets the color of the pixel at the specified coordinate.
   *
   * @details This method has no effect if the texture access isn't
   * `Streaming` or if the coordinate is out-of-bounds.
   *
   * @param pixel the pixel that will be changed.
   * @param color the new color of the pixel.
   *
   * @since 4.0.0
   */
  void set_pixel(const ipoint& pixel, const color& color) noexcept;

  /**
   * @brief Sets the alpha value of the texture.
   *
   * @param alpha the alpha value, in the range [0, 255].
   *
   * @since 3.0.0
   */
  void set_alpha(u8 alpha) noexcept;

  /**
   * @brief Sets the blend mode that will be used by the texture.
   *
   * @param mode the blend mode that will be used.
   *
   * @since 3.0.0
   */
  void set_blend_mode(blend_mode mode) noexcept;

  /**
   * @brief Sets the color modulation of the texture.
   *
   * @note The alpha component in the color struct is ignored by this method.
   *
   * @param color the color that will be used to modulate the color of the
   * texture.
   *
   * @since 3.0.0
   */
  void set_color_mod(const color& color) noexcept;

  /**
   * @brief Sets the scale mode that will be used by the texture.
   *
   * @param mode the scale mode that will be used.
   *
   * @since 4.0.0
   */
  void set_scale_mode(scale_mode mode) noexcept;

  /**
   * @brief Returns the pixel format that is used by the texture.
   *
   * @return the pixel format that is used by the texture.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto format() const noexcept -> pixel_format;

  /**
   * @brief Returns the texture access of the texture.
   *
   * @return the texture access of the texture.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto access() const noexcept -> texture_access;

  /**
   * @brief Returns the width of the texture.
   *
   * @return the width of the texture.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto width() const noexcept -> int;

  /**
   * @brief Returns the height of the texture.
   *
   * @return the height of the texture.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto height() const noexcept -> int;

  /**
   * @brief Returns the size of the texture.
   *
   * @return the size of the texture.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto size() const noexcept -> iarea;

  /**
   * @brief Indicates whether or not the texture is a possible render target.
   *
   * @return `true` if the texture is a possible render target; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_target() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the texture has static texture access.
   *
   * @return `true` if the texture has static texture access.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_static() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the texture has streaming texture access.
   *
   * @return `true` if the texture has streaming texture access; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_streaming() const noexcept -> bool;

  /**
   * @brief Returns the alpha value of the texture.
   *
   * @return the alpha value of the texture.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto alpha() const noexcept -> u8;

  /**
   * @brief Returns the blend mode of the texture.
   *
   * @return the blend mode of the texture.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode;

  /**
   * @brief Returns the color modulation of the texture.
   *
   * @return the modulation of the texture.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto color_mod() const noexcept -> color;

  /**
   * @brief Returns the scale mode that is used by the texture.
   *
   * @return the scale mode that is used by the texture.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get_scale_mode() const noexcept -> scale_mode;

  /**
   * @brief Returns a pointer to the associated `SDL_Texture`.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However it's useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated `SDL_Texture`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Texture*;

  /**
   * @brief Converts to `SDL_Texture*`.
   *
   * @return a pointer to the associated `SDL_Texture`.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator SDL_Texture*() noexcept;

  /**
   * @brief Converts to `const SDL_Texture*`.
   *
   * @return a pointer to the associated `SDL_Texture`.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator const SDL_Texture*() const noexcept;

 protected:
  template <typename... Args>
  explicit basic_texture(Args&&... args);

  [[nodiscard]] auto get_storage() noexcept -> storage_type&
  {
    return m_storage;
  }

  [[nodiscard]] auto get_storage() const noexcept -> const storage_type&
  {
    return m_storage;
  }

  /**
   * @brief Locks the texture for write-only pixel access.
   *
   * @remarks This method is only applicable if the texture access of the
   * texture is `Streaming`.
   *
   * @param pixels this will be filled with a pointer to the locked pixels.
   * @param pitch This is filled in with the pitch of the locked pixels, can
   * safely be null if it isn't needed.
   *
   * @return `true` if all went well; `false` otherwise.
   *
   * @since 4.0.0
   */
  auto lock(u32** pixels, int* pitch = nullptr) noexcept -> bool;

  /**
   * @brief Unlocks the texture.
   *
   * @since 4.0.0
   */
  void unlock() noexcept;

 private:
  storage_type m_storage;

  [[nodiscard]] auto ptr() const noexcept -> SDL_Texture*
  {
    if constexpr (std::is_pointer_v<storage_type>) {
      return m_storage;
    } else {
      return m_storage.get();
    }
  };
};

/**
 * @brief Indicates whether or not the two texture access values are the same.
 *
 * @ingroup graphics
 *
 * @param lhs the lhs texture access value.
 * @param rhs the rhs texture access value.
 *
 * @return `true` if the texture access values are the same; `false` otherwise.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator==(enum texture_access lhs,
                                               SDL_TextureAccess rhs) noexcept
    -> bool
{
  return static_cast<SDL_TextureAccess>(lhs) == rhs;
}

/**
 * @copydoc operator==(texture_access, SDL_TextureAccess)
 *
 * @ingroup graphics
 */
[[nodiscard]] inline constexpr auto operator==(SDL_TextureAccess lhs,
                                               enum texture_access rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not the two texture access values aren't the
 * same.
 *
 * @ingroup graphics
 *
 * @param lhs the lhs texture access value.
 * @param rhs the rhs texture access value.
 *
 * @return `true` if the texture access values aren't the same; `false`
 * otherwise.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(texture_access lhs,
                                               SDL_TextureAccess rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(texture_access, SDL_TextureAccess)
 *
 * @ingroup graphics
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_TextureAccess lhs,
                                               texture_access rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

template <typename T>
template <typename... Args>
basic_texture<T>::basic_texture(Args&&... args)
    : m_storage{std::forward<Args>(args)...}
{}

template <typename T>
auto basic_texture<T>::lock(u32** pixels, int* pitch) noexcept -> bool
{
  if (pitch) {
    const auto result = SDL_LockTexture(
        ptr(), nullptr, reinterpret_cast<void**>(pixels), pitch);
    return result == 0;
  } else {
    int dummyPitch;
    const auto result = SDL_LockTexture(
        ptr(), nullptr, reinterpret_cast<void**>(pixels), &dummyPitch);
    return result == 0;
  }
}

template <typename T>
void basic_texture<T>::unlock() noexcept
{
  SDL_UnlockTexture(ptr());
}

template <typename T>
void basic_texture<T>::set_pixel(const ipoint& pixel,
                                 const color& color) noexcept
{
  if (access() != texture_access::streaming || pixel.x() < 0 || pixel.y() < 0 ||
      pixel.x() >= width() || pixel.y() >= height()) {
    return;
  }

  u32* pixels = nullptr;
  int pitch;
  const auto success = lock(&pixels, &pitch);
  if (!success) {
    return;
  }

  const int nPixels = (pitch / 4) * height();
  const int index = (pixel.y() * width()) + pixel.x();

  if ((index >= 0) && (index < nPixels)) {
    auto* pixelFormat = SDL_AllocFormat(static_cast<u32>(format()));
    const auto value = SDL_MapRGBA(
        pixelFormat, color.red(), color.green(), color.blue(), color.alpha());

    SDL_FreeFormat(pixelFormat);

    pixels[index] = value;
  }

  unlock();
}

template <typename T>
void basic_texture<T>::set_alpha(u8 alpha) noexcept
{
  SDL_SetTextureAlphaMod(ptr(), alpha);
}

template <typename T>
void basic_texture<T>::set_blend_mode(blend_mode mode) noexcept
{
  SDL_SetTextureBlendMode(ptr(), static_cast<SDL_BlendMode>(mode));
}

template <typename T>
void basic_texture<T>::set_color_mod(const color& color) noexcept
{
  SDL_SetTextureColorMod(ptr(), color.red(), color.green(), color.blue());
}

template <typename T>
void basic_texture<T>::set_scale_mode(scale_mode mode) noexcept
{
  SDL_SetTextureScaleMode(ptr(), static_cast<SDL_ScaleMode>(mode));
}

template <typename T>
auto basic_texture<T>::format() const noexcept -> pixel_format
{
  u32 format{};
  SDL_QueryTexture(ptr(), &format, nullptr, nullptr, nullptr);
  return static_cast<pixel_format>(format);
}

template <typename T>
auto basic_texture<T>::access() const noexcept -> texture_access
{
  int access{};
  SDL_QueryTexture(ptr(), nullptr, &access, nullptr, nullptr);
  return static_cast<texture_access>(access);
}

template <typename T>
auto basic_texture<T>::width() const noexcept -> int
{
  const auto [width, height] = size();
  return width;
}

template <typename T>
auto basic_texture<T>::height() const noexcept -> int
{
  const auto [width, height] = size();
  return height;
}

template <typename T>
auto basic_texture<T>::size() const noexcept -> iarea
{
  int width{};
  int height{};
  SDL_QueryTexture(ptr(), nullptr, nullptr, &width, &height);
  return {width, height};
}

template <typename T>
auto basic_texture<T>::is_target() const noexcept -> bool
{
  return access() == texture_access::target;
}

template <typename T>
auto basic_texture<T>::is_static() const noexcept -> bool
{
  return access() == texture_access::no_lock;
}

template <typename T>
auto basic_texture<T>::is_streaming() const noexcept -> bool
{
  return access() == texture_access::streaming;
  ;
}

template <typename T>
auto basic_texture<T>::alpha() const noexcept -> u8
{
  u8 alpha{};
  SDL_GetTextureAlphaMod(ptr(), &alpha);
  return alpha;
}

template <typename T>
auto basic_texture<T>::get_blend_mode() const noexcept -> blend_mode
{
  SDL_BlendMode mode{};
  SDL_GetTextureBlendMode(ptr(), &mode);
  return static_cast<blend_mode>(mode);
}

template <typename T>
auto basic_texture<T>::color_mod() const noexcept -> color
{
  u8 red{};
  u8 green{};
  u8 blue{};
  SDL_GetTextureColorMod(ptr(), &red, &green, &blue);
  return {red, green, blue, 0xFF};
}

template <typename T>
auto basic_texture<T>::get_scale_mode() const noexcept -> scale_mode
{
  SDL_ScaleMode mode{};
  SDL_GetTextureScaleMode(ptr(), &mode);
  return static_cast<scale_mode>(mode);
}

template <typename T>
auto basic_texture<T>::get() const noexcept -> SDL_Texture*
{
  return ptr();
}

template <typename T>
basic_texture<T>::operator SDL_Texture*() noexcept
{
  return ptr();
}

template <typename T>
basic_texture<T>::operator const SDL_Texture*() const noexcept
{
  return ptr();
}

}  // namespace cen

#endif  // CENTURION_BASIC_TEXTURE_HEADER
