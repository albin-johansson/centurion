#ifndef CENTURION_INPUT_HAPTIC_LEFT_RIGHT_HPP_
#define CENTURION_INPUT_HAPTIC_LEFT_RIGHT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "haptic_effect.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class haptic_left_right
 *
 * \brief Represents a haptic effect based on controlling the large and small
 * motors featured in many modern game controllers.
 *
 * \note See the SDL documentation for `SDL_HapticLeftRight` for detailed documentation.
 *
 * \see SDL_HapticLeftRight
 *
 * \since 5.2.0
 */
class haptic_left_right final : public haptic_effect<haptic_left_right> {
 public:
  inline constexpr static bool hasDirection = false;
  inline constexpr static bool hasEnvelope = false;
  inline constexpr static bool hasTrigger = false;
  inline constexpr static bool hasDelay = false;

  /**
   * \brief Creates a "left/right" haptic effect.
   *
   * \since 5.2.0
   */
  haptic_left_right() noexcept
  {
    m_effect.leftright = {};
    representation().type = SDL_HAPTIC_LEFTRIGHT;
  }

  /**
   * \brief Sets the magnitude of the large (low frequency) controller motor.
   *
   * \param magnitude the magnitude of the large motor.
   *
   * \since 5.2.0
   */
  void set_large_magnitude(const Uint16 magnitude) noexcept
  {
    representation().large_magnitude = magnitude;
  }

  /**
   * \brief Sets the magnitude of the small (high frequency) controller motor.
   *
   * \param magnitude the magnitude of the small motor.
   *
   * \since 5.2.0
   */
  void set_small_magnitude(const Uint16 magnitude) noexcept
  {
    representation().small_magnitude = magnitude;
  }

  /**
   * \brief Returns the magnitude of the large (low frequency) controller motor.
   *
   * \return the magnitude of the large motor.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto large_magnitude() const noexcept -> Uint16
  {
    return representation().large_magnitude;
  }

  /**
   * \brief Returns the magnitude of the small (high frequency) controller
   * motor.
   *
   * \return the magnitude of the small motor.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto small_magnitude() const noexcept -> Uint16
  {
    return representation().small_magnitude;
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticLeftRight&
  {
    return m_effect.leftright;
  }

  /**
   * \copydoc representation();
   */
  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticLeftRight&
  {
    return m_effect.leftright;
  }
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_HAPTIC_LEFT_RIGHT_HPP_
