#ifndef CENTURION_INPUT_HAPTIC_CUSTOM_HPP_
#define CENTURION_INPUT_HAPTIC_CUSTOM_HPP_

#include <SDL.h>

#include <cassert>  // assert

#include "../common.hpp"
#include "../detail/stdlib.hpp"
#include "haptic_effect.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class haptic_custom
 *
 * \brief Represents a custom haptic effect, similar to a periodic effect.
 *
 * \note See the SDL documentation for `SDL_HapticCustom` for detailed documentation.
 *
 * \see SDL_HapticCustom
 *
 * \since 5.2.0
 */
class haptic_custom final : public haptic_effect<haptic_custom> {
 public:
  inline constexpr static bool hasDirection = true;
  inline constexpr static bool hasEnvelope = true;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \brief Creates a haptic custom effect.
   *
   * \since 5.2.0
   */
  haptic_custom() noexcept
  {
    m_effect.custom = {};
    representation().type = SDL_HAPTIC_CUSTOM;
  }

  /**
   * \brief Sets the number of axes that are used.
   *
   * \pre `count` must be greater than zero.
   *
   * \param count the number of axes that will be used.
   *
   * \since 5.2.0
   */
  void set_axis_count(const Uint8 count) noexcept
  {
    assert(count > 0);
    representation().channels = detail::max(Uint8{1}, count);
  }

  // clang-format off

  /**
   * \brief Sets the duration of the sample periods.
   *
   * \param period duration of sample periods.
   *
   * \since 5.2.0
   */
  void set_sample_period(const U16_Millis period) noexcept(noexcept(period.count()))
  {
    representation().period = period.count();
  }

  // clang-format on

  /**
   * \brief Sets the number of samples.
   *
   * \param count the number of samples.
   *
   * \since 5.2.0
   */
  void set_sample_count(const Uint16 count) noexcept { representation().samples = count; }

  /**
   * \brief Sets the associated custom data.
   *
   * \note The data must be allocated and managed by you.
   *
   * \details The data should consist of `sample_count() * axis_count()` sample items.
   *
   * \param data a pointer to the custom sample data.
   *
   * \since 5.2.0
   */
  void set_data(Uint16* data) noexcept { representation().data = data; }

  /**
   * \brief Returns the number of axes that are used.
   *
   * \return the number of used axes.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto axis_count() const noexcept -> Uint8 { return representation().channels; }

  /**
   * \brief Returns the duration of samples.
   *
   * \return the duration of samples.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto sample_period() const -> U16_Millis
  {
    return U16_Millis{representation().period};
  }

  /**
   * \brief Returns the number of samples.
   *
   * \return the number of samples.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto sample_count() const noexcept -> Uint16
  {
    return representation().samples;
  }

  /**
   * \brief Returns a pointer to user-provided data.
   *
   * \return a pointer to custom user-provided data, might be null.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto data() const noexcept -> Uint16* { return representation().data; }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticCustom& { return m_effect.custom; }

  /// \copydoc representation()
  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticCustom&
  {
    return m_effect.custom;
  }
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_HAPTIC_CUSTOM_HPP_
