#ifndef CENTURION_NOT_NULL_HEADER
#define CENTURION_NOT_NULL_HEADER

#include <SDL.h>

#include <type_traits>  // enable_if_t, is_pointer_v

namespace cen {

/**
 * \typedef not_null
 *
 * \ingroup misc
 *
 * \brief Tag used to indicate that a pointer cannot be null.
 *
 * \note This alias is equivalent to `T`, it is a no-op.
 *
 * \since 5.0.0
 */
template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>>
using not_null = T;

}  // namespace cen

#endif  // CENTURION_NOT_NULL_HEADER
