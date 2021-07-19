#include "filesystem/file_type.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"

TEST(FileType, Values)
{
  ASSERT_EQ(SDL_RWOPS_UNKNOWN, cen::to_underlying(cen::file_type::unknown));
  ASSERT_EQ(SDL_RWOPS_WINFILE, cen::to_underlying(cen::file_type::win32));
  ASSERT_EQ(SDL_RWOPS_STDFILE, cen::to_underlying(cen::file_type::stdio));
  ASSERT_EQ(SDL_RWOPS_JNIFILE, cen::to_underlying(cen::file_type::jni));
  ASSERT_EQ(SDL_RWOPS_MEMORY, cen::to_underlying(cen::file_type::memory));
  ASSERT_EQ(SDL_RWOPS_MEMORY_RO, cen::to_underlying(cen::file_type::memory_ro));
}

TEST(FileType, ToString)
{
  ASSERT_EQ("unknown", cen::to_string(cen::file_type::unknown));
  ASSERT_EQ("win32", cen::to_string(cen::file_type::win32));
  ASSERT_EQ("stdio", cen::to_string(cen::file_type::stdio));
  ASSERT_EQ("jni", cen::to_string(cen::file_type::jni));
  ASSERT_EQ("memory", cen::to_string(cen::file_type::memory));
  ASSERT_EQ("memory_ro", cen::to_string(cen::file_type::memory_ro));

  std::cout << "File type example: " << cen::file_type::win32 << '\n';
}
