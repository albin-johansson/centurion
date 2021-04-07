#ifndef CENTURION_WINDOW_UTILS_HEADER
#define CENTURION_WINDOW_UTILS_HEADER

#include <SDL.h>

#include "../misc/integers.hpp"
#include "renderer.hpp"
#include "window.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \brief Returns a handle to the currently grabbed window.
 *
 * \return a handle to the currently grabbed window, might not refer to a
 * valid window if there is no grabbed window.
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
 * \return a handle to the window associated with the ID, might not refer to a
 * valid window if there no matching window.
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
 * \details The returned handle will be null if the supplied window doesn't
 * have an associated renderer.
 *
 * \note You should always check whether or not the returned handle contains
 * a valid renderer pointer before using it!
 *
 * \tparam T the type of the derived window.
 *
 * \param window the window associated with the desired renderer.
 *
 * \return a handle to the associated renderer, might not contain a valid
 * renderer pointer.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] auto get_renderer(const basic_window<T>& window) noexcept
    -> renderer_handle
{
  return renderer_handle{SDL_GetRenderer(window.get())};
}

/// \}

}  // namespace cen

#endif  // CENTURION_WINDOW_UTILS_HEADER