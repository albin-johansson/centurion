#ifndef CENTURION_DETAIL_CZSTRING_COMPARE_HEADER
#define CENTURION_DETAIL_CZSTRING_COMPARE_HEADER

#include "../core/common.hpp"
#include "stdlib.hpp"

/// \cond FALSE
namespace cen::detail {

struct czstring_compare final
{
  auto operator()(const cstr lhs, const cstr rhs) const noexcept -> bool
  {
    return cmp(lhs, rhs);
  }
};

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_CZSTRING_COMPARE_HEADER
