#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/filesystem.hpp"

TEST(FileType, Values)
{
  ASSERT_EQ(SDL_RWOPS_UNKNOWN, to_underlying(cen::file_type::unknown));
  ASSERT_EQ(SDL_RWOPS_WINFILE, to_underlying(cen::file_type::win));
  ASSERT_EQ(SDL_RWOPS_STDFILE, to_underlying(cen::file_type::std));
  ASSERT_EQ(SDL_RWOPS_JNIFILE, to_underlying(cen::file_type::jni));
  ASSERT_EQ(SDL_RWOPS_MEMORY, to_underlying(cen::file_type::memory));
  ASSERT_EQ(SDL_RWOPS_MEMORY_RO, to_underlying(cen::file_type::memory_ro));
}

TEST(FileType, ToString)
{
  ASSERT_EQ("unknown", to_string(cen::file_type::unknown));
  ASSERT_EQ("win", to_string(cen::file_type::win));
  ASSERT_EQ("std", to_string(cen::file_type::std));
  ASSERT_EQ("jni", to_string(cen::file_type::jni));
  ASSERT_EQ("memory", to_string(cen::file_type::memory));
  ASSERT_EQ("memory_ro", to_string(cen::file_type::memory_ro));

  std::cout << "file_type::std == " << cen::file_type::std << '\n';
}