/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#ifndef CENTURION_SHARED_OBJECT_HEADER
#define CENTURION_SHARED_OBJECT_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <memory>   // unique_ptr

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "exception.hpp"
#include "not_null.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup system
/// \{

/**
 * \class shared_object
 *
 * \brief Represents a shared object, such as dynamic libraries (e.g. `.so` and
 * `.dll` files).
 *
 * \since 5.3.0
 *
 * \headerfile shared_object.hpp
 */
class shared_object final
{
 public:
  /**
   * \brief Loads a shared object.
   *
   * \param object the name of the shared object that will be loaded.
   *
   * \throws sdl_error if the shared object cannot be loaded.
   *
   * \since 5.3.0
   */
  explicit shared_object(const not_null<czstring> object)
      : m_object{SDL_LoadObject(object)}
  {
    if (!m_object) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Attempts to load a function from the shared object.
   *
   * \note The function must be a C-function!
   *
   * \tparam T the signature of the function, e.g. `void(int, float)`.
   *
   * \param name the name of the function in the shared object.
   *
   * \return the loaded function; a null pointer is returned if something goes
   * wrong.
   *
   * \since 5.3.0
   */
  template <typename T>
  [[nodiscard]] auto load_function(const not_null<czstring> name) const noexcept
      -> T*
  {
    assert(name);
    return reinterpret_cast<T*>(SDL_LoadFunction(m_object.get(), name));
  }

 private:
  struct deleter final
  {
    void operator()(void* object) noexcept
    {
      SDL_UnloadObject(object);
    }
  };
  std::unique_ptr<void, deleter> m_object;

#ifdef CENTURION_MOCK_FRIENDLY_MODE
 public:
  shared_object() = default;
#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/// \} End of system group

}  // namespace cen

#endif  // CENTURION_SHARED_OBJECT_HEADER
