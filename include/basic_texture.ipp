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
 * @file basic_texture.ipp
 *
 * @ingroup input
 *
 * @brief Provides the implementation of the `basic_texture` templates.
 *
 * @author Albin Johansson
 *
 * @copyright MIT License
 *
 * @date 2019-2020
 */

#ifndef CENTURION_BASIC_TEXTURE_IMPLEMENTATION
#define CENTURION_BASIC_TEXTURE_IMPLEMENTATION

#include <utility>  // forward

#include "basic_texture.hpp"

namespace centurion {

template <typename T>
template <typename... Args>
basic_texture<T>::basic_texture(Args&&... args)
    : m_storage{std::forward<Args>(args)...}
{}

template <typename Derived>
auto basic_texture<Derived>::lock(u32** pixels, int* pitch) noexcept -> bool
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

template <typename Derived>
void basic_texture<Derived>::unlock() noexcept
{
  SDL_UnlockTexture(ptr());
}

template <typename Derived>
void basic_texture<Derived>::set_pixel(const ipoint& pixel,
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

template <typename Derived>
void basic_texture<Derived>::set_alpha(u8 alpha) noexcept
{
  SDL_SetTextureAlphaMod(ptr(), alpha);
}

template <typename Derived>
void basic_texture<Derived>::set_blend_mode(blend_mode mode) noexcept
{
  SDL_SetTextureBlendMode(ptr(), static_cast<SDL_BlendMode>(mode));
}

template <typename Derived>
void basic_texture<Derived>::set_color_mod(const color& color) noexcept
{
  SDL_SetTextureColorMod(ptr(), color.red(), color.green(), color.blue());
}

template <typename Derived>
void basic_texture<Derived>::set_scale_mode(scale_mode mode) noexcept
{
  SDL_SetTextureScaleMode(ptr(), static_cast<SDL_ScaleMode>(mode));
}

template <typename Derived>
auto basic_texture<Derived>::format() const noexcept -> pixel_format
{
  u32 format{};
  SDL_QueryTexture(ptr(), &format, nullptr, nullptr, nullptr);
  return static_cast<pixel_format>(format);
}

template <typename Derived>
auto basic_texture<Derived>::access() const noexcept -> texture_access
{
  int access{};
  SDL_QueryTexture(ptr(), nullptr, &access, nullptr, nullptr);
  return static_cast<texture_access>(access);
}

template <typename Derived>
auto basic_texture<Derived>::width() const noexcept -> int
{
  const auto [width, height] = size();
  return width;
}

template <typename Derived>
auto basic_texture<Derived>::height() const noexcept -> int
{
  const auto [width, height] = size();
  return height;
}

template <typename Derived>
auto basic_texture<Derived>::size() const noexcept -> iarea
{
  int width{};
  int height{};
  SDL_QueryTexture(ptr(), nullptr, nullptr, &width, &height);
  return {width, height};
}

template <typename Derived>
auto basic_texture<Derived>::is_target() const noexcept -> bool
{
  return access() == texture_access::target;
}

template <typename Derived>
auto basic_texture<Derived>::is_static() const noexcept -> bool
{
  return access() == texture_access::no_lock;
}

template <typename Derived>
auto basic_texture<Derived>::is_streaming() const noexcept -> bool
{
  return access() == texture_access::streaming;
  ;
}

template <typename Derived>
auto basic_texture<Derived>::alpha() const noexcept -> u8
{
  u8 alpha{};
  SDL_GetTextureAlphaMod(ptr(), &alpha);
  return alpha;
}

template <typename Derived>
auto basic_texture<Derived>::get_blend_mode() const noexcept -> blend_mode
{
  SDL_BlendMode mode{};
  SDL_GetTextureBlendMode(ptr(), &mode);
  return static_cast<blend_mode>(mode);
}

template <typename Derived>
auto basic_texture<Derived>::color_mod() const noexcept -> color
{
  u8 red{};
  u8 green{};
  u8 blue{};
  SDL_GetTextureColorMod(ptr(), &red, &green, &blue);
  return {red, green, blue, 0xFF};
}

template <typename Derived>
auto basic_texture<Derived>::get_scale_mode() const noexcept -> scale_mode
{
  SDL_ScaleMode mode{};
  SDL_GetTextureScaleMode(ptr(), &mode);
  return static_cast<scale_mode>(mode);
}

template <typename Derived>
auto basic_texture<Derived>::get() const noexcept -> SDL_Texture*
{
  return ptr();
}

template <typename Derived>
basic_texture<Derived>::operator SDL_Texture*() noexcept
{
  return ptr();
}

template <typename Derived>
basic_texture<Derived>::operator const SDL_Texture*() const noexcept
{
  return ptr();
}

}  // namespace centurion

#endif  // CENTURION_BASIC_TEXTURE_IMPLEMENTATION
