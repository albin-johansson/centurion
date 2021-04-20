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
 * \typedef zstring
 *
 * \brief Alias for a C-style null-terminated string.
 */
using zstring = char*;

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_CZSTRING_HEADER
