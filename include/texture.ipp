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
 * @file texture.ipp
 *
 * @brief Provides the implementation of the templates in the `texture`
 * class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_TEXTURE_IMPLEMENTATION
#define CENTURION_TEXTURE_IMPLEMENTATION

#include "centurion_api.hpp"
#include "centurion_exception.hpp"
#include "surface.hpp"
#include "texture.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

template <typename Renderer>
texture::texture(const Renderer& renderer, const surface& surface)
    : basic_texture{SDL_CreateTextureFromSurface(renderer.get(), surface.get())}
{
  if (!get()) {
    throw sdl_error{"Failed to create texture from surface!"};
  }
}

template <typename Renderer>
texture::texture(const Renderer& renderer,
                 pixel_format format,
                 texture_access access,
                 const iarea& size)
    : basic_texture{SDL_CreateTexture(renderer.get(),
                                      static_cast<u32>(format),
                                      static_cast<int>(access),
                                      size.width,
                                      size.height)}
{
  if (!get()) {
    throw sdl_error{"Failed to create texture!"};
  }
}

template <typename Renderer>
texture::texture(const Renderer& renderer, nn_czstring path)
    : basic_texture{IMG_LoadTexture(renderer.get(), path)}
{
  if (!get()) {
    throw img_error{"Failed to load texture from file!"};
  }
}

template <typename Renderer>
auto texture::unique(const Renderer& renderer, nn_czstring path) -> uptr
{
  return std::make_unique<texture>(renderer, path);
}

template <typename Renderer>
auto texture::unique(const Renderer& renderer, const surface& surface) -> uptr
{
  return std::make_unique<texture>(renderer, surface);
}

template <typename Renderer>
auto texture::unique(const Renderer& renderer,
                     pixel_format format,
                     texture_access access,
                     const iarea& size) -> uptr
{
  return std::make_unique<texture>(renderer, format, access, size);
}

template <typename Renderer>
auto texture::shared(const Renderer& renderer, nn_czstring path) -> sptr
{
  return std::make_shared<texture>(renderer, path);
}

template <typename Renderer>
auto texture::shared(const Renderer& renderer, const surface& surface) -> sptr
{
  return std::make_shared<texture>(renderer, surface);
}

template <typename Renderer>
auto texture::shared(const Renderer& renderer,
                     pixel_format format,
                     texture_access access,
                     const iarea& size) -> sptr
{
  return std::make_shared<texture>(renderer, format, access, size);
}

template <typename Renderer>
auto texture::streaming(const Renderer& renderer,
                        nn_czstring path,
                        pixel_format format) -> uptr
{
  const auto blendMode = blend_mode::blend;
  const auto createSurface = [=](czstring path, pixel_format format) {
    surface source{path};
    source.set_blend_mode(blendMode);
    return source.convert(format);
  };
  const auto surface = createSurface(path, format);
  auto texture = texture::unique(renderer,
                                 format,
                                 texture_access::streaming,
                                 {surface.width(), surface.height()});
  texture->set_blend_mode(blendMode);

  u32* pixels = nullptr;
  const auto success = texture->lock(&pixels);
  if (!success) {
    throw centurion_exception{"Failed to lock texture!"};
  }

  const auto maxCount = static_cast<size_t>(surface.pitch()) *
                        static_cast<size_t>(surface.height());
  memcpy(pixels, surface.pixels(), maxCount);

  texture->unlock();

  return texture;
}



}  // namespace centurion

#endif  // CENTURION_TEXTURE_IMPLEMENTATION
