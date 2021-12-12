#pragma once

#include <gtest/gtest.h>

// Macros to reduce the quite severe boilerplate required to set up typed tests

// Defines a typed test with its own class with the specified name
#define CENTURION_DEFINE_TYPED_TEST(Name, Types) \
  template <typename T>                          \
  class Name : public testing::Test {};          \
                                                 \
  template <typename T>                          \
  using Name##Suite = Name<T>;                   \
                                                 \
  TYPED_TEST_SUITE_P(Name##Suite);               \
  TYPED_TEST_P(Name##Suite, Name##TypedTest)

// Defines a typed test based on a variant of an existing test class
#define CENTURION_DEFINE_TYPED_TEST_FROM_CLASS(Name, Class, Types) \
  template <typename T>                                            \
  using Name##Suite = Class<T>;                                    \
                                                                   \
  TYPED_TEST_SUITE_P(Name##Suite);                                 \
  TYPED_TEST_P(Name##Suite, Name##TypedTest)

// Registers a typed test, use the name and types provided to the above macros
#define CENTURION_REGISTER_TYPED_TEST(Name, Types)           \
  REGISTER_TYPED_TEST_SUITE_P(Name##Suite, Name##TypedTest); \
  INSTANTIATE_TYPED_TEST_SUITE_P(Name##s, Name##Suite, Types)
