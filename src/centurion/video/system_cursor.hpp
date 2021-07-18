#ifndef CENTURION_SYSTEM_CURSOR_HEADER
#define CENTURION_SYSTEM_CURSOR_HEADER

#include <SDL.h>

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum system_cursor
 *
 * \brief Represents the various available system cursors.
 *
 * \since 4.0.0
 *
 * \see `SDL_SystemCursor`
 */
enum class system_cursor
{
  arrow = SDL_SYSTEM_CURSOR_ARROW,
  ibeam = SDL_SYSTEM_CURSOR_IBEAM,
  wait = SDL_SYSTEM_CURSOR_WAIT,
  crosshair = SDL_SYSTEM_CURSOR_CROSSHAIR,
  wait_arrow = SDL_SYSTEM_CURSOR_WAITARROW,
  arrow_nw_se = SDL_SYSTEM_CURSOR_SIZENWSE,
  arrow_ne_sw = SDL_SYSTEM_CURSOR_SIZENESW,
  arrow_w_e = SDL_SYSTEM_CURSOR_SIZEWE,
  arrow_n_s = SDL_SYSTEM_CURSOR_SIZENS,
  arrow_all = SDL_SYSTEM_CURSOR_SIZEALL,
  no = SDL_SYSTEM_CURSOR_NO,
  hand = SDL_SYSTEM_CURSOR_HAND
};

/// \name System cursor comparison operators
/// \{

/**
 * \brief Indicates whether or not two system cursor values are the same.
 *
 * \param lhs the left-hand side system cursor value.
 * \param rhs the right-hand side system cursor value.
 *
 * \return `true` if the system cursor values are the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(const system_cursor lhs,
                                        const SDL_SystemCursor rhs) noexcept -> bool
{
  return static_cast<SDL_SystemCursor>(lhs) == rhs;
}

/// \copydoc operator==(system_cursor, SDL_SystemCursor)
[[nodiscard]] constexpr auto operator==(const SDL_SystemCursor lhs,
                                        const system_cursor rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two system cursor values aren't the same.
 *
 * \param lhs the left-hand side system cursor value.
 * \param rhs the right-hand side system cursor value.
 *
 * \return `true` if the system cursor values aren't the same; `false`
 * otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(const system_cursor lhs,
                                        const SDL_SystemCursor rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(system_cursor, SDL_SystemCursor)
[[nodiscard]] constexpr auto operator!=(const SDL_SystemCursor lhs,
                                        const system_cursor rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of system cursor comparison operators

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_SYSTEM_CURSOR_HEADER
