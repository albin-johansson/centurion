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
 * @file key.hpp
 *
 * @brief Provides the `key` class.
 *
 * @todo Add Key constants.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_KEY_HEADER
#define CENTURION_KEY_HEADER

#include <SDL_keycode.h>
#include <SDL_scancode.h>

#include "centurion_api.hpp"
#include "centurion_utils.hpp"

namespace centurion {

/**
 * @class key
 *
 * @brief Represents a keyboard key.
 *
 * @details Instances of this class can be created from both `SDL_Scancode` and
 * `SDL_Keycode` values.
 *
 * @see `SDL_Scancode`
 * @see `SDL_Keycode`
 *
 * @since 4.0.0
 */
class [[deprecated]] key final {
 public:
  /**
   * @brief Creates a key instance with the `UNKNOWN` scancode and keycode
   * values.
   *
   * @since 4.0.0
   */
  key() noexcept = default;

  /**
   * @brief Creates a key instance based on the supplied scancode.
   *
   * @param scancode the scancode that the key will be based on.
   *
   * @since 4.0.0
   */
  explicit key(SDL_Scancode scancode) noexcept { set(scancode); }

  /**
   * @brief Creates a key instance based on the supplied keycode.
   *
   * @param keycode the keycode that the key will be based on.
   *
   * @since 4.0.0
   */
  explicit key(SDL_Keycode keycode) noexcept { set(keycode); }

  /**
   * @brief `constexpr`-enabled constructor for keys.
   *
   * @param scancode the scancode that will be used.
   * @param keycode the keycode that will be used.
   *
   * @since 5.0.0
   */
  constexpr explicit key(SDL_Scancode scancode, SDL_KeyCode keycode) noexcept
      : m_scancode{scancode}, m_keycode{keycode}
  {}

  /**
   * @brief Creates a key instance from the specified key name.
   *
   * @details If no key is associated with the specified name, then the created
   * instance will assume the key- and scancodes that represent an unknown key.
   *
   * @param name the name of the key that the created instance will
   * represent, can safely be null.
   *
   * @since 4.1.0
   */
  explicit key(czstring name) noexcept
  {
    if (name) {
      set(SDL_GetScancodeFromName(name));
    }
  }

  /**
   * @brief Sets the value of the key.
   *
   * @param scancode the scancode of the key that the key instance will
   * represent.
   *
   * @since 4.0.0
   */
  void set(SDL_Scancode scancode) noexcept
  {
    m_scancode = scancode;
    m_keycode = SDL_GetKeyFromScancode(scancode);
  }

  /**
   * @brief Sets the value of the key.
   *
   * @param keycode the keycode of the key that the key instance will
   * represent.
   *
   * @since 4.0.0
   */
  void set(SDL_Keycode keycode) noexcept
  {
    m_scancode = SDL_GetScancodeFromKey(keycode);
    m_keycode = keycode;
  }

  /**
   * @brief Returns the name of the key associated with the key instance.
   *
   * @details This method returns the empty string if no name is found to be
   * associated with the key that the key instance represents.
   *
   * @return the name of the key associated with this key instance; the empty
   * string if the name couldn't be deduced.
   *
   * @since 4.1.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return SDL_GetScancodeName(m_scancode);
  }

  /**
   * @brief Indicates whether or not the key instance is associated with a known
   * key.
   *
   * @return `true` if no key is associated with the key instance; `false`
   * otherwise.
   *
   * @since 4.1.0
   */
  [[nodiscard]] auto unknown() const noexcept -> bool
  {
    return m_scancode == SDL_SCANCODE_UNKNOWN;
  }

  /**
   * @brief Returns the scancode associated with the key.
   *
   * @return the scancode associated with the key.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto scancode() const noexcept -> SDL_Scancode
  {
    return m_scancode;
  }

  /**
   * @brief Returns the keycode associated with the key.
   *
   * @return the keycode associated with the key.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto keycode() const noexcept -> SDL_Keycode
  {
    return m_keycode;
  }

  /**
   * @brief Converts to a scancode value.
   *
   * @return an `SDL_Scancode` value.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator SDL_Scancode() const noexcept
  {
    return m_scancode;
  }

  /**
   * @brief Converts to a keycode value.
   *
   * @return an `SDL_Keycode` value.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator SDL_Keycode() const noexcept
  {
    return m_keycode;
  }

 private:
  SDL_Scancode m_scancode{SDL_SCANCODE_UNKNOWN};
  SDL_Keycode m_keycode{SDLK_UNKNOWN};
};

static_assert(std::is_final_v<key>);
static_assert(std::is_copy_constructible_v<key>);
static_assert(std::is_copy_assignable_v<key>);
static_assert(std::is_move_constructible_v<key>);
static_assert(std::is_move_assignable_v<key>);

/**
 * @brief Indicates whether or not two key instances represent the same keyboard
 * key.
 *
 * @param lhs the left-hand side key.
 * @param rhs the right-hand side key.
 *
 * @return `true` if the two keys are the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto operator==(const key& lhs, const key& rhs) noexcept
    -> bool
{
  return (lhs.scancode() == rhs.scancode()) && (lhs.keycode() == rhs.keycode());
}

/**
 * @brief Indicates whether or not two key instances don't represent the same
 * keyboard key.
 *
 * @param lhs the left-hand side key.
 * @param rhs the right-hand side key.
 *
 * @return `true` if the two keys aren't the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto operator!=(const key& lhs, const key& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @namespace centurion::keys
 *
 * @brief Provides a limited collection of `key` constants.
 *
 * @details Far from all possible keys are provided. Instead, the most
 * commonly used keys are available.
 */
namespace keys {

/**
 * @brief Represents an unknown key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key unknown{SDL_SCANCODE_UNKNOWN, SDLK_UNKNOWN};

/**
 * @brief Represents the key "A".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key a{SDL_SCANCODE_A, SDLK_a};

/**
 * @brief Represents the key "B".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key b{SDL_SCANCODE_B, SDLK_b};

/**
 * @brief Represents the key "C".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key c{SDL_SCANCODE_C, SDLK_c};

/**
 * @brief Represents the key "D".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key d{SDL_SCANCODE_D, SDLK_d};

/**
 * @brief Represents the key "E".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key e{SDL_SCANCODE_E, SDLK_e};

/**
 * @brief Represents the key "F".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f{SDL_SCANCODE_F, SDLK_f};

/**
 * @brief Represents the key "G".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key g{SDL_SCANCODE_G, SDLK_g};

/**
 * @brief Represents the key "H".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key h{SDL_SCANCODE_H, SDLK_h};

/**
 * @brief Represents the key "I".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key i{SDL_SCANCODE_I, SDLK_i};

/**
 * @brief Represents the key "J".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key j{SDL_SCANCODE_J, SDLK_j};

/**
 * @brief Represents the key "K".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key k{SDL_SCANCODE_K, SDLK_k};

/**
 * @brief Represents the key "L".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key l{SDL_SCANCODE_L, SDLK_l};

/**
 * @brief Represents the key "M".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key m{SDL_SCANCODE_M, SDLK_m};

/**
 * @brief Represents the key "N".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key n{SDL_SCANCODE_N, SDLK_n};

/**
 * @brief Represents the key "O".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key o{SDL_SCANCODE_O, SDLK_o};

/**
 * @brief Represents the key "P".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key p{SDL_SCANCODE_P, SDLK_p};

/**
 * @brief Represents the key "Q".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key q{SDL_SCANCODE_Q, SDLK_q};

/**
 * @brief Represents the key "R".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key r{SDL_SCANCODE_R, SDLK_r};

/**
 * @brief Represents the key "S".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key s{SDL_SCANCODE_S, SDLK_s};

/**
 * @brief Represents the key "T".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key t{SDL_SCANCODE_T, SDLK_t};

/**
 * @brief Represents the key "U".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key u{SDL_SCANCODE_U, SDLK_u};

/**
 * @brief Represents the key "V".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key v{SDL_SCANCODE_V, SDLK_v};

/**
 * @brief Represents the key "W".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key w{SDL_SCANCODE_W, SDLK_w};

/**
 * @brief Represents the key "X".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key x{SDL_SCANCODE_X, SDLK_x};

/**
 * @brief Represents the key "Y".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key y{SDL_SCANCODE_Y, SDLK_y};

/**
 * @brief Represents the key "Z".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key z{SDL_SCANCODE_Z, SDLK_z};

/**
 * @brief Represents the key "1".
 *
 * @note This is not for a potential "1" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key one{SDL_SCANCODE_1, SDLK_1};

/**
 * @brief Represents the key "2".
 *
 * @note This is not for a potential "2" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key two{SDL_SCANCODE_2, SDLK_2};

/**
 * @brief Represents the key "3".
 *
 * @note This is not for a potential "3" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key three{SDL_SCANCODE_3, SDLK_3};

/**
 * @brief Represents the key "4".
 *
 * @note This is not for a potential "4" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key four{SDL_SCANCODE_4, SDLK_4};

/**
 * @brief Represents the key "5".
 *
 * @note This is not for a potential "5" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key five{SDL_SCANCODE_5, SDLK_5};

/**
 * @brief Represents the key "6".
 *
 * @note This is not for a potential "6" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key six{SDL_SCANCODE_6, SDLK_6};

/**
 * @brief Represents the key "7".
 *
 * @note This is not for a potential "7" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key seven{SDL_SCANCODE_7, SDLK_7};

/**
 * @brief Represents the key "8".
 *
 * @note This is not for a potential "8" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key eight{SDL_SCANCODE_8, SDLK_8};

/**
 * @brief Represents the key "9".
 *
 * @note This is not for a potential "9" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key nine{SDL_SCANCODE_9, SDLK_9};

/**
 * @brief Represents the key "0".
 *
 * @note This is not for a potential "0" key on the key pad.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key zero{SDL_SCANCODE_0, SDLK_0};

/**
 * @brief Represents the function key "F1".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f1{SDL_SCANCODE_F1, SDLK_F1};

/**
 * @brief Represents the function key "F2".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f2{SDL_SCANCODE_F2, SDLK_F2};

/**
 * @brief Represents the function key "F3".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f3{SDL_SCANCODE_F3, SDLK_F3};

/**
 * @brief Represents the function key "F4".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f4{SDL_SCANCODE_F4, SDLK_F4};

/**
 * @brief Represents the function key "F5".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f5{SDL_SCANCODE_F5, SDLK_F5};

/**
 * @brief Represents the function key "F6".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f6{SDL_SCANCODE_F6, SDLK_F6};

/**
 * @brief Represents the function key "F7".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f7{SDL_SCANCODE_F7, SDLK_F7};

/**
 * @brief Represents the function key "F8".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f8{SDL_SCANCODE_F8, SDLK_F8};

/**
 * @brief Represents the function key "F9".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f9{SDL_SCANCODE_F9, SDLK_F9};

/**
 * @brief Represents the function key "F10".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f10{SDL_SCANCODE_F10, SDLK_F10};

/**
 * @brief Represents the function key "F11".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f11{SDL_SCANCODE_F11, SDLK_F11};

/**
 * @brief Represents the function key "F12".
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key f12{SDL_SCANCODE_F12, SDLK_F12};

/**
 * @brief Represents the left arrow key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key left{SDL_SCANCODE_LEFT, SDLK_LEFT};

/**
 * @brief Represents the right arrow key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key right{SDL_SCANCODE_RIGHT, SDLK_RIGHT};

/**
 * @brief Represents the up arrow key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key up{SDL_SCANCODE_UP, SDLK_UP};

/**
 * @brief Represents the down arrow key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key down{SDL_SCANCODE_DOWN, SDLK_DOWN};

/**
 * @brief Represents the "Space" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key space{SDL_SCANCODE_SPACE, SDLK_SPACE};

/**
 * @brief Represents the "Enter" key.
 *
 * @note This key is also referred to as the "Return" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key enter{SDL_SCANCODE_RETURN, SDLK_RETURN};

/**
 * @brief Represents the "Escape" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key escape{SDL_SCANCODE_ESCAPE, SDLK_ESCAPE};

/**
 * @brief Represents the "Backspace" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key backspace{SDL_SCANCODE_BACKSPACE, SDLK_BACKSPACE};

/**
 * @brief Represents the "Tab" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key tab{SDL_SCANCODE_TAB, SDLK_TAB};

/**
 * @brief Represents the "Caps Lock" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key caps_lock{SDL_SCANCODE_CAPSLOCK, SDLK_CAPSLOCK};

/**
 * @brief Represents the left "Shift" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key left_shift{SDL_SCANCODE_LSHIFT, SDLK_LSHIFT};

/**
 * @brief Represents the right "Shift" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key right_shift{SDL_SCANCODE_RSHIFT, SDLK_RSHIFT};

/**
 * @brief Represents the left "CTRL" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key left_ctrl{SDL_SCANCODE_LCTRL, SDLK_LCTRL};

/**
 * @brief Represents the right "CTRL" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key right_ctrl{SDL_SCANCODE_RCTRL, SDLK_RCTRL};

/**
 * @brief Represents the left "Alt" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key left_alt{SDL_SCANCODE_LALT, SDLK_LALT};

/**
 * @brief Represents the right "Alt" key.
 *
 * @since 5.0.0
 *
 * @headerfile key.hpp
 */
inline constexpr key right_alt{SDL_SCANCODE_RALT, SDLK_RALT};

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
inline constexpr key left_gui{SDL_SCANCODE_LGUI, SDLK_LGUI};

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
inline constexpr key right_gui{SDL_SCANCODE_RGUI, SDLK_RGUI};

}  // namespace keys
}  // namespace centurion

#endif  // CENTURION_KEY_HEADER