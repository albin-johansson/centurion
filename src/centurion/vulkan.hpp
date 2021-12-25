#ifndef CENTURION_VULKAN_HPP_
#define CENTURION_VULKAN_HPP_

#ifndef CENTURION_NO_VULKAN

#include <SDL.h>
#include <SDL_vulkan.h>

#include <cassert>   // assert
#include <optional>  // optional, nullopt
#include <vector>    // vector

#include "common.hpp"
#include "features.hpp"
#include "math.hpp"
#include "window.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \class vk_library
 *
 * \brief Responsible for loading and unloading a Vulkan library.
 *
 * \since 6.0.0
 */
class vk_library final {
 public:
  /**
   * \brief Loads a Vulkan library.
   *
   * \param path optional file path to a Vulkan library; a null path indicates that the
   * default library will be used.
   */
  CENTURION_NODISCARD_CTOR explicit vk_library(const char* path = nullptr)
  {
    if (SDL_Vulkan_LoadLibrary(path) == -1) {
      throw SDLError{};
    }
  }

  ~vk_library() noexcept { SDL_Vulkan_UnloadLibrary(); }

  CENTURION_DISABLE_COPY(vk_library)
  CENTURION_DISABLE_MOVE(vk_library)
};

/// \} End of group video

namespace vk {

/// \addtogroup video
/// \{

/**
 * \brief Returns the address of the `vkGetInstanceProcAddr` function.
 *
 * \return the address of the `vkGetInstanceProcAddr` function.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto get_instance_proc_addr() noexcept -> void*
{
  return SDL_Vulkan_GetVkGetInstanceProcAddr();
}

/**
 * \brief Creates a rendering surface for a Vulkan window.
 *
 * \pre `window` must be a Vulkan window.
 *
 * \tparam T the ownership semantics of the window.
 *
 * \param window the Vulkan window.
 * \param instance the current Vulkan instance.
 * \param[out] outSurface the handle that will receive the handle of the created surface.
 *
 * \return `success` if the surface was succesfully created; `failure` otherwise.
 *
 * \since 6.0.0
 */
template <typename T>
auto create_surface(BasicWindow<T>& window,
                    VkInstance instance,
                    VkSurfaceKHR* outSurface) noexcept -> Result
{
  assert(window.IsVulkan());
  return SDL_Vulkan_CreateSurface(window.get(), instance, outSurface) == SDL_TRUE;
}

/**
 * \brief Returns the extensions required to create a Vulkan surface.
 *
 * \return the required Vulkan extensions; `std::nullopt` if something goes wrong.
 *
 * \since 6.0.0
 */
inline auto required_extensions() -> std::optional<std::vector<const char*>>
{
  uint count{};
  if (!SDL_Vulkan_GetInstanceExtensions(nullptr, &count, nullptr)) {
    return std::nullopt;
  }

  std::vector<const char*> names(count);
  if (!SDL_Vulkan_GetInstanceExtensions(nullptr, &count, names.data())) {
    return std::nullopt;
  }

  return names;
}

/**
 * \brief Returns the size of the drawable surface associated with the window.
 *
 * \pre `window` must be a Vulkan window.
 *
 * \tparam T the ownership semantics of the window.
 *
 * \param window the Vulkan window that will be queried.
 *
 * \return the size of the window drawable.
 *
 * \since 6.0.0
 */
template <typename T>
[[nodiscard]] auto drawable_size(const BasicWindow<T>& window) noexcept -> Area
{
  assert(window.IsVulkan());

  int width{};
  int height{};
  SDL_Vulkan_GetDrawableSize(window.get(), &width, &height);

  return {width, height};
}

/// \} End of group video

}  // namespace vk
}  // namespace cen

#endif  // CENTURION_NO_VULKAN
#endif  // CENTURION_VULKAN_HPP_
