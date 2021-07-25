#ifndef CENTURION_STR_OR_NA_HEADER
#define CENTURION_STR_OR_NA_HEADER

#include "not_null.hpp"
#include "str.hpp"

namespace cen {

/// \addtogroup core
/// \{

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

#endif  // CENTURION_STR_OR_NA_HEADER
