#ifndef CENTURION_LOG_CATEGORY_HEADER
#define CENTURION_LOG_CATEGORY_HEADER

#include <SDL.h>

#include "sdl_log_category_workaround.hpp"

namespace cen {

/// \addtogroup core
/// \{

/**
 * \brief Represents different logging categories.
 *
 * \see `SDL_LogCategory`
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

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_LOG_CATEGORY_HEADER
