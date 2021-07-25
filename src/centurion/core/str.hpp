#ifndef CENTURION_STR_HEADER
#define CENTURION_STR_HEADER

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

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_STR_HEADER
