#ifndef CENTURION_DETAIL_CONVERT_BOOL_HEADER
#define CENTURION_DETAIL_CONVERT_BOOL_HEADER

#include <SDL.h>

/// \cond FALSE
namespace cen::detail {

/**
 * \brief Returns the corresponding `SDL_bool` value for the supplied boolean value.
 *
 * \param b the boolean value that will be converted.
 *
 * \return `SDL_TRUE` for `true`; `SDL_FALSE` for `false`.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto convert_bool(const bool b) noexcept -> SDL_bool
{
  return b ? SDL_TRUE : SDL_FALSE;
}

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_CONVERT_BOOL_HEADER
