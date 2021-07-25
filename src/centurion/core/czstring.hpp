#ifndef CENTURION_CZSTRING_HEADER
#define CENTURION_CZSTRING_HEADER

#include "not_null.hpp"

namespace cen {

/// \addtogroup core
/// \{

/**
 * \typedef czstring
 *
 * \brief Alias for a const C-style null-terminated string.
 */
using czstring = const char*;

/**
 * \typedef str
 *
 * \brief Shorter alternative to `czstring`.
 *
 * \since 6.2.0
 */
using str = czstring;

/**
 * \typedef zstring
 *
 * \brief Alias for a C-style null-terminated string.
 */
using zstring = char*;

/**
 * \brief Simply returns the string if it isn't null, returning a placeholder otherwise.
 *
 * \note This is mainly used in `to_string()` overloads.
 *
 * \param string the string that will be checked.
 *
 * \return the supplied string if it isn't null; "n/a" otherwise.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto str_or_na(const str string) noexcept -> not_null<str>
{
  return string ? string : "n/a";
}

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_CZSTRING_HEADER
