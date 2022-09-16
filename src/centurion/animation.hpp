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

#ifndef CENTURION_ANIMATION_HPP_
#define CENTURION_ANIMATION_HPP_

#ifndef CENTURION_NO_SDL_IMAGE

#include <SDL.h>
#include <SDL_image.h>

#include "features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include <cassert>  // assert
#include <ostream>  // ostream
#include <string>   // string

#include "common.hpp"
#include "detail/stdlib.hpp"
#include "math.hpp"
#include "surface.hpp"

namespace cen {

#if SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)

class animation final
{
 public:
  /// Creates an animation from an existing handle, claiming ownership in the process
  explicit animation(owner<IMG_Animation*> ptr) : mAnim{ptr}
  {
    if (!mAnim) {
      throw exception{"Invalid null animation!"};
    }
  }

  [[nodiscard]] static auto load(const char* file) -> animation
  {
    assert(file);
    if (auto* ptr = IMG_LoadAnimation(file)) {
      return animation{ptr};
    }
    else {
      throw img_error{};
    }
  }

  [[nodiscard]] static auto load(const std::string& file) -> animation
  {
    return load(file.c_str());
  }

  [[nodiscard]] auto at(const usize index) -> surface_handle
  {
    if (index < count()) {
      return surface_handle{mAnim->frames[index]};
    }
    else {
      throw exception{"Invalid animation frame index!"};
    }
  }

  [[nodiscard]] auto operator[](const usize index) -> surface_handle { return at(index); }

  [[nodiscard]] auto delay(const usize index) const -> int
  {
    if (index < count()) {
      return mAnim->delays[index];
    }
    else {
      throw exception{"Invalid animation frame index!"};
    }
  }

  [[nodiscard]] auto count() const noexcept -> int { return mAnim->count; }

  [[nodiscard]] auto width() const noexcept -> int { return mAnim->w; }
  [[nodiscard]] auto height() const noexcept -> int { return mAnim->h; }
  [[nodiscard]] auto size() const noexcept -> iarea { return {width(), height()}; }

  [[nodiscard]] auto get() const noexcept -> IMG_Animation* { return mAnim.get(); }

 private:
  managed_ptr<IMG_Animation> mAnim;
};

[[nodiscard]] inline auto to_string(const animation& anim) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("animation(data: {})", detail::address_of(anim.get()));
#else
  return "animation(data: " + detail::address_of(anim.get()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const animation& anim) -> std::ostream&
{
  return stream << to_string(anim);
}

#endif  // SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)

}  // namespace cen

#endif  // CENTURION_NO_SDL_IMAGE
#endif  // CENTURION_ANIMATION_HPP_