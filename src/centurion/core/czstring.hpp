#ifndef CENTURION_CZSTRING_HEADER
#define CENTURION_CZSTRING_HEADER

#include "not_null.hpp"

namespace cen {

/// \addtogroup core
/// \{

/**
 * \typedef str
 *
 * \brief Alias for a C-style string.
 *
 * \since 6.2.0
 */
using str = const char*;

/**
 * \typedef czstring
 *
 * \brief Alias for a const C-style null-terminated string.
 *
 * \deprecated Since 6.2.0, use `str` instead.
 */
using czstring [[deprecated]] = const char*;

/**
 * \typedef zstring
 * \deprecated Since 6.2.0.
 */
using zstring [[deprecated]] = char*;

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
