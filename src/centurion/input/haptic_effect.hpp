#ifndef CENTURION_HAPTIC_EFFECT_HEADER
#define CENTURION_HAPTIC_EFFECT_HEADER

#include <SDL.h>

#include <type_traits>  // enable_if_t

#include "../core/integers.hpp"
#include "../core/time.hpp"
#include "haptic_direction.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \brief A constant that can be used to play an effect indefinitely.
 *
 * \since 5.2.0
 */
inline constexpr u32 haptic_infinity = SDL_HAPTIC_INFINITY;

/**
 * \class haptic_effect
 *
 * \brief Represents a haptic effect.
 *
 * \details The following is an illustration of the different stages of a haptic effect,
 * copied from the SDL documentation, albeit with tweaked terms.
 * \verbatim
    Strength
    ^
    |
    |    effect level -->  _________________
    |                     /                 \
    |                    /                   \
    |                   /                     \
    |                  /                       \
    | attack_level --> |                        \
    |                  |                        |  <---  fade_level
    |
    +--------------------------------------------------> Time
                       [--]                 [---]
                       attack_length        fade_length

    [------------------][-----------------------]
    delay               duration
    \endverbatim
 *
 * \tparam Derived the type of the subclass, for CRTP.
 *
 * \since 5.2.0
 */
template <typename Derived>
class haptic_effect
{
  template <typename T>
  using has_direction = std::enable_if_t<T::hasDirection, int>;

  template <typename T>
  using has_envelope = std::enable_if_t<T::hasEnvelope, int>;

  template <typename T>
  using has_trigger = std::enable_if_t<T::hasTrigger, int>;

  template <typename T>
  using has_delay = std::enable_if_t<T::hasDelay, int>;

 public:
  /// \name Direction functions
  /// \{

  /**
   * \brief Sets the haptic direction associated with the effect.
   *
   * \note This function is not available for all haptic effects.
   *
   * \param direction the new direction of the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_direction<D> = 0>
  void set_direction(const haptic_direction& direction) noexcept
  {
    rep().direction = direction.get();
  }

  /**
   * \brief Returns the haptic direction associated with the effect.
   *
   * \return the current direction associated with the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_direction<D> = 0>
  [[nodiscard]] auto direction() const noexcept -> haptic_direction
  {
    return haptic_direction{rep().direction};
  }

  /// \} End of direction functions

  /// \name Replay functions
  /// \{

  /**
   * \brief Sets the effect to be repeated indefinitely when run.
   *
   * \details This function makes the effect repeat forever when run, but the attack and
   * fade are not repeated.
   *
   * \since 5.2.0
   */
  void set_repeat_forever() noexcept
  {
    rep().length = haptic_infinity;
  }

  /**
   * \brief Sets the duration of the effect.
   *
   * \param duration the duration of the effect.
   *
   * \since 5.2.0
   */
  void set_duration(const milliseconds<u32> duration) noexcept(noexcept(duration.count()))
  {
    rep().length = duration.count();
  }

  /**
   * \brief Sets the delay before before the effect is started.
   *
   * \note This function is not available for all haptic effects.
   *
   * \param delay the delay before before the effect is started.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_delay<D> = 0>
  void set_delay(const milliseconds<u16> delay) noexcept(noexcept(delay.count()))
  {
    rep().delay = delay.count();
  }

  /**
   * \brief Returns the duration of the effect.
   *
   * \return the duration of the effect.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto duration() const -> milliseconds<u32>
  {
    return milliseconds<u32>{rep().length};
  }

  /**
   * \brief Returns the delay before before the effect is started.
   *
   * \note This function is not available for all haptic effects.
   *
   * \return the delay before before the effect is started.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_delay<D> = 0>
  [[nodiscard]] auto delay() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().delay};
  }

  /// \} End of replay functions

  /// \name Trigger functions
  /// \{

  /**
   * \brief Sets the button that triggers the effect.
   *
   * \note This function is not available for all haptic effects.
   *
   * \param button the button that triggers the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_trigger<D> = 0>
  void set_button(const u16 button) noexcept
  {
    rep().button = button;
  }

  /**
   * \brief Sets the minimum interval in between activations of the effect.
   *
   * \note This function is not available for all haptic effects.
   *
   * \param interval the minimum interval in between activations of the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_trigger<D> = 0>
  void set_interval(const milliseconds<u16> interval) noexcept(noexcept(interval.count()))
  {
    rep().interval = interval.count();
  }

  /**
   * \brief Returns the button that triggers the effect.
   *
   * \note This function is not available for all haptic effects.
   *
   * \return the button that triggers the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_trigger<D> = 0>
  [[nodiscard]] auto button() const noexcept -> u16
  {
    return rep().button;
  }

  /**
   * \brief Returns the minimum interval in between activations of the effect.
   *
   * \note This function is not available for all haptic effects.
   *
   * \return the minimum interval in between activations of the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_trigger<D> = 0>
  [[nodiscard]] auto interval() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().interval};
  }

  /// \} End of trigger functions

  /// \name Envelope functions
  /// \{

  /**
   * \brief Sets the level at the *start* of the attack.
   *
   * \note This function is not available for all haptic effects.
   *
   * \param level the level at the start of the attack.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = 0>
  void set_attack_level(const u16 level) noexcept
  {
    rep().attack_level = level;
  }

  /**
   * \brief Sets the level at the *end* of the fade out.
   *
   * \note This function is not available for all haptic effects.
   *
   * \param level the level at the *end* of the fade out.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = 0>
  void set_fade_level(const u16 level) noexcept
  {
    rep().fade_level = level;
  }

  // clang-format off

  /**
   * \brief Sets the duration of the attack.
   *
   * \note This function is not available for all haptic effects.
   *
   * \param duration the duration of the attack.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = 0>
  void set_attack_duration(const milliseconds<u16> duration) noexcept(noexcept(duration.count()))
  {
    rep().attack_length = duration.count();
  }

  /**
   * \brief Sets the duration of the fade out.
   *
   * \note This function is not available for all haptic effects.
   *
   * \param duration the duration of the fade out.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = 0>
  void set_fade_duration(const milliseconds<u16> duration) noexcept(noexcept(duration.count()))
  {
    rep().fade_length = duration.count();
  }

  // clang-format on

  /**
   * \brief Returns the level at the *start* of the attack.
   *
   * \note This function is not available for all haptic effects.
   *
   * \return the the level at the *start* of the attack.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = 0>
  [[nodiscard]] auto attack_level() const noexcept -> u16
  {
    return rep().attack_level;
  }

  /**
   * \brief Returns the level at the *end* of the fade.
   *
   * \note This function is not available for all haptic effects.
   *
   * \return the level at the *end* of the fade.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = 0>
  [[nodiscard]] auto fade_level() const noexcept -> u16
  {
    return rep().fade_level;
  }

  /**
   * \brief Returns the duration of the attack.
   *
   * \note This function is not available for all haptic effects.
   *
   * \return the duration of the attack.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = 0>
  [[nodiscard]] auto attack_duration() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().attack_length};
  }

  /**
   * \brief Returns the duration of the fade out.
   *
   * \note This function is not available for all haptic effects.
   *
   * \return the duration of the fade out.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = 0>
  [[nodiscard]] auto fade_duration() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().fade_length};
  }

  /// \} End of envelope functions

  /**
   * \brief Returns the type associated with the haptic effect.
   *
   * \return the associated effect type.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto type() const noexcept -> u16
  {
    return rep().type;
  }

  /**
   * \brief Returns the internal effect representation.
   *
   * \return the internal effect representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto get() noexcept -> SDL_HapticEffect&
  {
    return m_effect;
  }

  /**
   * \copydoc get()
   */
  [[nodiscard]] auto get() const noexcept -> const SDL_HapticEffect&
  {
    return m_effect;
  }

 protected:
  SDL_HapticEffect m_effect{};

 private:
  [[nodiscard]] auto derived() noexcept -> Derived*
  {
    return static_cast<Derived*>(this);
  }

  [[nodiscard]] auto derived() const noexcept -> const Derived*
  {
    return static_cast<const Derived*>(this);
  }

  [[nodiscard]] auto rep() noexcept -> auto&
  {
    return derived()->representation();
  }

  [[nodiscard]] auto rep() const noexcept -> const auto&
  {
    return derived()->representation();
  }
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_HAPTIC_EFFECT_HEADER
