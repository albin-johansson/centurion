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
 * @file sharing_texture.ipp
 *
 * @brief Provides the implementation of the `sharing_texture` templates.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_SHARING_TEXTURE_IMPLEMENTATION
#define CENTURION_SHARING_TEXTURE_IMPLEMENTATION

#include "centurion_api.hpp"
#include "centurion_exception.hpp"
#include "sharing_texture.hpp"
#include "surface.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

template <typename Renderer>
sharing_texture::sharing_texture(const Renderer& renderer, nn_czstring path)
    : basic_texture{IMG_LoadTexture(renderer.get(), path), get_deleter()}
{
  if (!get()) {
    throw img_error{"Failed to load sharing_texture from file!"};
  }
}

template <typename Renderer>
sharing_texture::sharing_texture(const Renderer& renderer,
                                 const surface& surface)
    : basic_texture{SDL_CreateTextureFromSurface(renderer.get(), surface.get()),
                    get_deleter()}
{
  if (!get()) {
    throw sdl_error{"Failed to create sharing_texture from surface!"};
  }
}

template <typename Renderer>
sharing_texture::sharing_texture(const Renderer& renderer,
                                 pixel_format format,
                                 texture_access access,
                                 const iarea& size)
    : basic_texture{SDL_CreateTexture(renderer.get(),
                                      static_cast<u32>(format),
                                      static_cast<int>(access),
                                      size.width,
                                      size.height),
                    get_deleter()}
{
  if (!get()) {
    throw sdl_error{"Failed to create sharing_texture!"};
  }
}

}  // namespace centurion

#endif  // CENTURION_SHARING_TEXTURE_IMPLEMENTATION
