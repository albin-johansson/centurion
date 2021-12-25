#ifndef CENTURION_FEATURES_HPP_
#define CENTURION_FEATURES_HPP_

/// Do we have general C++20 support?
#if __cplusplus >= 202002L
#define CENTURION_HAS_FEATURE_CPP20 1
#else
#define CENTURION_HAS_FEATURE_CPP20 0
#endif  // __cplusplus >= 202002L

/// C++20 nodiscard constructors
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
#define CENTURION_HAS_FEATURE_FORMAT 1
#else
#define CENTURION_HAS_FEATURE_FORMAT 0
#endif  // __cpp_lib_format

#ifdef __cpp_lib_concepts
#define CENTURION_HAS_FEATURE_CONCEPTS 1
#else
#define CENTURION_HAS_FEATURE_CONCEPTS 0
#endif  // __cpp_lib_concepts

#ifdef __cpp_lib_interpolate
#define CENTURION_HAS_FEATURE_LERP 1
#else
#define CENTURION_HAS_FEATURE_LERP 0
#endif  // __cpp_lib_interpolate

#ifdef __cpp_lib_three_way_comparison
#define CENTURION_HAS_FEATURE_SPACESHIP 1
#else
#define CENTURION_HAS_FEATURE_SPACESHIP 0
#endif  // __cpp_lib_three_way_comparison

#if __cpp_lib_chrono >= 201907L
#define CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES 1
#else
#define CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES 0
#endif  // __cpp_lib_chrono >= 201907L

#if __cpp_lib_to_array >= 201907L
#define CENTURION_HAS_FEATURE_TO_ARRAY 1
#else
#define CENTURION_HAS_FEATURE_TO_ARRAY 0
#endif  // __cpp_lib_to_array >= 201907L

#if __cpp_lib_to_chars >= 201611L
#define CENTURION_HAS_FEATURE_CHARCONV 1
#else
#define CENTURION_HAS_FEATURE_CHARCONV 0
#endif  // __cpp_lib_to_chars >= 201611L

#endif  // __has_include

#endif  // CENTURION_FEATURES_HPP_
