/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file basic_joystick.ipp
 *
 * @brief Provides the implementation of `basic_joystick` templates.
 *
 * @author Albin Johansson
 *
 * @copyright MIT License
 *
 * @date 2019-2020
 */

#ifndef CENTURION_BASIC_JOYSTICK_IMPLEMENTATION_FILE
#define CENTURION_BASIC_JOYSTICK_IMPLEMENTATION_FILE

#include <utility>  // forward

#include "centurion_api.hpp"
#include "joystick.hpp"

namespace centurion {

template <typename T>
template <typename... Args>
basic_joystick<T>::basic_joystick(Args&&... args)
    : m_storage{std::forward<Args>(args)...}
{}

template <typename T>
void basic_joystick<T>::update() noexcept
{
  SDL_JoystickUpdate();
}

template <typename T>
void basic_joystick<T>::lock() noexcept
{
  SDL_LockJoysticks();
}

template <typename T>
void basic_joystick<T>::unlock() noexcept
{
  SDL_UnlockJoysticks();
}

template <typename T>
void basic_joystick<T>::set_polling(bool enabled) noexcept
{
  SDL_JoystickEventState(enabled ? SDL_ENABLE : SDL_DISABLE);
}

template <typename T>
auto basic_joystick<T>::polling() noexcept -> bool
{
  return SDL_JoystickEventState(SDL_QUERY);
}

template <typename T>
auto basic_joystick<T>::amount() noexcept -> std::optional<int>
{
  const auto result = SDL_NumJoysticks();
  if (result < 0) {
    return std::nullopt;
  } else {
    return result;
  }
}

template <typename T>
auto basic_joystick<T>::guid(int deviceIndex) noexcept -> SDL_JoystickGUID
{
  return SDL_JoystickGetDeviceGUID(deviceIndex);
}

template <typename T>
auto basic_joystick<T>::player_index(int deviceIndex) noexcept
    -> std::optional<int>
{
  const auto index = SDL_JoystickGetDevicePlayerIndex(deviceIndex);
  if (index == -1) {
    return std::nullopt;
  } else {
    return index;
  }
}

template <typename T>
auto basic_joystick<T>::vendor(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto vendor = SDL_JoystickGetDeviceVendor(deviceIndex);
  if (vendor == 0) {
    return std::nullopt;
  } else {
    return vendor;
  }
}

template <typename T>
auto basic_joystick<T>::product(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto product = SDL_JoystickGetDeviceProduct(deviceIndex);
  if (product == 0) {
    return std::nullopt;
  } else {
    return product;
  }
}

template <typename T>
auto basic_joystick<T>::product_version(int deviceIndex) noexcept
    -> std::optional<u16>
{
  const auto version = SDL_JoystickGetDeviceProductVersion(deviceIndex);
  if (version == 0) {
    return std::nullopt;
  } else {
    return version;
  }
}

template <typename T>
auto basic_joystick<T>::get_type(int deviceIndex) noexcept -> type
{
  return static_cast<type>(SDL_JoystickGetDeviceType(deviceIndex));
}

template <typename T>
auto basic_joystick<T>::instance_id(int deviceIndex) noexcept
    -> std::optional<SDL_JoystickID>
{
  const auto id = SDL_JoystickGetDeviceInstanceID(deviceIndex);
  if (id == -1) {
    return std::nullopt;
  } else {
    return id;
  }
}

template <typename T>
auto basic_joystick<T>::name(int deviceIndex) noexcept -> czstring
{
  return SDL_JoystickNameForIndex(deviceIndex);
}

template <typename T>
auto basic_joystick<T>::guid_from_string(nn_czstring str) noexcept
    -> SDL_JoystickGUID
{
  return SDL_JoystickGetGUIDFromString(str);
}

template <typename T>
void basic_joystick<T>::rumble(u16 lowFreq,
                               u16 highFreq,
                               milliseconds<u32> duration) noexcept
{
  SDL_JoystickRumble(ptr(), lowFreq, highFreq, duration.count());
}

template <typename T>
void basic_joystick<T>::set_player_index(int index) noexcept
{
  SDL_JoystickSetPlayerIndex(ptr(), index);
}

template <typename T>
auto basic_joystick<T>::player_index() const noexcept -> std::optional<int>
{
  const auto index = SDL_JoystickGetPlayerIndex(ptr());
  if (index == -1) {
    return std::nullopt;
  } else {
    return index;
  }
}

template <typename T>
auto basic_joystick<T>::get_type() const noexcept -> type
{
  return static_cast<type>(SDL_JoystickGetType(ptr()));
}

template <typename T>
auto basic_joystick<T>::vendor() const noexcept -> std::optional<u16>
{
  const auto vendor = SDL_JoystickGetVendor(ptr());
  if (vendor == 0) {
    return std::nullopt;
  } else {
    return vendor;
  }
}

template <typename T>
auto basic_joystick<T>::product() const noexcept -> std::optional<u16>
{
  const auto product = SDL_JoystickGetProduct(ptr());
  if (product == 0) {
    return std::nullopt;
  } else {
    return product;
  }
}

template <typename T>
auto basic_joystick<T>::product_version() const noexcept -> std::optional<u16>
{
  const auto version = SDL_JoystickGetProductVersion(ptr());
  if (version == 0) {
    return std::nullopt;
  } else {
    return version;
  }
}

template <typename T>
auto basic_joystick<T>::get_ball_axis_change(int ball) const noexcept
    -> std::optional<ball_axis_change>
{
  ball_axis_change change{};
  const auto result = SDL_JoystickGetBall(ptr(), ball, &change.dx, &change.dy);
  if (result == 0) {
    return change;
  } else {
    return std::nullopt;
  }
}

template <typename T>
auto basic_joystick<T>::axis_pos(unsigned int axis) const noexcept
    -> std::optional<i16>
{
  const auto result = SDL_JoystickGetAxis(ptr(), static_cast<int>(axis));
  if (result == 0) {
    return std::nullopt;
  } else {
    return result;
  }
}

template <typename T>
auto basic_joystick<T>::axis_initial_state(unsigned int axis) const noexcept
    -> std::optional<i16>
{
  i16 state{};
  const auto hadInitialState =
      SDL_JoystickGetAxisInitialState(ptr(), static_cast<int>(axis), &state);
  if (hadInitialState) {
    return state;
  } else {
    return std::nullopt;
  }
}

template <typename T>
auto basic_joystick<T>::attached() const noexcept -> bool
{
  return SDL_JoystickGetAttached(ptr());
}

template <typename T>
auto basic_joystick<T>::num_hats() const noexcept -> int
{
  return SDL_JoystickNumHats(ptr());
}

template <typename T>
auto basic_joystick<T>::num_axes() const noexcept -> int
{
  return SDL_JoystickNumAxes(ptr());
}

template <typename T>
auto basic_joystick<T>::num_trackballs() const noexcept -> int
{
  return SDL_JoystickNumBalls(ptr());
}

template <typename T>
auto basic_joystick<T>::num_buttons() const noexcept -> int
{
  return SDL_JoystickNumButtons(ptr());
}

template <typename T>
auto basic_joystick<T>::instance_id() const noexcept -> SDL_JoystickID
{
  return SDL_JoystickInstanceID(ptr());
}

template <typename T>
auto basic_joystick<T>::guid() noexcept -> SDL_JoystickGUID
{
  return SDL_JoystickGetGUID(ptr());
}

template <typename T>
auto basic_joystick<T>::name() const noexcept -> czstring
{
  return SDL_JoystickName(ptr());
}

template <typename T>
auto basic_joystick<T>::get_power() const noexcept -> power
{
  return static_cast<power>(SDL_JoystickCurrentPowerLevel(ptr()));
}

template <typename T>
auto basic_joystick<T>::get_button_state(int button) const noexcept
    -> button_state
{
  return static_cast<button_state>(SDL_JoystickGetButton(ptr(), button));
}

template <typename T>
auto basic_joystick<T>::get_hat_state(int hat) const noexcept -> hat_state
{
  return static_cast<hat_state>(SDL_JoystickGetHat(ptr(), hat));
}

}  // namespace centurion

#endif  // CENTURION_BASIC_JOYSTICK_IMPLEMENTATION_FILE
