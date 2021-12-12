#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core/common.hpp"
#include "core_mocks.hpp"
#include "video/vulkan.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_Vulkan_LoadLibrary, const char*)
  FAKE_VOID_FUNC(SDL_Vulkan_UnloadLibrary)
}

class VulkanLibraryTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_Vulkan_LoadLibrary)
    RESET_FAKE(SDL_Vulkan_UnloadLibrary)
  }
};

TEST_F(VulkanLibraryTest, Initialization)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_Vulkan_LoadLibrary, values.data(), cen::isize(values));

  ASSERT_THROW(cen::vk_library{}, cen::SDLError);
  ASSERT_NO_THROW(cen::vk_library{});
  ASSERT_EQ(2u, SDL_Vulkan_LoadLibrary_fake.call_count);
}
