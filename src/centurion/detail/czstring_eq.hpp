#ifndef CENTURION_DETAIL_CZSTRING_EQ_HEADER
#define CENTURION_DETAIL_CZSTRING_EQ_HEADER

#include <cstring>  // strcmp

#include "../core/str.hpp"

/// \cond FALSE
namespace cen::detail {

/**
 * \brief Indicates whether or not two C-style strings are equal.
 *
 * \param lhs the left-hand side string, can safely be null.
 * \param rhs the right-hand side string, can safely be null.
 *
 * \return `true` if the strings are equal; `false` otherwise.
 *
 * \since 4.1.0
 */
[[nodiscard]] inline auto czstring_eq(const str lhs, const str rhs) noexcept -> bool
{
  if (lhs && rhs) {
    return std::strcmp(lhs, rhs) == 0;
  }
  else {
    return false;
  }
}

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_CZSTRING_EQ_HEADER
