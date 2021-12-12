#ifndef CENTURION_INPUT_HAPTIC_CONSTANT_HPP_
#define CENTURION_INPUT_HAPTIC_CONSTANT_HPP_

#include <SDL.h>

#include "haptic_effect.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class haptic_constant
 *
 * \brief Represents a haptic effect that applies a constant force in some direction.
 *
 * \note See the SDL documentation for `SDL_HapticConstant` for  more detailed
 * documentation.
 *
 * \see SDL_HapticConstant
 *
 * \since 5.2.0
 */
class haptic_constant final : public haptic_effect<haptic_constant> {
 public:
  inline constexpr static bool hasDirection = true;
  inline constexpr static bool hasEnvelope = true;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \brief Creates a constant haptic effect.
   *
   * \since 5.2.0
   */
  haptic_constant() noexcept
  {
    m_effect.constant = {};
    representation().type = SDL_HAPTIC_CONSTANT;
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticConstant&
  {
    return m_effect.constant;
  }

  /**
   * \copydoc representation();
   */
  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticConstant&
  {
    return m_effect.constant;
  }
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_HAPTIC_CONSTANT_HPP_
