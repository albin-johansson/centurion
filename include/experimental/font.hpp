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

#ifndef CENTURION_EXPERIMENTAL_FONT_HEADER
#define CENTURION_EXPERIMENTAL_FONT_HEADER

#include <SDL_ttf.h>

#include <array>
#include <memory>

#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "graphics.hpp"

namespace centurion::experimental {

class fast_font final {
 public:
  template <typename T>
  fast_font(const basic_renderer<T>& renderer, owner<TTF_Font*> font);

  template <typename T>
  static auto unique(const basic_renderer<T>& renderer, owner<TTF_Font*> font)
      -> std::unique_ptr<fast_font>;

 private:
  std::array<char, 1024> m_buffer;
  TTF_Font* m_font;
};

template <typename T>
fast_font::fast_font(const basic_renderer<T>& renderer, owner<TTF_Font*> font)
{}

template <typename T>
auto fast_font::unique(const basic_renderer<T>& renderer, owner<TTF_Font*> font)
    -> std::unique_ptr<fast_font>
{
  return std::make_unique<fast_font>(renderer, font);
}

}  // namespace centurion::experimental

#ifdef CENTURION_HEADER_ONLY
// TODO include source file
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_EXPERIMENTAL_FONT_HEADER