#ifndef CENTURION_SYSTEM_CURSOR_HEADER
#define CENTURION_SYSTEM_CURSOR_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

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
 * \see `system_cursor_count()`
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

/**
 * \brief Returns the number of available system cursors.
 *
 * \return the number of system cursors.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto system_cursor_count() noexcept -> int
{
  return SDL_NUM_SYSTEM_CURSORS;
}

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied system cursor.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(system_cursor::hand) == "hand"`.
 *
 * \param cursor the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const system_cursor cursor) -> std::string_view
{
  switch (cursor) {
    case system_cursor::arrow:
      return "arrow";

    case system_cursor::ibeam:
      return "ibeam";

    case system_cursor::wait:
      return "wait";

    case system_cursor::crosshair:
      return "crosshair";

    case system_cursor::wait_arrow:
      return "wait_arrow";

    case system_cursor::arrow_nw_se:
      return "arrow_nw_se";

    case system_cursor::arrow_ne_sw:
      return "arrow_ne_sw";

    case system_cursor::arrow_w_e:
      return "arrow_w_e";

    case system_cursor::arrow_n_s:
      return "arrow_n_s";

    case system_cursor::arrow_all:
      return "arrow_all";

    case system_cursor::no:
      return "no";

    case system_cursor::hand:
      return "hand";

    default:
      throw cen_error{"Did not recognize system cursor!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a system cursor enumerator.
 *
 * \param stream the output stream that will be used.
 * \param cursor the enumerator that will be printed.
 *
 * \see `to_string(system_cursor)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const system_cursor cursor) -> std::ostream&
{
  return stream << to_string(cursor);
}

/// \} End of streaming

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
