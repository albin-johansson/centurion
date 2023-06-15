/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#ifndef CENTURION_SYSTEM_SHARED_OBJECT_HPP_
#define CENTURION_SYSTEM_SHARED_OBJECT_HPP_

#include <SDL.h>

#include <cassert>  // assert
#include <memory>   // unique_ptr

#include "../common/errors.hpp"
#include "../common/primitives.hpp"

namespace cen {

/// Represents a shared object, i.e. dynamic libraries.
class shared_object final {
 public:
  explicit shared_object(const char* object) : mObject {SDL_LoadObject(object)}
  {
    if (!mObject) {
      throw sdl_error {};
    }
  }

  explicit shared_object(const std::string& object) : shared_object {object.c_str()} {}

  /**
   * Attempts to load a C function.
   *
   * \note This can only be used to load C functions.
   *
   * \tparam T the signature of the function, e.g. `void(int, float)`.
   *
   * \param name the function name.
   *
   * \return a potentially null function pointer.
   */
  template <typename T>
  [[nodiscard]] auto load_function(const char* name) const noexcept -> T*
  {
    assert(name);
    return reinterpret_cast<T*>(SDL_LoadFunction(mObject.get(), name));
  }

  template <typename T>
  [[nodiscard]] auto load_function(const std::string& name) const noexcept -> T*
  {
    return load_function<T>(name.c_str());
  }

 private:
  struct object_deleter final {
    void operator()(void* object) noexcept { SDL_UnloadObject(object); }
  };
  std::unique_ptr<void, object_deleter> mObject;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  shared_object() = default;

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

}  // namespace cen

#endif  // CENTURION_SYSTEM_SHARED_OBJECT_HPP_
