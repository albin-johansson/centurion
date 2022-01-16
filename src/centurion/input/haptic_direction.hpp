#ifndef CENTURION_INPUT_HAPTIC_DIRECTION_HPP_
#define CENTURION_INPUT_HAPTIC_DIRECTION_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "../math.hpp"
#include "haptic_direction_type.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class haptic_direction
 *
 * \brief Represents a haptic direction, used by haptic effects.
 *
 * \since 5.2.0
 */
class haptic_direction final {
 public:
  using direction_type = basic_vector3<int32>;

  /**
   * \brief Creates a haptic direction of the specified type.
   *
   * \param type the type of the direction.
   *
   * \since 5.2.0
   */
  explicit haptic_direction(const haptic_direction_type type) noexcept { set_type(type); }

  /**
   * \brief Creates a haptic direction based on an `SDL_HapticDirection` instance.
   *
   * \param direction the direction that will be copied.
   *
   * \since 5.2.0
   */
  explicit haptic_direction(const SDL_HapticDirection& direction) noexcept
      : m_direction{direction}
  {}

  /**
   * \brief Sets the type of the direction.
   *
   * \param type the new type of the direction.
   *
   * \since 5.2.0
   */
  void set_type(const haptic_direction_type type) noexcept
  {
    m_direction.type = to_underlying(type);
  }

  /**
   * \brief Sets the value of direction.
   *
   * \param direction the new value of the direction.
   *
   * \since 5.2.0
   */
  void set_value(const direction_type& direction) noexcept
  {
    m_direction.dir[0] = direction.x;
    m_direction.dir[1] = direction.y;
    m_direction.dir[2] = direction.z;
  }

  /**
   * \brief Returns the type associated with the direction.
   *
   * \return the current type of the direction.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto type() const noexcept -> haptic_direction_type
  {
    return static_cast<haptic_direction_type>(m_direction.type);
  }

  /**
   * \brief Returns the value of the direction.
   *
   * \return the current value of the direction.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto value() const noexcept -> direction_type
  {
    return {m_direction.dir[0], m_direction.dir[1], m_direction.dir[2]};
  }

  /**
   * \brief Returns the internal representation of the direction.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto get() const noexcept -> const SDL_HapticDirection& { return m_direction; }

 private:
  SDL_HapticDirection m_direction{};
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_HAPTIC_DIRECTION_HPP_
