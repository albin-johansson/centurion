#ifndef CENTURION_CHANNELS_HEADER
#define CENTURION_CHANNELS_HEADER

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL.h>
#include <SDL_mixer.h>

#include <optional>  // optional

#include "../core/result.hpp"
#include "../core/time.hpp"

namespace cen {

/// \addtogroup audio
/// \{

using channel_index = int;

using group_index = int;

using channel_finished_callback = void(SDLCALL*)(channel_index) noexcept;

/// \} End of group audio

/// \namespace cen::channels
/// \brief Contains functions related to audio channels.
/// \ingroup audio
/// \since 6.0.0
namespace channels {

/// \addtogroup audio
/// \{

/// \name Channel functions
/// \{

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
inline void on_finished(channel_finished_callback callback) noexcept
{
  Mix_ChannelFinished(callback);
}

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
inline auto allocate(const int count) noexcept -> int
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
inline auto reserve(const int count) noexcept -> int
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
inline auto expire(const channel_index channel,
                   const milliseconds<int> ms) noexcept(noexcept(ms.count())) -> result
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
inline auto remove_expiration(const channel_index channel) noexcept -> result
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
inline auto set_group(const channel_index channel, const group_index group) noexcept -> result
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
inline auto reset_group(const channel_index channel) noexcept -> result
{
  return set_group(channel, -1);
}

/**
 * \brief Returns the number of channels in the specified group.
 *
 * \note If the supplied group is `-1`, then this function returns the total amount of
 * channels.
 *
 * \param group the index of the channel group that will be checked.
 *
 * \return the number of channels in the group.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto group_count(const group_index group = -1) noexcept -> int
{
  return Mix_GroupCount(group);
}

/**
 * \brief Returns the first available channel in the specified group.
 *
 * \param group the channel group that will be checked.
 *
 * \return an available channel index in the specified group; `std::nullopt` if no channel
 * was available.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto first_available(const group_index group) noexcept
    -> std::optional<channel_index>
{
  const auto channel = Mix_GroupAvailable(group);
  if (channel != -1) {
    return channel;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the most recently playing channel in the specified group.
 *
 * \param group the channel group that will be checked.
 *
 * \return the most recently playing channel in the group; `std::nullopt` if it couldn't
 * be determined.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto most_recent(const group_index group) -> std::optional<channel_index>
{
  const auto channel = Mix_GroupNewer(group);
  if (channel != -1) {
    return channel;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the oldest playing channel in the specified group.
 *
 * \param group the channel group that will be checked.
 *
 * \return the oldest playing channel in the group; `std::nullopt` if it couldn't be
 * determined.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto oldest(const group_index group) -> std::optional<channel_index>
{
  const auto channel = Mix_GroupOldest(group);
  if (channel != -1) {
    return channel;
  }
  else {
    return std::nullopt;
  }
}

/// \} End of channel functions

/// \} End of group audio

}  // namespace channels

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_CHANNELS_HEADER
