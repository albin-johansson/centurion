#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"
#include "video/vulkan.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(void*, SDL_Vulkan_GetVkGetInstanceProcAddr)
  FAKE_VALUE_FUNC(SDL_bool, SDL_Vulkan_CreateSurface, SDL_Window*, VkInstance, VkSurfaceKHR*)
  FAKE_VOID_FUNC(SDL_Vulkan_GetDrawableSize, SDL_Window*, int*, int*)
  FAKE_VALUE_FUNC(SDL_bool,
                  SDL_Vulkan_GetInstanceExtensions,
                  SDL_Window*,
                  unsigned*,
                  const char**)
}

class VulkanCoreTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_Vulkan_GetVkGetInstanceProcAddr)
    RESET_FAKE(SDL_Vulkan_CreateSurface)
    RESET_FAKE(SDL_Vulkan_GetDrawableSize)
    RESET_FAKE(SDL_Vulkan_GetInstanceExtensions)
  }
};

TEST_F(VulkanCoreTest, GetInstanceProcAddr)
{
  const auto* address [[maybe_unused]] = cen::vk::get_instance_proc_addr();
  ASSERT_EQ(1u, SDL_Vulkan_GetVkGetInstanceProcAddr_fake.call_count);
}

TEST_F(VulkanCoreTest, CreateSurface)
{
  std::array flags{Uint32{cen::window::vulkan}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, flags.data(), cen::isize(flags));

  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_Vulkan_CreateSurface, values.data(), cen::isize(values));

  VkInstance instance{};
  cen::window_handle window{nullptr};
  VkSurfaceKHR surface;

  ASSERT_EQ(cen::failure, cen::vk::create_surface(window, instance, &surface));
  ASSERT_EQ(cen::success, cen::vk::create_surface(window, instance, &surface));
  ASSERT_EQ(2u, SDL_Vulkan_CreateSurface_fake.call_count);
}

TEST_F(VulkanCoreTest, RequiredExtensions)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_Vulkan_GetInstanceExtensions, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::vk::required_extensions());
  ASSERT_TRUE(cen::vk::required_extensions());
}

TEST_F(VulkanCoreTest, DrawableSize)
{
  std::array flags{Uint32{cen::window::vulkan}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, flags.data(), cen::isize(flags));

  cen::window_handle window{nullptr};
  const auto size [[maybe_unused]] = cen::vk::drawable_size(window);
  ASSERT_EQ(1u, SDL_Vulkan_GetDrawableSize_fake.call_count);
}
