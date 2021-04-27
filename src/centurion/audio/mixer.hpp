#ifndef CENTURION_MIXER_HEADER
#define CENTURION_MIXER_HEADER

#include <SDL.h>
#include <SDL_mixer.h>

#include "../core/czstring.hpp"
#include "../core/result.hpp"
#include "../core/time.hpp"

namespace cen {

/// \addtogroup audio
/// \{

/// \name Sound fonts
/// \{

/**
 * \brief Sets the paths to the available SoundFont files.
 *
 * \param paths a string of SoundFont paths, separated by semicolons.
 *
 * \return `success` if the operation was successful; `failure` otherwise.
 *
 * \see `Mix_SetSoundFonts`
 *
 * \since 6.0.0
 */
inline auto set_sound_fonts(const czstring paths) noexcept -> result
{
  return Mix_SetSoundFonts(paths) != 0;
}

/**
 * \brief Returns a path to a SoundFont file.
 *
 * \return a path to a SoundFonts file; can be null.
 *
 * \see `Mix_GetSoundFonts`
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto get_sound_fonts() noexcept -> czstring
{
  return Mix_GetSoundFonts();
}

/// \} End of sound fonts

/// \name Callbacks
/// \{

using sound_font_visit_callback = int(SDLCALL*)(czstring, void*) noexcept;

/**
 * \brief Visits each available SoundFont path.
 *
 * \tparam T the type of the associated data.
 *
 * \param callable the callable that will be invoked for each SoundFont path.
 * \param data optional user data.
 *
 * \return `success` if the operation was successful; `failure` otherwise.
 *
 * \see `Mix_EachSoundFont`
 *
 * \since 6.0.0
 */
template <typename T = void>
auto each_sound_font(sound_font_visit_callback callable, T* data = nullptr) noexcept
    -> result
{
  return Mix_EachSoundFont(callable, static_cast<void*>(data)) != 0;
}

using channel_finished_callback = void(SDLCALL*)(int) noexcept;

/**
 * \brief Assigns a callback for when a channel finishes its playback.
 *
 * \param callback the callback that will be used; can safely be null to disable the
 * callback.
 *
 * \see `Mix_ChannelFinished`
 *
 * \since 6.0.0
 */
inline void on_channel_finished(channel_finished_callback callback) noexcept
{
  Mix_ChannelFinished(callback);
}

/// \} End of callbacks

/// \name Channel functions
/// \{

/**
 * \brief Changes the amount of channels managed by the mixer.
 *
 * \note The the channel count is decreased, the removed channels are stopped.
 *
 * \param count the total amount of channels managed by the mixer.
 *
 * \return the number of allocated channels.
 *
 * \see `Mix_AllocateChannels`
 *
 * \since 6.0.0
 */
inline auto allocate_channels(const int count) noexcept -> int
{
  return Mix_AllocateChannels(count);
}

/**
 * \brief Reserves a group of channels for the use of the application.
 *
 * \param count the desired amount of channels to be reserved.
 *
 * \return the number of reserved channels.
 *
 * \see `Mix_ReserveChannels`
 *
 * \since 6.0.0
 */
inline auto reserve_channels(const int count) noexcept -> int
{
  return Mix_ReserveChannels(count);
}

/**
 * \brief Sets a channel to stop playing after the specified amount of time.
 *
 * \param channel the channel that will be affected.
 * \param ms the duration of the expiration.
 *
 * \return `success` if the operation was successful; `failure` otherwise.
 *
 * \see `Mix_ExpireChannel`
 *
 * \since 6.0.0
 */
inline auto expire_channel(const int channel,
                           const milliseconds<int> ms) noexcept(noexcept(ms.count()))
    -> result
{
  return Mix_ExpireChannel(channel, ms.count()) != 0;
}

/**
 * \brief Removes the current expiration from the specified channel.
 *
 * \param channel the channel that will be affected.
 *
 * \return `success` if the operation was successful; `failure` otherwise.
 *
 * \since 6.0.0
 */
inline auto remove_expiration(const int channel) noexcept -> result
{
  return Mix_ExpireChannel(channel, -1) != 0;
}

/**
 * \brief Sets the group that a channel belongs to.
 *
 * \param channel the channel that will be affected.
 * \param group the group will be assigned to the channel.
 *
 * \return `success` if the group was assigned successfully; `failure` otherwise.
 *
 * \see `Mix_GroupChannel`
 *
 * \since 6.0.0
 */
inline auto set_channel_group(const int channel, const int group) noexcept -> result
{
  return Mix_GroupChannel(channel, group) == 1;
}

/**
 * \brief Resets the group that a channel is assigned to.
 *
 * \param channel the channel which reset to belong to the default channel group.
 *
 * \return `success` if the channel group was reset successfully; `failure` otherwise.
 *
 * \since 6.0.0
 */
inline auto reset_channel_group(const int channel) noexcept -> result
{
  return set_channel_group(channel, -1);
}

/// \} End of channel functions
/// \} End of group audio

}  // namespace cen

#endif  // CENTURION_MIXER_HEADER
