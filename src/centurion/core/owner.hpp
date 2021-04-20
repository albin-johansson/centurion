#ifndef CENTURION_OWNER_HEADER
#define CENTURION_OWNER_HEADER

#include "sfinae.hpp"

namespace cen {

/**
 * \typedef owner
 *
 * \ingroup core
 *
 * \brief Tag used to denote ownership of raw pointers directly in code.
 *
 * \details If a function takes an `owner<T*>` as a parameter, then the
 * function will claim ownership of that pointer. Subsequently, if a function
 * returns an `owner<T*>`, then ownership is transferred to the caller.
 */
template <typename T, enable_if_pointer_v<T> = 0>
using owner = T;

}  // namespace cen

#endif  // CENTURION_OWNER_HEADER