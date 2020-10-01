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
 * @file scan_code.hpp
 *
 * @brief Provides the `scan_code` class and constants.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_SCAN_CODE_HEADER
#define CENTURION_SCAN_CODE_HEADER

#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <SDL_scancode.h>

#include <ostream>
#include <string>

#include "centurion_api.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @class scan_code
 *
 * @ingroup input
 *
 * @brief Represents a scan code.
 *
 * @details Scan codes represent the physical location of a key on the
 * keyboard. Use the associated key code associated with the location to give
 * the key press meaning.
 *
 * Scan codes are meant to be layout-independent. Think of this as "the user
 * pressed the Q key as it would be on a US QWERTY keyboard" regardless of
 * whether this is actually a European keyboard or a Dvorak keyboard or
 * whatever. *The scancode is always the same key position.*
 *
 * @since 5.0.0
 *
 * @see `key_code`
 * @see `cen::scancodes`
 *
 * @headerfile scan_code.hpp
 */
class scan_code final
{
 public:
  /**
   * @brief Creates a `scan_code` instance with the `SDL_SCANCODE_UNKNOWN` scan
   * code.
   *
   * @since 5.0.0
   */
  constexpr scan_code() noexcept = default;

  constexpr scan_code(const scan_code&) noexcept = default;

  constexpr scan_code(scan_code&&) noexcept = default;

  /**
   * @brief Creates a `scan_code` instance with the specified scan code.
   *
   * @param scancode the scan code that will be used.
   *
   * @since 5.0.0
   */
  constexpr scan_code(SDL_Scancode scancode) noexcept : m_code{scancode}
  {}

  /**
   * @brief Creates a `scan_code` instance based on a key code.
   *
   * @details The created `scan_code` will use the scan code obtained
   * by converting the specified key code.
   *
   * @param key the key code that will be converted and used.
   *
   * @since 5.0.0
   */
  explicit scan_code(SDL_Keycode key) noexcept
      : m_code{SDL_GetScancodeFromKey(key)}
  {}

  /**
   * @brief Creates a `scan_code` instance based on the specified name.
   *
   * @details If the specified name isn't recognized, `SDL_SCANCODE_UNKNOWN` is
   * used as the scan code.
   *
   * @param name the name of the key, mustn't be null.
   *
   * @see `SDL_GetScancodeFromName`
   *
   * @since 5.0.0
   */
  explicit scan_code(nn_czstring name) noexcept
      : m_code{SDL_GetScancodeFromName(name)}
  {}

  constexpr auto operator=(const scan_code&) noexcept -> scan_code& = default;

  constexpr auto operator=(scan_code&&) noexcept -> scan_code& = default;

  /**
   * @brief Sets the scan code used to the specified scan code.
   *
   * @param code the scan code that will be used.
   *
   * @return the `scan_code` instance.
   *
   * @since 5.0.0
   */
  constexpr auto operator=(SDL_Scancode code) noexcept -> scan_code&
  {
    m_code = code;
    return *this;
  }

  /**
   * @brief Sets the scan code used to be the converted version of the
   * supplied key code.
   *
   * @param keycode the key code that will be converted and used.
   *
   * @return the `scan_code` instance.
   *
   * @since 5.0.0
   */
  auto operator=(SDL_Keycode keycode) noexcept -> scan_code&
  {
    m_code = SDL_GetScancodeFromKey(keycode);
    return *this;
  }

  /**
   * @brief Sets the scan code used to be the one associated with the
   * specified name.
   *
   * @details If the specified name isn't recognized, `SDL_SCANCODE_UNKNOWN` is
   * used as the scan code.
   *
   * @param name the name of the key, mustn't be null.
   *
   * @return the `scan_code` instance.
   *
   * @since 5.0.0
   */
  auto operator=(nn_czstring name) noexcept -> scan_code&
  {
    m_code = SDL_GetScancodeFromName(name);
    return *this;
  }

  /**
   * @brief Indicates whether or not the stored scan code is
   * `SDL_SCANCODE_UNKNOWN`.
   *
   * @return `true` if the internal scan code is `SDL_SCANCODE_UNKNOWN`;
   * `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] constexpr auto unknown() const noexcept -> bool
  {
    return m_code == SDL_SCANCODE_UNKNOWN;
  }

  /**
   * @brief Returns the name associated with the scan code.
   *
   * @return the name associated with the scan code.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return SDL_GetScancodeName(m_code);
  }

  /**
   * @brief Returns the internal scan code.
   *
   * @return the internal scan code.
   *
   * @since 5.0.0
   */
  [[nodiscard]] constexpr auto get() const noexcept -> SDL_Scancode
  {
    return m_code;
  }

  /**
   * @brief Converts to `SDL_Scancode`.
   *
   * @return the internal scan code.
   *
   * @since 5.0.0
   */
  constexpr explicit operator SDL_Scancode() const noexcept
  {
    return m_code;
  }

  /**
   * @brief Converts to `SDL_KeyCode`.
   *
   * @return the key code associated with the internal scan code.
   *
   * @see `SDL_GetKeyFromScancode`
   *
   * @since 5.0.0
   */
  explicit operator SDL_KeyCode() const noexcept
  {
    return static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(m_code));
  }

 private:
  SDL_Scancode m_code{SDL_SCANCODE_UNKNOWN};
};

/**
 * @brief Returns a textual representation of a scan code.
 *
 * @ingroup input
 *
 * @param scanCode the scan code that will be converted.
 *
 * @return a textual representation of the scan code.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto to_string(const scan_code& scanCode) -> std::string;

/**
 * @brief Prints a scan code using a stream.
 *
 * @ingroup input
 *
 * @param stream the stream that will be used.
 * @param scanCode the scan code that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
CENTURION_API
auto operator<<(std::ostream& stream, const scan_code& scanCode)
    -> std::ostream&;

/**
 * @brief Indicates whether or not two scan codes are the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side scan code.
 * @param rhs the right-hand side scan code.
 *
 * @return `true` if the scan codes are the same; `false` otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline constexpr auto operator==(const scan_code& lhs,
                                               const scan_code& rhs) noexcept
    -> bool
{
  return lhs.get() == rhs.get();
}

/**
 * @brief Indicates whether or not two scan codes aren't the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side scan code.
 * @param rhs the right-hand side scan code.
 *
 * @return `true` if the scan codes aren't the same; `false` otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(const scan_code& lhs,
                                               const scan_code& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @namespace cen::scancodes
 *
 * @ingroup input
 *
 * @brief Provides a collection of `scan_code` constants.
 *
 * @details Far from all scan codes are provided. Instead, the most
 * commonly used scan codes are available.
 *
 * @since 5.0.0
 */
namespace scancodes {

/**
 * @brief Represents an unknown key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code unknown;

/**
 * @brief Represents the key "A".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code a{SDL_SCANCODE_A};

/**
 * @brief Represents the key "B".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code b{SDL_SCANCODE_B};

/**
 * @brief Represents the key "C".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code c{SDL_SCANCODE_C};

/**
 * @brief Represents the key "D".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code d{SDL_SCANCODE_D};

/**
 * @brief Represents the key "E".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code e{SDL_SCANCODE_E};

/**
 * @brief Represents the key "F".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f{SDL_SCANCODE_F};

/**
 * @brief Represents the key "G".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code g{SDL_SCANCODE_G};

/**
 * @brief Represents the key "H".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code h{SDL_SCANCODE_H};

/**
 * @brief Represents the key "I".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code i{SDL_SCANCODE_I};

/**
 * @brief Represents the key "J".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code j{SDL_SCANCODE_J};

/**
 * @brief Represents the key "K".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code k{SDL_SCANCODE_K};

/**
 * @brief Represents the key "L".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code l{SDL_SCANCODE_L};

/**
 * @brief Represents the key "M".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code m{SDL_SCANCODE_M};

/**
 * @brief Represents the key "N".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code n{SDL_SCANCODE_N};

/**
 * @brief Represents the key "O".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code o{SDL_SCANCODE_O};

/**
 * @brief Represents the key "P".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code p{SDL_SCANCODE_P};

/**
 * @brief Represents the key "Q".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code q{SDL_SCANCODE_Q};

/**
 * @brief Represents the key "R".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code r{SDL_SCANCODE_R};

/**
 * @brief Represents the key "S".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code s{SDL_SCANCODE_S};

/**
 * @brief Represents the key "T".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code t{SDL_SCANCODE_T};

/**
 * @brief Represents the key "U".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code u{SDL_SCANCODE_U};

/**
 * @brief Represents the key "V".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code v{SDL_SCANCODE_V};

/**
 * @brief Represents the key "W".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code w{SDL_SCANCODE_W};

/**
 * @brief Represents the key "X".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code x{SDL_SCANCODE_X};

/**
 * @brief Represents the key "Y".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code y{SDL_SCANCODE_Y};

/**
 * @brief Represents the key "Z".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code z{SDL_SCANCODE_Z};

/**
 * @brief Represents the key "1".
 *
 * @note This is not for a potential "1" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code one{SDL_SCANCODE_1};

/**
 * @brief Represents the key "2".
 *
 * @note This is not for a potential "2" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code two{SDL_SCANCODE_2};

/**
 * @brief Represents the key "3".
 *
 * @note This is not for a potential "3" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code three{SDL_SCANCODE_3};

/**
 * @brief Represents the key "4".
 *
 * @note This is not for a potential "4" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code four{SDL_SCANCODE_4};

/**
 * @brief Represents the key "5".
 *
 * @note This is not for a potential "5" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code five{SDL_SCANCODE_5};

/**
 * @brief Represents the key "6".
 *
 * @note This is not for a potential "6" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code six{SDL_SCANCODE_6};

/**
 * @brief Represents the key "7".
 *
 * @note This is not for a potential "7" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code seven{SDL_SCANCODE_7};

/**
 * @brief Represents the key "8".
 *
 * @note This is not for a potential "8" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code eight{SDL_SCANCODE_8};

/**
 * @brief Represents the key "9".
 *
 * @note This is not for a potential "9" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code nine{SDL_SCANCODE_9};

/**
 * @brief Represents the key "0".
 *
 * @note This is not for a potential "0" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code zero{SDL_SCANCODE_0};

/**
 * @brief Represents the function key "F1".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f1{SDL_SCANCODE_F1};

/**
 * @brief Represents the function key "F2".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f2{SDL_SCANCODE_F2};

/**
 * @brief Represents the function key "F3".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f3{SDL_SCANCODE_F3};

/**
 * @brief Represents the function key "F4".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f4{SDL_SCANCODE_F4};

/**
 * @brief Represents the function key "F5".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f5{SDL_SCANCODE_F5};

/**
 * @brief Represents the function key "F6".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f6{SDL_SCANCODE_F6};

/**
 * @brief Represents the function key "F7".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f7{SDL_SCANCODE_F7};

/**
 * @brief Represents the function key "F8".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f8{SDL_SCANCODE_F8};

/**
 * @brief Represents the function key "F9".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f9{SDL_SCANCODE_F9};

/**
 * @brief Represents the function key "F10".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f10{SDL_SCANCODE_F10};

/**
 * @brief Represents the function key "F11".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f11{SDL_SCANCODE_F11};

/**
 * @brief Represents the function key "F12".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code f12{SDL_SCANCODE_F12};

/**
 * @brief Represents the left arrow key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code left{SDL_SCANCODE_LEFT};

/**
 * @brief Represents the right arrow key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code right{SDL_SCANCODE_RIGHT};

/**
 * @brief Represents the up arrow key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code up{SDL_SCANCODE_UP};

/**
 * @brief Represents the down arrow key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code down{SDL_SCANCODE_DOWN};

/**
 * @brief Represents the "Space" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code space{SDL_SCANCODE_SPACE};

/**
 * @brief Represents the "Enter" key.
 *
 * @note This key is also referred to as the "Return" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code enter{SDL_SCANCODE_RETURN};

/**
 * @brief Represents the "Escape" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code escape{SDL_SCANCODE_ESCAPE};

/**
 * @brief Represents the "Backspace" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code backspace{SDL_SCANCODE_BACKSPACE};

/**
 * @brief Represents the "Tab" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code tab{SDL_SCANCODE_TAB};

/**
 * @brief Represents the "Caps Lock" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code caps_lock{SDL_SCANCODE_CAPSLOCK};

/**
 * @brief Represents the left "Shift" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code left_shift{SDL_SCANCODE_LSHIFT};

/**
 * @brief Represents the right "Shift" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code right_shift{SDL_SCANCODE_RSHIFT};

/**
 * @brief Represents the left "CTRL" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code left_ctrl{SDL_SCANCODE_LCTRL};

/**
 * @brief Represents the right "CTRL" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code right_ctrl{SDL_SCANCODE_RCTRL};

/**
 * @brief Represents the left "Alt" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code left_alt{SDL_SCANCODE_LALT};

/**
 * @brief Represents the right "Alt" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code right_alt{SDL_SCANCODE_RALT};

/**
 * @brief Represents the left "GUI" key.
 *
 * @details On Windows, this is the "Windows key"; for macs it's the "CMD" key,
 * etc.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code left_gui{SDL_SCANCODE_LGUI};

/**
 * @brief Represents the right "GUI" key.
 *
 * @details On Windows, this is the "Windows" key; for macs it's the "CMD" key,
 * etc.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr scan_code right_gui{SDL_SCANCODE_RGUI};

}  // namespace scancodes
}  // namespace cen

#endif  // CENTURION_SCAN_CODE_HEADER