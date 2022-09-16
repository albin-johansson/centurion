/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

/// Responsible for loading and unloading a Vulkan library.
class vk_library final
{
 public:
  CENTURION_DISABLE_COPY(vk_library)
  CENTURION_DISABLE_MOVE(vk_library)

  CENTURION_NODISCARD_CTOR explicit vk_library(const char* path = nullptr)
  {
    if (SDL_Vulkan_LoadLibrary(path) == -1) {
      throw sdl_error{};
    }
  }

  ~vk_library() noexcept { SDL_Vulkan_UnloadLibrary(); }
};

namespace vk {

/// Returns the address of the vkGetInstanceProcAddr function.
[[nodiscard]] inline auto get_instance_proc_addr() noexcept -> void*
{
  return SDL_Vulkan_GetVkGetInstanceProcAddr();
}

template <typename T>
auto make_surface(basic_window<T>& window,
                  VkInstance instance,
                  VkSurfaceKHR* outSurface) noexcept -> result
{
  assert(window.is_vulkan());
  return SDL_Vulkan_CreateSurface(window.get(), instance, outSurface) == SDL_TRUE;
}

/// Returns the extensions required to create a Vulkan surface.
inline auto required_extensions() -> maybe<std::vector<const char*>>
{
  uint count{};
  if (!SDL_Vulkan_GetInstanceExtensions(nullptr, &count, nullptr)) {
    return nothing;
  }

  std::vector<const char*> names(count);
  if (!SDL_Vulkan_GetInstanceExtensions(nullptr, &count, names.data())) {
    return nothing;
  }

  return names;
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

}  // namespace vk
}  // namespace cen

#endif  // CENTURION_NO_VULKAN
#endif  // CENTURION_VULKAN_HPP_
