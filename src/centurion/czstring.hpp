#ifndef CENTURION_CZSTRING_HEADER
#define CENTURION_CZSTRING_HEADER

#include "centurion_cfg.hpp"
#include "not_null.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \typedef czstring
 *
 * \brief Alias for a const C-style null-terminated string.
 */
using czstring = const char*;

/**
 * \typedef zstring
 *
 * \brief Alias for a C-style null-terminated string.
 */
using zstring = char*;

}  // namespace cen

#endif  // CENTURION_CZSTRING_HEADER
