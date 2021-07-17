#include "compiler/features.hpp"

#include <gtest/gtest.h>

#include <array>    // array
#include <cstddef>  // byte

#ifdef CENTURION_HAS_FEATURE_CONCEPTS
  #include <concepts>
#endif  // CENTURION_HAS_FEATURE_CONCEPTS

#ifdef CENTURION_HAS_FEATURE_FORMAT
  #include <format>
#endif  // CENTURION_HAS_FEATURE_FORMAT

#ifdef CENTURION_HAS_FEATURE_MEMORY_RESOURCE
  #include <memory_resource>
#endif  // CENTURION_HAS_FEATURE_MEMORY_RESOURCE

#ifdef CENTURION_HAS_FEATURE_CONCEPTS

TEST(Features, Concepts)
{
  using foo = int;
  using bar = int;
  static_assert(std::same_as<foo, bar>);
}

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

#ifdef CENTURION_HAS_FEATURE_FORMAT

TEST(Features, Format)
{
  ASSERT_EQ("foo: 42", std::format("foo: {}", 42));
}

#endif  // CENTURION_HAS_FEATURE_FORMAT

#ifdef CENTURION_HAS_FEATURE_MEMORY_RESOURCE

TEST(Features, MemoryResource)
{
  std::array<std::byte, 64> buffer{};
  std::pmr::monotonic_buffer_resource resource{buffer.data(), sizeof buffer};
}

#endif  // CENTURION_HAS_FEATURE_MEMORY_RESOURCE