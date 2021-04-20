#ifndef CENTURION_ANDROID_HINTS_HEADER
#define CENTURION_ANDROID_HINTS_HEADER

#include <SDL.h>

#include "../core/czstring.hpp"
#include "../detail/hints_impl.hpp"

/// \addtogroup configuration
/// \{

namespace cen::hint::android {

struct block_on_pause final : detail::bool_hint<block_on_pause>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_ANDROID_BLOCK_ON_PAUSE;
  }
};

struct trap_back_button final : detail::bool_hint<trap_back_button>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_ANDROID_TRAP_BACK_BUTTON;
  }
};

struct apk_expansion_main_file_version final
    : detail::int_hint<apk_expansion_main_file_version>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION;
  }
};

struct apk_expansion_patch_file_version final
    : detail::int_hint<apk_expansion_patch_file_version>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION;
  }
};

#if SDL_VERSION_ATLEAST(2, 0, 14)

struct pause_background_audio final : detail::bool_hint<pause_background_audio>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_ANDROID_BLOCK_ON_PAUSE_PAUSEAUDIO;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen::hint::android

/// \} End of group configuration

#endif  // CENTURION_ANDROID_HINTS_HEADER