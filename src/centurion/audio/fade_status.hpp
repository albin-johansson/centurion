#ifndef CENTURION_FADE_STATUS_HEADER
#define CENTURION_FADE_STATUS_HEADER

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL_mixer.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup audio
/// \{

/**
 * \enum fade_status
 *
 * \brief Provides values that represent different fade playback states.
 *
 * \see `Mix_Fading`
 * \see `fade_status_count()`
 *
 * \since 3.0.0
 */
enum class fade_status
{
  none = MIX_NO_FADING,  ///< No currently fading music.
  in = MIX_FADING_IN,    ///< Currently fading in music.
  out = MIX_FADING_OUT   ///< Currently fading out music.
};

/**
 * \brief Returns the number of enumerators for the `fade_status` enum.
 *
 * \return the number of enumerators.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto fade_status_count() noexcept -> int
{
  return 3;
}

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied fade status.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(fade_status::in) == "in"`.
 *
 * \param status the fade status that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const fade_status status) -> std::string_view
{
  switch (status) {
    case fade_status::none:
      return "none";

    case fade_status::in:
      return "in";

    case fade_status::out:
      return "out";

    default:
      throw cen_error{"Did not recognize fade status!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a fade status enumerator.
 *
 * \param stream the output stream that will be used.
 * \param status the fade status that will be printed.
 *
 * \see `to_string(fade_status)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const fade_status status) -> std::ostream&
{
  return stream << to_string(status);
}

/// \} End of streaming

/// \name Fade status comparison operators
/// \{

/**
 * \brief Indicates whether or not the fading status values represent are the same.
 *
 * \param lhs the left-hand side fading status value.
 * \param rhs the right-hand side fading status value.
 *
 * \return `true` if the fading status values are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator==(const fade_status lhs, const Mix_Fading rhs) noexcept
    -> bool
{
  return static_cast<Mix_Fading>(lhs) == rhs;
}

/// \copydoc operator==(fade_status, Mix_Fading)
[[nodiscard]] constexpr auto operator==(const Mix_Fading lhs, const fade_status rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the fading status values represent aren't the same.
 *
 * \param lhs the left-hand side fading status value.
 * \param rhs the right-hand side fading status value.
 *
 * \return `true` if the fading status values aren't the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const fade_status lhs, const Mix_Fading rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(fade_status, Mix_Fading)
[[nodiscard]] constexpr auto operator!=(const Mix_Fading lhs, const fade_status rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \} End of fade status comparison operators

/// \} End of group audio

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_FADE_STATUS_HEADER
