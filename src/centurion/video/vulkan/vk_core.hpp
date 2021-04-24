#ifndef CENTURION_VULKAN_HEADER
#define CENTURION_VULKAN_HEADER

#ifndef CENTURION_NO_VULKAN

#include <SDL.h>
#include <SDL_vulkan.h>

#include <cassert>  // assert
#include <memory>   // unique_ptr

#include "../../core/czstring.hpp"
#include "../window.hpp"

/// \addtogroup video
/// \{

/**
 * \namespace cen::vk
 *
 * \brief Contains Vulkan-related components.
 *
 * \since 6.0.0
 */
namespace cen::vk {

// TODO Centurion 6: document and test

[[nodiscard]] inline auto get_instance_proc_addr() noexcept -> void*
{
  return SDL_Vulkan_GetVkGetInstanceProcAddr();
}

template <typename T>
auto create_surface(basic_window<T>& window,
                    VkInstance instance,
                    VkSurfaceKHR* outSurface) noexcept -> bool
{
  assert(window.is_vulkan());
  return SDL_Vulkan_CreateSurface(window.get(), instance, outSurface) == SDL_TRUE;
}

template <typename T>
auto get_extensions(basic_window<T>& window,
                    unsigned* outCount,
                    czstring* outNames) noexcept -> bool
{
  assert(window.is_vulkan());
  return SDL_Vulkan_GetInstanceExtensions(window.get(), outCount, outNames) == SDL_TRUE;
}

template <typename T>
[[nodiscard]] auto drawable_size(const basic_window<T>& window) noexcept -> iarea
{
  assert(window.is_vulkan());

  int width{};
  int height{};

  SDL_Vulkan_GetDrawableSize(window.get(), &width, &height);

  return {width, height};
}

}  // namespace cen::vk

/// \} End of group video

#endif  // CENTURION_NO_VULKAN
#endif  // CENTURION_VULKAN_HEADER
