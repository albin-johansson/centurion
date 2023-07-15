/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_VIDEO_VULKAN_HPP_
#define CENTURION_VIDEO_VULKAN_HPP_

#include <cassert>  // assert
#include <vector>   // vector

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <centurion/common/errors.hpp>
#include <centurion/common/macros.hpp>
#include <centurion/common/primitives.hpp>

namespace cen {

class VulkanLibrary final {
 public:
  CEN_CANNOT_COPY(VulkanLibrary);
  CEN_CANNOT_MOVE(VulkanLibrary);

  [[nodiscard]] explicit VulkanLibrary(const char* library_path = nullptr)
  {
    if (SDL_Vulkan_LoadLibrary(library_path) != 0) {
      throw SDLError {};
    }
  }

  ~VulkanLibrary() noexcept { SDL_Vulkan_UnloadLibrary(); }
};

namespace vk {

[[nodiscard]] inline auto get_required_instance_extensions() -> std::vector<const char*>
{
  uint extension_count = 0;
  if (!SDL_Vulkan_GetInstanceExtensions(&extension_count, nullptr)) {
    throw SDLError {};
  }

  std::vector<const char*> extensions;
  extensions.resize(static_cast<usize>(extension_count));

  if (!SDL_Vulkan_GetInstanceExtensions(&extension_count, extensions.data())) {
    throw SDLError {};
  }

  return extensions;
}

[[nodiscard]] inline auto make_surface(SDL_Window* window, VkInstance instance)
    -> VkSurfaceKHR
{
  assert(window);
  assert(instance);

  VkSurfaceKHR surface = nullptr;
  if (SDL_Vulkan_CreateSurface(window, instance, &surface)) {
    return surface;
  }
  else {
    throw SDLError {};
  }
}

}  // namespace vk
}  // namespace cen

#endif  // CENTURION_VIDEO_VULKAN_HPP_
