#ifndef CENTURION_FEATURES_HEADER
#define CENTURION_FEATURES_HEADER

// Do we have general C++20 support?
#if __cplusplus >= 202002L
#define CENTURION_HAS_FEATURE_CPP20
#endif  // __cplusplus >= 202002L

// C++20 nodiscard constructors
#if nodiscard >= 201907L
#define CENTURION_NODISCARD_CTOR [[nodiscard]]
#else
#define CENTURION_NODISCARD_CTOR
#endif  // nodiscard >= 201907L

#ifdef __has_include

#if __has_include(<version>)
#include <version>
#endif  // __has_include(<version>)

#ifdef __cpp_lib_format
#define CENTURION_HAS_FEATURE_FORMAT
#endif  // __cpp_lib_format

#ifdef __cpp_lib_concepts
#define CENTURION_HAS_FEATURE_CONCEPTS
#endif  // __cpp_lib_concepts

#ifdef __cpp_lib_memory_resource
#define CENTURION_HAS_FEATURE_MEMORY_RESOURCE
#endif  // __cpp_lib_memory_resource

#ifdef __cpp_lib_interpolate
#define CENTURION_HAS_FEATURE_LERP
#endif  // __cpp_lib_interpolate

#ifdef __cpp_lib_three_way_comparison
#define CENTURION_HAS_FEATURE_SPACESHIP
#endif  // __cpp_lib_three_way_comparison

#endif  // __has_include

#endif  // CENTURION_FEATURES_HEADER
