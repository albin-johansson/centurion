#ifndef CENTURION_INPUT_HAPTIC_CONDITION_HPP_
#define CENTURION_INPUT_HAPTIC_CONDITION_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "../math.hpp"
#include "haptic_effect.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class haptic_condition
 *
 * \brief Represents an axes-based haptic effect.
 *
 * \note See the SDL documentation for `SDL_HapticCondition` for detailed documentation.
 *
 * \see SDL_HapticCondition
 *
 * \since 5.2.0
 */
class haptic_condition final : public haptic_effect<haptic_condition> {
 public:
  inline constexpr static bool hasDirection = false;
  inline constexpr static bool hasEnvelope = false;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \enum condition_type
   *
   * \brief Provides values that serve as identifiers for the different kinds of
   * "condition" haptic effects.
   *
   * \since 5.2.0
   */
  enum condition_type : uint32 {
    spring = SDL_HAPTIC_SPRING,     ///< Based on axes position.
    damper = SDL_HAPTIC_DAMPER,     ///< Based on axes velocity.
    inertia = SDL_HAPTIC_INERTIA,   ///< Based on axes acceleration.
    friction = SDL_HAPTIC_FRICTION  ///< Based on axes movement.
  };

  /**
   * \brief Creates a haptic "condition" effect.
   *
   * \param type the type of the effect.
   *
   * \since 5.2.0
   */
  explicit haptic_condition(const condition_type type = spring) noexcept
  {
    m_effect.condition = {};
    set_type(type);
  }

  /**
   * \brief Sets the type of the effect.
   *
   * \param type the type of the effect.
   *
   * \since 5.2.0
   */
  void set_type(const condition_type type) noexcept
  {
    representation().type = static_cast<uint16>(to_underlying(type));
  }

  /**
   * \brief Sets the effect level when the joystick is to the "positive" side.
   *
   * \param level the x-, y- and z-axis levels.
   *
   * \since 5.2.0
   */
  void set_joystick_positive_level(const basic_vector3<uint16>& level) noexcept
  {
    representation().right_sat[0] = level.x;
    representation().right_sat[1] = level.y;
    representation().right_sat[2] = level.z;
  }

  /**
   * \brief Sets the effect level when the joystick is to the "negative" side.
   *
   * \param level the x-, y- and z-axis levels.
   *
   * \since 5.2.0
   */
  void set_joystick_negative_level(const basic_vector3<uint16>& level) noexcept
  {
    representation().left_sat[0] = level.x;
    representation().left_sat[1] = level.y;
    representation().left_sat[2] = level.z;
  }

  /**
   * \brief Sets of quickly the force should increase towards the "positive"
   * side.
   *
   * \param rate the x-, y- and z-axis rates.
   *
   * \since 5.2.0
   */
  void set_force_rate_positive(const basic_vector3<int16>& rate) noexcept
  {
    representation().right_coeff[0] = rate.x;
    representation().right_coeff[1] = rate.y;
    representation().right_coeff[2] = rate.z;
  }

  /**
   * \brief Sets of quickly the force should increase towards the "negative"
   * side.
   *
   * \param rate the x-, y- and z-axis rates.
   *
   * \since 5.2.0
   */
  void set_force_rate_negative(const basic_vector3<int16>& rate) noexcept
  {
    representation().left_coeff[0] = rate.x;
    representation().left_coeff[1] = rate.y;
    representation().left_coeff[2] = rate.z;
  }

  /**
   * \brief Sets the size of the dead zone.
   *
   * \param size the x-, y- and z-axis sizes.
   *
   * \since 5.2.0
   */
  void set_deadband(const basic_vector3<uint16>& size) noexcept
  {
    representation().deadband[0] = size.x;
    representation().deadband[1] = size.y;
    representation().deadband[2] = size.z;
  }

  /**
   * \brief Sets the "center", i.e. the position of the dead zone.
   *
   * \param center the position of the dead zone.
   *
   * \since 5.2.0
   */
  void set_center(const basic_vector3<int16>& center) noexcept
  {
    representation().center[0] = center.x;
    representation().center[1] = center.y;
    representation().center[2] = center.z;
  }

  /**
   * \brief Returns the effect level when the joystick is to the "positive"
   * side.
   *
   * \return the positive side effect level.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto joystick_positive_level() const noexcept -> basic_vector3<uint16>
  {
    const auto& level = representation().right_sat;
    return {level[0], level[1], level[2]};
  }

  /**
   * \brief Returns the effect level when the joystick is to the "negative"
   * side.
   *
   * \return the negative side effect level.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto joystick_negative_level() const noexcept -> basic_vector3<uint16>
  {
    const auto& level = representation().left_sat;
    return {level[0], level[1], level[2]};
  }

  /**
   * \brief Returns how fast the force increases towards to the "positive" side.
   *
   * \return the positive side force increase rate.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto force_rate_positive() const noexcept -> basic_vector3<int16>
  {
    const auto& rate = representation().right_coeff;
    return {rate[0], rate[1], rate[2]};
  }

  /**
   * \brief Returns how fast the force increases towards to the "negative" side.
   *
   * \return the negative side force increase rate.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto force_rate_negative() const noexcept -> basic_vector3<int16>
  {
    const auto& rate = representation().left_coeff;
    return {rate[0], rate[1], rate[2]};
  }

  /**
   * \brief Returns the size of the dead zone.
   *
   * \return the size of the dead zone.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto deadband() const noexcept -> basic_vector3<uint16>
  {
    const auto& band = representation().deadband;
    return {band[0], band[1], band[2]};
  }

  /**
   * \brief Returns the position of the dead zone.
   *
   * \return the position of the dead zone.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto center() const noexcept -> basic_vector3<int16>
  {
    const auto& center = representation().center;
    return {center[0], center[1], center[2]};
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticCondition&
  {
    return m_effect.condition;
  }

  /**
   * \copydoc representation();
   */
  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticCondition&
  {
    return m_effect.condition;
  }
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_HAPTIC_CONDITION_HPP_
