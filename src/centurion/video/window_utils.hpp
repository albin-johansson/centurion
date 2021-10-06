#ifndef CENTURION_WINDOW_UTILS_HEADER
#define CENTURION_WINDOW_UTILS_HEADER

#include <SDL.h>

#include <utility>  // pair, make_pair, move

#include "../core/integers.hpp"
#include "../math/area.hpp"
#include "renderer.hpp"
#include "window.hpp"

namespace cen {

/// \addtogroup video
/// \{

/// \name Window functions
/// \{

/**
 * \brief Returns a handle to the currently grabbed window.
 *
 * \return a handle to the currently grabbed window, might not refer to a valid window if
 * there is no grabbed window.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto get_grabbed_window() noexcept -> window_handle
{
  return window_handle{SDL_GetGrabbedWindow()};
}

/**
 * \brief Returns a handle to the window that has mouse focus.
 *
 * \return a window handle.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto mouse_focus_window() noexcept -> window_handle
{
  return window_handle{SDL_GetMouseFocus()};
}

/**
 * \brief Returns a handle to the window that has keyboard focus.
 *
 * \return a window handle.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto keyboard_focus_window() noexcept -> window_handle
{
  return window_handle{SDL_GetKeyboardFocus()};
}

/**
 * \brief Returns a handle to the window associated with the specified ID.
 *
 * \param id the ID associated with the desired window.
 *
 * \return a handle to the window associated with the ID, might not refer to a valid
 * window if there no matching window.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto get_window(const u32 id) noexcept -> window_handle
{
  return window_handle{SDL_GetWindowFromID(id)};
}

/**
 * \brief Returns a handle to the renderer associated with a window.
 *
 * \details The returned handle will be null if the supplied window doesn't have an
 * associated renderer.
 *
 * \note You should always check whether or not the returned handle contains a valid
 * renderer pointer before using it!
 *
 * \tparam T the type of the derived window.
 *
 * \param window the window associated with the desired renderer.
 *
 * \return a handle to the associated renderer, might not contain a valid renderer
 * pointer.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] auto get_renderer(const basic_window<T>& window) noexcept -> renderer_handle
{
  return renderer_handle{SDL_GetRenderer(window.get())};
}

/**
 * \brief Creates a window and an associated renderer.
 *
 * \details This function can be used as a slightly more concise way to create a window
 * and a renderer.
 * \code{cpp}
 *   auto [window, renderer] = cen::make_window_and_renderer();
 * \endcode
 *
 * \param size the size of the window.
 * \param flags the flags used by the window, see `basic_window::window_flags`.
 *
 * \return the created window and renderer.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto make_window_and_renderer(const iarea size = window::default_size(),
                                                   const u32 flags = window::default_flags())
    -> std::pair<window, renderer>
{
  cen::window window{"Centurion window", size, flags};
  cen::renderer renderer{window};
  return std::make_pair(std::move(window), std::move(renderer));
}

/// \} End of window functions

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_WINDOW_UTILS_HEADER