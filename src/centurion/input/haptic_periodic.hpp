#ifndef CENTURION_HAPTIC_PERIODIC_HEADER
#define CENTURION_HAPTIC_PERIODIC_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "../core/time.hpp"
#include "../core/to_underlying.hpp"
#include "haptic_effect.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class haptic_periodic
 *
 * \brief Represents a wave-shaped haptic effect that repeats itself over time.
 *
 * \note See the SDL documentation for `SDL_HapticPeriodic` for detailed documentation.
 *
 * \see SDL_HapticPeriodic
 *
 * \since 5.2.0
 */
class haptic_periodic final : public haptic_effect<haptic_periodic>
{
 public:
  inline constexpr static bool hasDirection = true;
  inline constexpr static bool hasEnvelope = true;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \enum periodic_type
   *
   * \brief Provides values that serve as identifiers for the different kinds of
   * "periodic" haptic effects.
   *
   * \since 5.2.0
   */
  enum periodic_type : u16
  {
    sine = SDL_HAPTIC_SINE,
    left_right = SDL_HAPTIC_LEFTRIGHT,
    triangle = SDL_HAPTIC_TRIANGLE,
    sawtooth_up = SDL_HAPTIC_SAWTOOTHUP,
    sawtooth_down = SDL_HAPTIC_SAWTOOTHDOWN
  };

  /**
   * \brief Creates a periodic haptic effect.
   *
   * \since 5.2.0
   */
  explicit haptic_periodic(const periodic_type type = sine) noexcept
  {
    m_effect.periodic = {};
    set_type(type);
  }

  /**
   * \brief Sets the type of the effect.
   *
   * \param type the periodic effect type.
   *
   * \since 5.2.0
   */
  void set_type(const periodic_type type) noexcept
  {
    representation().type = to_underlying(type);
  }

  /**
   * \brief Sets the period of the wave.
   *
   * \param period the period duration of the wave.
   *
   * \since 5.2.0
   */
  void set_period(const milliseconds<u16> period) noexcept(noexcept(period.count()))
  {
    representation().period = period.count();
  }

  /**
   * \brief Sets the magnitude (peak value) of the wave.
   *
   * \note If the supplied magnitude is negative, that is interpreted as an extra phase
   * shift of 180 degrees.
   *
   * \param magnitude the magnitude of the wave, can be negative.
   *
   * \since 5.2.0
   */
  void set_magnitude(const i16 magnitude) noexcept
  {
    representation().magnitude = magnitude;
  }

  /**
   * \brief Sets the mean value of the wave.
   *
   * \param mean the mean value of the wave.
   *
   * \since 5.2.0
   */
  void set_mean(const i16 mean) noexcept
  {
    representation().offset = mean;
  }

  /**
   * \brief Sets the phase shift.
   *
   * \param shift the positive phase shift, interpreted as hundredths of a degree.
   *
   * \since 5.2.0
   */
  void set_phase_shift(const u16 shift) noexcept
  {
    representation().phase = shift;
  }

  /**
   * \brief Returns the current period of the wave.
   *
   * \return the period of the wave.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto period() const -> milliseconds<u16>
  {
    return milliseconds<u16>{representation().period};
  }

  /**
   * \brief Returns the current magnitude (peak value) of the wave.
   *
   * \return the magnitude of the wave.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto magnitude() const noexcept -> i16
  {
    return representation().magnitude;
  }

  /**
   * \brief Returns the current mean value of the wave.
   *
   * \return the mean value of the wave.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto mean() const noexcept -> i16
  {
    return representation().offset;
  }

  /**
   * \brief Returns the current positive phase shift of the wave.
   *
   * \return the positive phase shift of the wave, in hundredths of a degree.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto phase_shift() const noexcept -> u16
  {
    return representation().phase;
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticPeriodic&
  {
    return m_effect.periodic;
  }

  /// \copydoc representation();
  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticPeriodic&
  {
    return m_effect.periodic;
  }
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_HAPTIC_PERIODIC_HEADER
