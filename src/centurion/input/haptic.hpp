#ifndef CENTURION_INPUT_HAPTIC_HPP_
#define CENTURION_INPUT_HAPTIC_HPP_

#include <SDL.h>

#include <cassert>   // assert
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string

#include "../common.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../detail/stdlib.hpp"
#include "../features.hpp"
#include "../joystick.hpp"
#include "../math.hpp"
#include "haptic_effect.hpp"
#include "haptic_feature.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/**
 * \ingroup input
 * \defgroup haptic Haptic
 *
 * \brief Provides the force feedback API.
 */

/// \addtogroup haptic
/// \{

template <typename B>
class basic_haptic;

/**
 * \typedef haptic
 *
 * \brief Represents an owning haptic device.
 *
 * \since 5.2.0
 */
using haptic = basic_haptic<detail::owner_tag>;

/**
 * \typedef haptic_handle
 *
 * \brief Represents a non-owning haptic device.
 *
 * \since 5.2.0
 */
using haptic_handle = basic_haptic<detail::handle_tag>;

/**
 * \class basic_haptic
 *
 * \brief Represents a haptic (force feedback) device.
 *
 * \ownerhandle `haptic`/`haptic_handle`
 *
 * \see `haptic`
 * \see `haptic_handle`
 *
 * \since 5.2.0
 */
template <typename T>
class basic_haptic final {
 public:
  using effect_id = int;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a haptic instance based on an existing pointer.
   *
   * \note The created instance will claim ownership of the supplied pointer if the class
   * has owning semantics.
   *
   * \param haptic a pointer to the haptic device data.
   *
   * \throws exception if the supplied pointer is null and the class has owning semantics.
   *
   * \since 5.2.0
   */
  explicit basic_haptic(maybe_owner<SDL_Haptic*> haptic) noexcept(detail::is_handle<T>)
      : m_haptic{haptic}
  {
    if constexpr (detail::is_owner<T>) {
      if (!m_haptic) {
        throw exception{"Null haptic pointer!"};
      }
    }
  }

  /**
   * \brief Creates a haptic device based on a haptic device index.
   *
   * \note This constructor is only available for owning haptic instances.
   *
   * \param index the device index of the desired haptic device.
   *
   * \throws sdl_error if the haptic device couldn't be opened.
   *
   * \since 5.2.0
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_haptic(const int index = 0) : m_haptic{SDL_HapticOpen(index)}
  {
    if (!m_haptic) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a handle based on an owning haptic instance.
   *
   * \param owner the associated owning haptic device.
   *
   * \since 5.2.0
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_haptic(const haptic& owner) noexcept : m_haptic{owner.get()}
  {}

  /**
   * \brief Creates a haptic device based on a joystick.
   *
   * \note This function is only available for owning haptic instances.
   *
   * \param joystick a joystick handle to the associated joystick.
   *
   * \throws sdl_error if the haptic device couldn't be opened.
   *
   * \see `is_joystick_haptic()`
   *
   * \since 5.2.0
   */
  template <typename U, typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto from_joystick(const basic_joystick<U>& joystick) -> basic_haptic
  {
    if (auto* ptr = SDL_HapticOpenFromJoystick(joystick.get())) {
      return basic_haptic{ptr};
    }
    else {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a haptic device based on the current mouse.
   *
   * \note This function is only available for owning haptic instances.
   *
   * \throws sdl_error if the haptic device couldn't be opened.
   *
   * \see `is_mouse_haptic()`
   *
   * \since 5.2.0
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto from_mouse() -> basic_haptic
  {
    if (auto* ptr = SDL_HapticOpenFromMouse()) {
      return basic_haptic{ptr};
    }
    else {
      throw sdl_error{};
    }
  }

  /// \} End of construction

  /// \name Rumble effects
  /// \{

  /**
   * \brief Initializes rumble playback for the haptic device.
   *
   * \return `success` if rumble playback was successfully initialized; `failure`
   * otherwise.
   *
   * \since 5.2.0
   */
  auto init_rumble() noexcept -> result { return SDL_HapticRumbleInit(m_haptic) == 0; }

  /**
   * \brief Plays a rumble effect.
   *
   * \note Make sure to call `init_rumble()` before calling this function!
   *
   * \param strength the strength of the rumble effect, clamped to [0, 1].
   * \param duration the duration of the rumble effect.
   *
   * \return `success` if the rumble was successful; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto play_rumble(const float strength,
                   const u32ms duration) noexcept(noexcept(duration.count())) -> result
  {
    return SDL_HapticRumblePlay(m_haptic,
                                detail::clamp(strength, 0.0f, 1.0f),
                                duration.count()) == 0;
  }

  /**
   * \brief Stops the current rumble effect.
   *
   * \return `success` if the rumble was successfully stopped; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto stop_rumble() noexcept -> result { return SDL_HapticRumbleStop(m_haptic) == 0; }

  /**
   * \brief Indicates whether or not rumble playback is supported.
   *
   * \return `true` if rumble playback is supported; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto is_rumble_supported() const noexcept -> bool
  {
    return SDL_HapticRumbleSupported(m_haptic) == SDL_TRUE;
  }

  /// \} End of rumble effects

  /// \name Effects
  /// \{

  /**
   * \brief Pauses the device.
   *
   * \pre The device must support the `pause` feature.
   * \post You must call `unpause()` before calling `upload()` or `update()`.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto pause() noexcept -> result
  {
    assert(has_feature_pause());
    return SDL_HapticPause(m_haptic) == 0;
  }

  /**
   * \brief Unpauses the device.
   *
   * \pre `pause()` must have been called before this function is invoked.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto unpause() noexcept -> result { return SDL_HapticUnpause(m_haptic) == 0; }

  /**
   * \brief Uploads an effect to the device.
   *
   * \param effect the effect that will be uploaded to the device.
   *
   * \return the ID associated with the uploaded effect; `std::nullopt` if something went
   * wrong.
   *
   * \since 5.2.0
   */
  template <typename D>
  auto upload(const haptic_effect<D>& effect) noexcept -> std::optional<effect_id>
  {
    auto internal = effect.get();
    const auto id = SDL_HapticNewEffect(m_haptic, &internal);
    if (id != -1) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Attempts to update the effect associated with the specified ID.
   *
   * \note It is not possible to change the type of the effect through this function.
   *
   * \note You might experience strange results if you call this function for an
   * effect that is currently playing, but it is possible.
   *
   * \param id the ID associated with the effect that will be updated.
   * \param effect the new properties that will be associated with the effect.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  template <typename D>
  auto update(const effect_id id, const haptic_effect<D>& effect) noexcept -> result
  {
    auto internal = effect.get();
    return SDL_HapticUpdateEffect(m_haptic, id, &internal) == 0;
  }

  /**
   * \brief Runs the specified effect.
   *
   * \note If you want to repeat the effect indefinitely without repeating the attack and
   * fade, see `haptic_effect::set_repeat_forever()`.
   *
   * \param id the ID associated with the effect that will be run.
   * \param iterations the number of iterations, can be `haptic_infinity` to repeat the
   * effect forever (including the attack and fade).
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto run(const effect_id id, const uint32 iterations = 1) noexcept -> result
  {
    return SDL_HapticRunEffect(m_haptic, id, iterations) == 0;
  }

  /**
   * \brief Stops a currently running effect.
   *
   * \param id the ID associated with the effect that will be stopped.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto stop(const effect_id id) noexcept -> result
  {
    return SDL_HapticStopEffect(m_haptic, id) == 0;
  }

  /**
   * \brief Stops all currently running effects on the device.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto stop_all() noexcept -> result { return SDL_HapticStopAll(m_haptic) == 0; }

  /**
   * \brief Destroys the effect associated with the specified ID.
   *
   * \note This is done automatically when the device is destructed.
   *
   * \details The effect will be destroyed will be stopped if it is running by the time
   * this function is invoked.
   *
   * \param id the ID associated with the effect that will be destroyed.
   *
   * \since 5.2.0
   */
  void destroy(const effect_id id) noexcept { SDL_HapticDestroyEffect(m_haptic, id); }

  /**
   * \brief Sets the gain the is used.
   *
   * \pre The device must support the `gain` feature.
   * \pre `gain` must be greater or equal to zero.
   * \pre `gain` must be less than or equal to zero.
   *
   * \param gain the gain that will be used, in the interval [0, 100].
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto set_gain(const int gain) noexcept -> result
  {
    assert(has_feature_gain());
    assert(gain >= 0);
    assert(gain <= 100);
    return SDL_HapticSetGain(m_haptic, gain) == 0;
  }

  /**
   * \brief Sets the autocenter value that will be used.
   *
   * \pre The device must support the `autocenter` feature.
   * \pre `autocenter` must be greater or equal to zero.
   * \pre `autocenter` must be less than or equal to zero.
   *
   * \param autocenter the value of the autocenter that will be used, in the interval [0,
   * 100]. Autocentering will be disabled if this value is zero.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto set_autocenter(const int autocenter) noexcept -> result
  {
    assert(has_feature_autocenter());
    assert(autocenter >= 0);
    assert(autocenter <= 100);
    return SDL_HapticSetAutocenter(m_haptic, autocenter) == 0;
  }

  /**
   * \brief Indicates whether or not the device can run the specified effect.
   *
   * \param effect the effect that will be checked.
   *
   * \return `true` if the device supports the effect; `false` otherwise.
   *
   * \since 5.2.0
   */
  template <typename D>
  [[nodiscard]] auto is_supported(const haptic_effect<D>& effect) const noexcept -> bool
  {
    auto internal = effect.get();
    return SDL_HapticEffectSupported(m_haptic, &internal) == SDL_TRUE;
  }

  /**
   * \brief Indicates whether or not the specified effect is playing on the device.
   *
   * \pre The device must support the `status` feature.
   *
   * \return `true` on if the effect is playing on the device; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto is_playing(const effect_id id) const noexcept -> bool
  {
    assert(has_feature_status());
    return SDL_HapticGetEffectStatus(m_haptic, id) == 1;
  }

  /// \}

  /// \name Feature checks
  /// \{

  /**
   * \brief Indicates whether or not the device supports the specified feature.
   *
   * \param feature the haptic feature to be checked.
   *
   * \return `true` if the feature is supported; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature(const haptic_feature feature) const noexcept -> bool
  {
    return has_feature(to_underlying(feature));
  }

  /**
   * \brief Indicates whether or not the device has the `constant` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_constant() const noexcept -> bool
  {
    return has_feature(haptic_feature::constant);
  }

  /**
   * \brief Indicates whether or not the device has the `sine` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_sine() const noexcept -> bool
  {
    return has_feature(haptic_feature::sine);
  }

  /**
   * \brief Indicates whether or not the device has the `left_right` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_left_right() const noexcept -> bool
  {
    return has_feature(haptic_feature::left_right);
  }

  /**
   * \brief Indicates whether or not the device has the `triangle` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_triangle() const noexcept -> bool
  {
    return has_feature(haptic_feature::triangle);
  }

  /**
   * \brief Indicates whether or not the device has the `sawtooth_up` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_sawtooth_up() const noexcept -> bool
  {
    return has_feature(haptic_feature::sawtooth_up);
  }

  /**
   * \brief Indicates whether or not the device has the `sawtooth_down` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_sawtooth_down() const noexcept -> bool
  {
    return has_feature(haptic_feature::sawtooth_down);
  }

  /**
   * \brief Indicates whether or not the device has the `ramp` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_ramp() const noexcept -> bool
  {
    return has_feature(haptic_feature::ramp);
  }

  /**
   * \brief Indicates whether or not the device has the `spring` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_spring() const noexcept -> bool
  {
    return has_feature(haptic_feature::spring);
  }

  /**
   * \brief Indicates whether or not the device has the `damper` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_damper() const noexcept -> bool
  {
    return has_feature(haptic_feature::damper);
  }

  /**
   * \brief Indicates whether or not the device has the `inertia` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_inertia() const noexcept -> bool
  {
    return has_feature(haptic_feature::inertia);
  }

  /**
   * \brief Indicates whether or not the device has the `friction` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_friction() const noexcept -> bool
  {
    return has_feature(haptic_feature::friction);
  }

  /**
   * \brief Indicates whether or not the device has the `gain` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_gain() const noexcept -> bool
  {
    return has_feature(haptic_feature::gain);
  }

  /**
   * \brief Indicates whether or not the device has the `autocenter` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_autocenter() const noexcept -> bool
  {
    return has_feature(haptic_feature::autocenter);
  }

  /**
   * \brief Indicates whether or not the device has the `status` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_status() const noexcept -> bool
  {
    return has_feature(haptic_feature::status);
  }

  /**
   * \brief Indicates whether or not the device has the `pause` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_pause() const noexcept -> bool
  {
    return has_feature(haptic_feature::pause);
  }

  /**
   * \brief Indicates whether or not the device has the `custom` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_custom() const noexcept -> bool
  {
    return has_feature(haptic_feature::custom);
  }

  /// \} End of feature queries

  /// \name Device information
  /// \{

  /**
   * \brief Returns the index associated with the haptic device.
   *
   * \return the index associated with the haptic device; `std::nullopt` if something goes
   * wrong.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto index() const noexcept -> std::optional<int>
  {
    const auto res = SDL_HapticIndex(m_haptic);
    if (res != -1) {
      return res;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Attempts to return the name associated with the haptic device.
   *
   * \return the name associated with the haptic device; a null pointer is returned if no
   * name was found.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto name() const noexcept -> const char*
  {
    if (const auto i = index()) {
      return SDL_HapticName(*i);
    }
    else {
      return nullptr;
    }
  }

  /**
   * \brief Returns the maximum amount of effect the device can store.
   *
   * \note This function isn't supported on all platforms and the returned value should be
   * treated as an approximation.
   *
   * \return the maximum number of effects the the haptic device can store; `std::nullopt`
   * if something goes wrong.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto effect_capacity() const noexcept -> std::optional<int>
  {
    const auto capacity = SDL_HapticNumEffects(m_haptic);
    if (capacity != -1) {
      return capacity;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the maximum amount of effects that can be played simultaneously.
   *
   * \note This function isn't supported on all platforms.
   *
   * \return the maximum number of effects that can be playing simultaneously;
   * `std::nullopt` if something goes wrong.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto concurrent_capacity() const noexcept -> std::optional<int>
  {
    const auto capacity = SDL_HapticNumEffectsPlaying(m_haptic);
    if (capacity != -1) {
      return capacity;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the number of axes that the haptic device has.
   *
   * \return the number of axes that the haptic device has.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto axis_count() const noexcept -> int { return SDL_HapticNumAxes(m_haptic); }

  /// \} End of device information

  /**
   * \brief Returns the number of available haptic devices.
   *
   * \return the amount of available haptic devices.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto count() noexcept -> int { return SDL_NumHaptics(); }

  /**
   * \brief Indicates whether or not a joystick has haptic capabilities.
   *
   * \param joystick the joystick that will be checked.
   *
   * \return `true` if the joystick has haptic capabilities; `false` otherwise.
   *
   * \since 5.2.0
   */
  template <typename U>
  [[nodiscard]] static auto is_joystick_haptic(const basic_joystick<U>& joystick) noexcept
      -> bool
  {
    return SDL_JoystickIsHaptic(joystick.get()) == SDL_TRUE;
  }

  /**
   * \brief Indicates whether or not the system mouse has haptic capabilities.
   *
   * \return `true` if the mouse has haptic capabilities; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto is_mouse_haptic() noexcept -> bool { return SDL_MouseIsHaptic(); }

  /**
   * \brief Indicates whether or not a haptic device at a specified index has
   * been opened.
   *
   * \param index the index of the haptic device that will be queried.
   *
   * \return `true` if the haptic device has been opened; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto is_opened(const int index) noexcept -> bool
  {
    return SDL_HapticOpened(index);
  }

  /**
   * \brief Indicates whether or not the handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.2.0
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return m_haptic != nullptr;
  }

  /**
   * \brief Returns a pointer to the internal representation.
   *
   * \warning Don't claim ownership of the returned pointer!
   *
   * \return a pointer to the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Haptic* { return m_haptic.get(); }

 private:
  detail::pointer<T, SDL_Haptic> m_haptic;

  /**
   * \brief Indicates whether or not the haptic device supports the specified features.
   *
   * \details The supplied value must be a masked subset of the following flags:
   *
   * \verbatim
       SDL_HAPTIC_CONSTANT
       SDL_HAPTIC_SINE
       SDL_HAPTIC_LEFTRIGHT
       SDL_HAPTIC_LEFTRIGHT
       SDL_HAPTIC_TRIANGLE
       SDL_HAPTIC_SAWTOOTHUP
       SDL_HAPTIC_SAWTOOTHDOWN
       SDL_HAPTIC_RAMP
       SDL_HAPTIC_SPRING
       SDL_HAPTIC_DAMPER
       SDL_HAPTIC_INERTIA
       SDL_HAPTIC_FRICTION
       SDL_HAPTIC_CUSTOM
       SDL_HAPTIC_GAIN
       SDL_HAPTIC_AUTOCENTER
       SDL_HAPTIC_STATUS
       SDL_HAPTIC_PAUSE.
   * \endverbatim
   *
   * \param flag the mask of feature flags.
   *
   * \return `true` if the haptic device supports the features; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature(const uint flag) const noexcept -> bool
  {
    return flag & SDL_HapticQuery(m_haptic);
  }
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a haptic device.
 *
 * \param haptic the haptic device that will be converted.
 *
 * \return a string that represents a haptic device.
 *
 * \since 5.2.0
 */
template <typename T>
[[nodiscard]] auto ToString(const basic_haptic<T>& haptic) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("haptic{{data: {}, name: {}}}",
                     detail::address_of(haptic.get()),
                     str_or_na(haptic.name()));
#else
  return "haptic{data: " + detail::address_of(haptic.get()) +
         ", name: " + str_or_na(haptic.name()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a haptic device using a stream.
 *
 * \param stream the stream that will be used.
 * \param haptic the haptic device that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.2.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_haptic<T>& haptic) -> std::ostream&
{
  return stream << ToString(haptic);
}

/// \} End of streaming

/// \} End of input haptic

}  // namespace cen

#endif  // CENTURION_INPUT_HAPTIC_HPP_
