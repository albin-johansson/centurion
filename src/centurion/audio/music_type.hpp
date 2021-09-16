#ifndef CENTURION_MUSIC_TYPE_HEADER
#define CENTURION_MUSIC_TYPE_HEADER

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL_mixer.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup audio
/// \{

/**
 * \enum music_type
 *
 * \brief Provides values that represent different supported music types.
 *
 * \see `Mix_MusicType`
 * \see `music_type_count()`
 *
 * \since 3.0.0
 */
enum class music_type
{
  unknown = MUS_NONE,
  mp3 = MUS_MP3,
  wav = MUS_WAV,
  ogg = MUS_OGG,
  mod = MUS_MOD,
  midi = MUS_MID,
  cmd = MUS_CMD,
  flac = MUS_FLAC,
  opus = MUS_OPUS
};

/**
 * \brief Returns the number of enumerators for the `music_type` enum.
 *
 * \return the number of enumerators.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto music_type_count() noexcept -> int
{
  return 9;
}

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied music type.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(music_type::mp3) == "mp3"`.
 *
 * \param type the music type that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const music_type type) -> std::string_view
{
  switch (type) {
    case music_type::unknown:
      return "unknown";

    case music_type::mp3:
      return "mp3";

    case music_type::wav:
      return "wav";

    case music_type::ogg:
      return "ogg";

    case music_type::mod:
      return "mod";

    case music_type::midi:
      return "midi";

    case music_type::cmd:
      return "cmd";

    case music_type::flac:
      return "flac";

    case music_type::opus:
      return "opus";

    default:
      throw cen_error{"Did not recognize music type!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a music type enumerator.
 *
 * \param stream the output stream that will be used.
 * \param type the music type that will be printed.
 *
 * \see `to_string(music_type)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const music_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \} End of streaming

/// \name Music type comparison operators
/// \{

/**
 * \brief Indicates whether or not the music type values are the same.
 *
 * \param lhs the left-hand side music type value.
 * \param rhs the right-hand side music type value.
 *
 * \return `true` if the music type values are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator==(const music_type lhs, const Mix_MusicType rhs) noexcept
    -> bool
{
  return static_cast<Mix_MusicType>(lhs) == rhs;
}

/// \copydoc operator==(music_type, Mix_MusicType)
[[nodiscard]] constexpr auto operator==(const Mix_MusicType lhs, const music_type rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the music type values aren't the same.
 *
 * \param lhs the left-hand side music type value.
 * \param rhs the right-hand side music type value.
 *
 * \return `true` if the music type values aren't the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const music_type lhs, const Mix_MusicType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(music_type, Mix_MusicType)
[[nodiscard]] constexpr auto operator!=(const Mix_MusicType lhs, const music_type rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \} End of music type comparison operators

/// \} End of group audio

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_MUSIC_TYPE_HEADER
