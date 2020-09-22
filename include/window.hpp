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
 * @file window.hpp
 *
 * @brief Provides the `window` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_WINDOW_HEADER
#define CENTURION_WINDOW_HEADER

#include <SDL_video.h>

#include <memory>
#include <ostream>
#include <string>

#include "area.hpp"
#include "basic_window.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @class window
 *
 * @ingroup graphics
 *
 * @brief Represents an owning window.
 *
 * @details This is the main representation of a window in the library. This
 * class should always be the preferred option over `window_handle`. The API of
 * this class and `window_handle` is identical, except for the RAII semantics
 * of this class.
 *
 * @par Examples
 * The following example illustrates a typical setup for a responsive window.
 * Of course, the example assumes that the library has been initialized.
 * @code{.cpp}
 *
 *   #include <window.hpp>
 *   #include <renderer.hpp>
 *   #include <event.hpp>
 *   #include <rect.hpp>
 *
 *   void demo()
 *   {
 *     cen::window window;
 *     cen::renderer renderer{window};
 *
 *     window.set_title("Window demo");
 *
 *     cen::Event event;
 *     bool running = true;
 *
 *     window.show();
 *     while (running) {
 *       while (event.poll()) {
 *         if (event.is<cen::QuitEvent>()) {
 *           running = false;
 *           break;
 *         }
 *       }
 *
 *       renderer.clear_with(cen::black);
 *
 *       const cen::irect rect{{100, 100}, {150, 80}};
 *
 *       renderer.set_color(cen::pink);
 *       renderer.fill_rect(rect);
 *
 *       renderer.present();
 *     }
 *     window.hide();
 *   }
 *
 * @endcode
 *
 * @since 3.0.0
 *
 * @see `window_handle`
 *
 * @headerfile window.hpp
 */
class window final : public basic_window<window>
{
 public:
  /**
   * @brief Creates a window based on the supplied SDL_Window instance.
   *
   * @details The created window will claim ownership of the supplied pointer.
   *
   * @param sdlWindow a pointer to the window that will be claimed, can't be
   * null.
   *
   * @throws exception if the supplied pointer is null.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit window(owner<SDL_Window*> sdlWindow);

  /**
   * @brief Creates a window instance.
   *
   * @details The window will be hidden by default.
   *
   * @param title the title of the window, can't be null.
   * @param size the size of the window, components must be greater than
   * zero, defaults to `default_size()`.
   *
   * @throws exception if the supplied width or height aren't
   * greater than zero.
   * @throws sdl_error if the window cannot be created.
   *
   * @since 3.0.0
   */
  CENTURION_API
  explicit window(nn_czstring title, const iarea& size = default_size());

  /**
   * @brief Creates a 800x600 window. The window will be hidden by default.
   *
   * @throws sdl_error if the window cannot be created.
   *
   * @since 3.0.0
   */
  CENTURION_API
  window();

  /**
   * @brief Converts to `SDL_Window*`.
   *
   * @return a pointer to the associated SDL window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator SDL_Window*() noexcept
  {
    return m_window.get();
  }

  /**
   * @brief Converts to `const SDL_Window*`.
   *
   * @return a pointer to the associated SDL window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator const SDL_Window*() const noexcept
  {
    return m_window.get();
  }

  /**
   * @brief Returns a pointer to the associated SDL window.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However it is useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated SDL window.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Window*
  {
    return m_window.get();
  }

  [[nodiscard]] static constexpr auto default_size() -> iarea
  {
    return {800, 600};
  }

 private:
  class deleter final
  {
   public:
    void operator()(SDL_Window* window) noexcept { SDL_DestroyWindow(window); }
  };
  std::unique_ptr<SDL_Window, deleter> m_window;
};

/**
 * @brief Returns a textual representation of a window.
 *
 * @ingroup graphics
 *
 * @param window the window that will be converted.
 *
 * @return a textual representation of the window.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto to_string(const window& window) -> std::string;

/**
 * @brief Prints a textual representation of a window.
 *
 * @ingroup graphics
 *
 * @param stream the stream that will be used.
 * @param window the window that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto operator<<(std::ostream& stream, const window& window) -> std::ostream&;

}  // namespace cen

#endif  // CENTURION_WINDOW_HEADER