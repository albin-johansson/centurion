#ifndef CENTURION_HAPTIC_RAMP_HEADER
#define CENTURION_HAPTIC_RAMP_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "haptic_effect.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class haptic_ramp
 *
 * \brief Represents a linear or quadratic haptic effect.
 *
 * \note See the SDL documentation for `SDL_HapticRamp` for more detailed documentation.
 *
 * \see SDL_HapticRamp
 *
 * \since 5.2.0
 */
class haptic_ramp final : public haptic_effect<haptic_ramp>
{
 public:
  inline constexpr static bool hasDirection = true;
  inline constexpr static bool hasEnvelope = true;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \brief Creates a haptic ramp effect.
   *
   * \since 5.2.0
   */
  haptic_ramp() noexcept
  {
    m_effect.ramp = {};
    representation().type = SDL_HAPTIC_RAMP;
  }

  /**
   * \brief Sets the initial strength level.
   *
   * \param start the initial strength level.
   *
   * \since 5.2.0
   */
  void set_start_strength(const i16 start) noexcept
  {
    representation().start = start;
  }

  /**
   * \brief Sets the strength level at the end of the effect.
   *
   * \param end the strength level at the end of the effect.
   *
   * \since 5.2.0
   */
  void set_end_strength(const i16 end) noexcept
  {
    representation().end = end;
  }

  /**
   * \brief Returns the initial strength level.
   *
   * \return the initial strength level.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto start_strength() const noexcept -> i16
  {
    return representation().start;
  }

  /**
   * \brief Returns the strength level at the end of the effect.
   *
   * \return the final strength level.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto end_strength() const noexcept -> i16
  {
    return representation().end;
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticRamp&
  {
    return m_effect.ramp;
  }

  /// \copydoc representation();
  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticRamp&
  {
    return m_effect.ramp;
  }
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_HAPTIC_RAMP_HEADER
