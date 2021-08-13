#ifndef CENTURION_DETAIL_CZSTRING_COMPARE_HEADER
#define CENTURION_DETAIL_CZSTRING_COMPARE_HEADER

#include "../core/str.hpp"
#include "czstring_eq.hpp"

/// \cond FALSE
namespace cen::detail {

struct czstring_compare final
{
  auto operator()(const str lhs, const str rhs) const noexcept -> bool
  {
    return detail::czstring_eq(lhs, rhs);
  }
};

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_CZSTRING_COMPARE_HEADER
