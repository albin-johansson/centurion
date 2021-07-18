#ifndef CENTURION_VK_LIBRARY_HEADER
#define CENTURION_VK_LIBRARY_HEADER

#ifndef CENTURION_NO_VULKAN

// clang-format off
#include "../../compiler/features.hpp"
// clang-format on

#include <SDL.h>
#include <SDL_vulkan.h>

#include "../../core/czstring.hpp"
#include "../../core/exception.hpp"

/// \addtogroup video
/// \{

namespace cen {

/**
 * \class vk_library
 *
 * \brief Responsible for loading and unloading a Vulkan library.
 *
 * \since 6.0.0
 */
class vk_library final
{
 public:
  /**
   * \brief Loads a Vulkan library.
   *
   * \param path optional file path to a Vulkan library; a null path indicates that the
   * default library will be used.
   */
  CENTURION_NODISCARD_CTOR explicit vk_library(const czstring path = nullptr)
  {
    if (SDL_Vulkan_LoadLibrary(path) == -1)
    {
      throw sdl_error{};
    }
  }

  vk_library(const vk_library&) = delete;
  vk_library(vk_library&&) = delete;

  auto operator=(const vk_library&) -> vk_library& = delete;
  auto operator=(vk_library&&) -> vk_library& = delete;

  ~vk_library() noexcept
  {
    SDL_Vulkan_UnloadLibrary();
  }
};

}  // namespace cen

/// \} End of group video

#endif  // CENTURION_NO_VULKAN
#endif  // CENTURION_VK_LIBRARY_HEADER
