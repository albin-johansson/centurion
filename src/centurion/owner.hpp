#ifndef CENTURION_OWNER_HEADER
#define CENTURION_OWNER_HEADER

#include <type_traits>  // enable_if_t, is_pointer_v

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \typedef owner
 *
 * \brief Tag used to denote ownership of raw pointers directly in code.
 *
 * \details If a function takes an `owner<T*>` as a parameter, then the
 * function will claim ownership of that pointer. Subsequently, if a function
 * returns an `owner<T*>`, then ownership is transferred to the caller.
 */
template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>>
using owner = T;

}  // namespace cen

#endif  // CENTURION_OWNER_HEADER