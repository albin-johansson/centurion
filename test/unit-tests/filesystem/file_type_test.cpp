#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "filesystem/file.hpp"

TEST(FileType, Values)
{
  ASSERT_EQ(SDL_RWOPS_UNKNOWN, cen::ToUnderlying(cen::FileType::Unknown));
  ASSERT_EQ(SDL_RWOPS_WINFILE, cen::ToUnderlying(cen::FileType::Win));
  ASSERT_EQ(SDL_RWOPS_STDFILE, cen::ToUnderlying(cen::FileType::Std));
  ASSERT_EQ(SDL_RWOPS_JNIFILE, cen::ToUnderlying(cen::FileType::Jni));
  ASSERT_EQ(SDL_RWOPS_MEMORY, cen::ToUnderlying(cen::FileType::Memory));
  ASSERT_EQ(SDL_RWOPS_MEMORY_RO, cen::ToUnderlying(cen::FileType::MemoryReadOnly));
}
