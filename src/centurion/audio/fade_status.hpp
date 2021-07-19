#ifndef CENTURION_FADE_STATUS_HEADER
#define CENTURION_FADE_STATUS_HEADER

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL_mixer.h>

#include <ostream>  // ostream
#include <string>   // string

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup audio
/// \{

/**
 * \enum fade_status
 *
 * \brief Provides values that represent different fade playback states.
 *
 * \since 3.0.0
 *
 * \see `Mix_Fading`
 */
enum class fade_status
{
  none = MIX_NO_FADING,  ///< No currently fading music.
  in = MIX_FADING_IN,    ///< Currently fading in music.
  out = MIX_FADING_OUT   ///< Currently fading out music.
};

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
[[nodiscard]] inline auto to_string(const fade_status status) -> std::string
{
  switch (status)
  {
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
[[nodiscard]] constexpr auto operator==(const fade_status lhs,
                                        const Mix_Fading rhs) noexcept -> bool
{
  return static_cast<Mix_Fading>(lhs) == rhs;
}

/// \copydoc operator==(fade_status, Mix_Fading)
[[nodiscard]] constexpr auto operator==(const Mix_Fading lhs,
                                        const fade_status rhs) noexcept -> bool
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
[[nodiscard]] constexpr auto operator!=(const fade_status lhs,
                                        const Mix_Fading rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(fade_status, Mix_Fading)
[[nodiscard]] constexpr auto operator!=(const Mix_Fading lhs,
                                        const fade_status rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of fade status comparison operators

/// \} End of group audio

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_FADE_STATUS_HEADER