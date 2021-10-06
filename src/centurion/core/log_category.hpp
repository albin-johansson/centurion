#ifndef CENTURION_LOG_CATEGORY_HEADER
#define CENTURION_LOG_CATEGORY_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "exception.hpp"
#include "sdl_log_category_workaround.hpp"

namespace cen {

/// \addtogroup core
/// \{

/**
 * \brief Represents different logging categories.
 *
 * \see `SDL_LogCategory`
 * \see `log_category_count()`
 *
 * \todo Centurion 7: rename `misc` enumerator to `custom`.
 *
 * \since 3.0.0
 */
enum class log_category : int
{
  app = SDL_LOG_CATEGORY_APPLICATION,
  error = SDL_LOG_CATEGORY_ERROR,
  assert = SDL_LOG_CATEGORY_ASSERT,
  system = SDL_LOG_CATEGORY_SYSTEM,
  audio = SDL_LOG_CATEGORY_AUDIO,
  video = SDL_LOG_CATEGORY_VIDEO,
  render = SDL_LOG_CATEGORY_RENDER,
  input = SDL_LOG_CATEGORY_INPUT,
  test = SDL_LOG_CATEGORY_TEST,
  misc = SDL_LOG_CATEGORY_CUSTOM
};

/**
 * \brief Returns the number of enumerators for the `log_category` enum.
 *
 * \return the number of enumerators.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto log_category_count() noexcept -> int
{
  return 10;
}

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied log category.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(log_category::app) == "app"`.
 *
 * \param category the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const log_category category) -> std::string_view
{
  switch (category) {
    case log_category::app:
      return "app";

    case log_category::error:
      return "error";

    case log_category::assert:
      return "assert";

    case log_category::system:
      return "system";

    case log_category::audio:
      return "audio";

    case log_category::video:
      return "video";

    case log_category::render:
      return "render";

    case log_category::input:
      return "input";

    case log_category::test:
      return "test";

    case log_category::misc:
      return "misc";

    default:
      throw cen_error{"Did not recognize log category!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a log category enumerator.
 *
 * \param stream the output stream that will be used.
 * \param priority the enumerator that will be printed.
 *
 * \see `to_string(log_category)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const log_category category) -> std::ostream&
{
  return stream << to_string(category);
}

/// \} End of streaming

/// \name Log category comparison operators
/// \{

/**
 * \brief Indicates whether or not the two log category values are the same.
 *
 * \param lhs the left-hand side log category value.
 * \param rhs the right-hand side log category value.
 *
 * \return `true` if the categories are the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(const log_category lhs,
                                        const SDL_LogCategory rhs) noexcept -> bool
{
  return static_cast<SDL_LogCategory>(lhs) == rhs;
}

/// \copydoc operator==(const log_category, const SDL_LogCategory)
[[nodiscard]] constexpr auto operator==(const SDL_LogCategory lhs,
                                        const log_category rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the two log category values are the same.
 *
 * \param lhs the left-hand side log category value.
 * \param rhs the right-hand side log category value.
 *
 * \return `true` if the categories are the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(const log_category lhs,
                                        const SDL_LogCategory rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(const log_category, const SDL_LogCategory)
[[nodiscard]] constexpr auto operator!=(const SDL_LogCategory lhs,
                                        const log_category rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of log category comparison operators

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_LOG_CATEGORY_HEADER
