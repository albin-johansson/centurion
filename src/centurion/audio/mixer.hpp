#ifndef CENTURION_MIXER_HEADER
#define CENTURION_MIXER_HEADER

#include <SDL.h>
#include <SDL_mixer.h>

#include "../core/czstring.hpp"
#include "../core/time.hpp"

namespace cen {

// TODO Centurion 6: Document and test

/// \addtogroup audio
/// \{

/// \name Sound fonts
/// \{

inline auto set_sound_fonts(const czstring fonts) noexcept -> bool
{
  return Mix_SetSoundFonts(fonts) != 0;
}

[[nodiscard]] inline auto get_sound_fonts() noexcept -> czstring
{
  return Mix_GetSoundFonts();
}

/// \} End of sound fonts

/// \name Callbacks
/// \{

using sound_font_visit_callback = int(SDLCALL*)(czstring, void*) noexcept;

template <typename T = void>
auto each_sound_font(sound_font_visit_callback callable,
                     T* data = nullptr) noexcept -> bool
{
  return Mix_EachSoundFont(callable, static_cast<void*>(data)) != 0;
}

using channel_finished_callback = void(SDLCALL*)(int) noexcept;

inline void on_channel_finished(channel_finished_callback callback) noexcept
{
  Mix_ChannelFinished(callback);
}

/// \} End of callbacks

/// \name Channel functions
/// \{

inline auto allocate_channels(const int count) noexcept -> int
{
  return Mix_AllocateChannels(count);
}

inline auto reserve_channels(const int count) noexcept -> int
{
  return Mix_ReserveChannels(count);
}

// clang-format off

inline auto expire_channel(const int channel,
                           const milliseconds<int> ms) noexcept(noexcept(ms.count()))
    -> bool
{
  return Mix_ExpireChannel(channel, ms.count()) != 0;
}

// clang-format on

inline auto set_channel_group(const int channel, const int group) noexcept
    -> bool
{
  return Mix_GroupChannel(channel, group) == 1;
}

inline auto reset_channel_group(const int channel) noexcept -> bool
{
  return set_channel_group(channel, -1);
}

// TODO Mix_GroupChannels();

/// \} End of channel functions

/// \} End of group audio

}  // namespace cen

#endif  // CENTURION_MIXER_HEADER
