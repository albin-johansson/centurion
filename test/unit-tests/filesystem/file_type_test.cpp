#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "filesystem/file.hpp"

TEST(FileType, Values)
{
  ASSERT_EQ(SDL_RWOPS_UNKNOWN, cen::to_underlying(cen::FileType::Unknown));
  ASSERT_EQ(SDL_RWOPS_WINFILE, cen::to_underlying(cen::FileType::Win));
  ASSERT_EQ(SDL_RWOPS_STDFILE, cen::to_underlying(cen::FileType::Std));
  ASSERT_EQ(SDL_RWOPS_JNIFILE, cen::to_underlying(cen::FileType::Jni));
  ASSERT_EQ(SDL_RWOPS_MEMORY, cen::to_underlying(cen::FileType::Memory));
  ASSERT_EQ(SDL_RWOPS_MEMORY_RO, cen::to_underlying(cen::FileType::MemoryReadOnly));
}
