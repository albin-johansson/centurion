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
 * \details If a function takes an `owner<T*>` as a parameter, then the function will
 * claim ownership of that pointer. Subsequently, if a function returns an `owner<T*>`,
 * then ownership is transferred to the caller.
 */
template <typename T, enable_if_pointer_v<T> = 0>
using owner = T;

/**
 * \typedef maybe_owner
 *
 * \ingroup core
 *
 * \brief Tag used to denote conditional ownership of raw pointers directly in code.
 *
 * \details This is primarily used in constructors of owner/handle classes, where the
 * owner version will claim ownership of the pointer, whilst the handle does not.
 *
 * \since 6.0.0
 */
template <typename T, enable_if_pointer_v<T> = 0>
using maybe_owner = T;

}  // namespace cen

#endif  // CENTURION_OWNER_HEADER