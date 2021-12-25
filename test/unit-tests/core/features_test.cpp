#include "features.hpp"

#include <gtest/gtest.h>

#include <array>    // array
#include <cstddef>  // byte

#if CENTURION_HAS_FEATURE_CONCEPTS
#include <concepts>
#endif  // CENTURION_HAS_FEATURE_CONCEPTS

#if CENTURION_HAS_FEATURE_FORMAT
#include <format>
#endif  // CENTURION_HAS_FEATURE_FORMAT

#if CENTURION_HAS_FEATURE_CONCEPTS

TEST(Features, Concepts)
{
  using foo = int;
  using bar = int;
  static_assert(std::same_as<foo, bar>);
}

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

#if CENTURION_HAS_FEATURE_FORMAT

TEST(Features, Format)
{
  ASSERT_EQ("foo: 42", std::format("foo: {}", 42));
}

#endif  // CENTURION_HAS_FEATURE_FORMAT
