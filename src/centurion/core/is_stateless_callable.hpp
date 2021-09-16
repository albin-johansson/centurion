#ifndef CENTURION_IS_STATELESS_CALLABLE_HEADER
#define CENTURION_IS_STATELESS_CALLABLE_HEADER

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_CONCEPTS

#include <concepts>  // default_initializable, invocable

namespace cen {

/// \addtogroup core
/// \{

template <typename T, typename... Args>
concept is_stateless_callable = std::default_initializable<T> && std::invocable<T, Args...>;

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_HAS_FEATURE_CONCEPTS
#endif  // CENTURION_IS_STATELESS_CALLABLE_HEADER
