#ifndef CENTURION_VK_LIBRARY_HEADER
#define CENTURION_VK_LIBRARY_HEADER

#ifndef CENTURION_NO_VULKAN

#include <SDL.h>
#include <SDL_vulkan.h>

#include "../../misc/czstring.hpp"
#include "../../misc/exception.hpp"

/// \addtogroup video
/// \{

namespace cen::vk {

// TODO Centurion 6: document and test

class library final
{
 public:
  explicit library(const czstring path = nullptr)
  {
    const auto result = SDL_Vulkan_LoadLibrary(path);
    if (result == -1)
    {
      throw sdl_error{};
    }
  }

  library(const library&) = delete;
  library(library&&) = delete;

  auto operator=(const library&) -> library& = delete;
  auto operator=(library&&) -> library& = delete;

  ~library() noexcept
  {
    SDL_Vulkan_UnloadLibrary();
  }
};

}  // namespace cen::vk

/// \} End of group video

#endif  // CENTURION_NO_VULKAN
#endif  // CENTURION_VK_LIBRARY_HEADER
