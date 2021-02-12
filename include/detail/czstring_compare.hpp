#ifndef CENTURION_DETAIL_CZSTRING_COMPARE_HEADER
#define CENTURION_DETAIL_CZSTRING_COMPARE_HEADER

#include "../centurion_cfg.hpp"
#include "czstring.hpp"
#include "czstring_eq.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \cond FALSE
namespace cen::detail {

struct czstring_compare final
{
  auto operator()(const czstring lhs, const czstring rhs) const noexcept -> bool
  {
    return detail::czstring_eq(lhs, rhs);
  }
};

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_CZSTRING_COMPARE_HEADER
