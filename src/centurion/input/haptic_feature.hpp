#ifndef CENTURION_HAPTIC_FEATURE_HEADER
#define CENTURION_HAPTIC_FEATURE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum haptic_feature
 *
 * \brief Provides values that represent all of the haptic features.
 *
 * \since 5.2.0
 */
enum class haptic_feature : uint
{
  constant = SDL_HAPTIC_CONSTANT,
  sine = SDL_HAPTIC_SINE,
  left_right = SDL_HAPTIC_LEFTRIGHT,
  triangle = SDL_HAPTIC_TRIANGLE,
  sawtooth_up = SDL_HAPTIC_SAWTOOTHUP,
  sawtooth_down = SDL_HAPTIC_SAWTOOTHDOWN,
  ramp = SDL_HAPTIC_RAMP,
  spring = SDL_HAPTIC_SPRING,
  damper = SDL_HAPTIC_DAMPER,
  inertia = SDL_HAPTIC_INERTIA,
  friction = SDL_HAPTIC_FRICTION,
  custom = SDL_HAPTIC_CUSTOM,
  gain = SDL_HAPTIC_GAIN,
  autocenter = SDL_HAPTIC_AUTOCENTER,
  status = SDL_HAPTIC_STATUS,
  pause = SDL_HAPTIC_PAUSE
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied haptic feature.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(haptic_feature::spring) == "spring"`.
 *
 * \param feature the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const haptic_feature feature) -> std::string_view
{
  switch (feature) {
    case haptic_feature::constant:
      return "constant";

    case haptic_feature::sine:
      return "sine";

    case haptic_feature::left_right:
      return "left_right";

    case haptic_feature::triangle:
      return "triangle";

    case haptic_feature::sawtooth_up:
      return "sawtooth_up";

    case haptic_feature::sawtooth_down:
      return "sawtooth_down";

    case haptic_feature::ramp:
      return "ramp";

    case haptic_feature::spring:
      return "spring";

    case haptic_feature::damper:
      return "damper";

    case haptic_feature::inertia:
      return "inertia";

    case haptic_feature::friction:
      return "friction";

    case haptic_feature::custom:
      return "custom";

    case haptic_feature::gain:
      return "gain";

    case haptic_feature::autocenter:
      return "autocenter";

    case haptic_feature::status:
      return "status";

    case haptic_feature::pause:
      return "pause";

    default:
      throw cen_error{"Did not recognize haptic feature!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a haptic feature enumerator.
 *
 * \param stream the output stream that will be used.
 * \param feature the enumerator that will be printed.
 *
 * \see `to_string(haptic_feature)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const haptic_feature feature) -> std::ostream&
{
  return stream << to_string(feature);
}

/// \} End of streaming

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_HAPTIC_FEATURE_HEADER
