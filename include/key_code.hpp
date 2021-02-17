/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#ifndef CENTURION_KEY_CODE_HEADER
#define CENTURION_KEY_CODE_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <ostream>  // ostream
#include <string>   // string

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "not_null.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class key_code
 *
 * \brief Represents a key code (or virtual key).
 *
 * \details Key codes are mapped to the current layout of the keyboard and
 * correlate to a `scan_code`. Whilst scan codes identify the *location* of
 * a key press, the corresponding key codes give the key press *meaning* in
 * the context of the current keyboard layout.
 *
 * Keycodes are meant to be layout-dependent. Think of this as "the user pressed
 * the key that is labelled 'Q' on a specific keyboard."
 *
 * For example, if you pressed the key that's two keys to the right of CAPS
 * LOCK on a US QWERTY keyboard, it'll report a scancode of SDL_SCANCODE_S and a
 * keycode of SDLK_S. The same key on a Dvorak keyboard, will report a
 * scancode of SDL_SCANCODE_S and a keycode of SDLK_O.
 *
 * \note Key codes are sometimes referred to as "keysyms" in the SDL
 * documentation.
 *
 * \since 5.0.0
 *
 * \see `scan_code`
 * \see `cen::keycodes`
 *
 * \headerfile key_code.hpp
 */
class key_code final
{
 public:
  /**
   * \brief Creates a `key_code` instance with the `SDLK_UNKNOWN` key code.
   *
   * \since 5.0.0
   */
  constexpr key_code() noexcept = default;

  constexpr key_code(const key_code&) noexcept = default;

  constexpr key_code(key_code&&) noexcept = default;

  /**
   * \brief Creates a `key_code` instance with the specified key code.
   *
   * \param key the key code that will be used.
   *
   * \since 5.0.0
   */
  constexpr /*implicit*/ key_code(SDL_KeyCode key) noexcept : m_key{key}
  {}

  /**
   * \brief Creates a `key_code` instance based on a scan code.
   *
   * \details The created `key_code` will use the key code obtained
   * by converting the specified scan code.
   *
   * \param scancode the scan code that will be converted and used.
   *
   * \see `SDL_GetKeyFromScancode`
   *
   * \since 5.0.0
   */
  explicit key_code(SDL_Scancode scancode) noexcept
      : m_key{static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(scancode))}
  {}

  /**
   * \brief Creates a `key_code` instance based on the specified name.
   *
   * \details If the specified name isn't recognized, `SDLK_UNKNOWN` is used as
   * the key code.
   *
   * \param name the name of the key, mustn't be null.
   *
   * \see `SDL_GetKeyFromName`
   *
   * \since 5.0.0
   */
  explicit key_code(not_null<czstring> name) noexcept
      : m_key{static_cast<SDL_KeyCode>(SDL_GetKeyFromName(name))}
  {}

  constexpr auto operator=(const key_code&) noexcept -> key_code& = default;

  constexpr auto operator=(key_code&&) noexcept -> key_code& = default;

  /**
   * \brief Sets the key code used to the specified key code.
   *
   * \param key the key code that will be used.
   *
   * \return the `key_code` instance.
   *
   * \since 5.0.0
   */
  constexpr auto operator=(SDL_KeyCode key) noexcept -> key_code&
  {
    m_key = key;
    return *this;
  }

  /**
   * \brief Sets the key code used to be the converted version of the
   * supplied scan code.
   *
   * \param scancode the scan code that will be converted and used.
   *
   * \return the `key_code` instance.
   *
   * \since 5.0.0
   */
  auto operator=(SDL_Scancode scancode) noexcept -> key_code&
  {
    m_key = static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(scancode));
    return *this;
  }

  /**
   * \brief Sets the key code used to be the one associated with the
   * specified name.
   *
   * \details If the specified name isn't recognized, `SDLK_UNKNOWN` is used as
   * the key code.
   *
   * \param name the name of the key, mustn't be null.
   *
   * \return the `key_code` instance.
   *
   * \since 5.0.0
   */
  auto operator=(not_null<czstring> name) noexcept -> key_code&
  {
    assert(name);
    m_key = static_cast<SDL_KeyCode>(SDL_GetKeyFromName(name));
    return *this;
  }

  /**
   * \brief Indicates whether or not the stored key code is `SDLK_UNKNOWN`.
   *
   * \return `true` if the internal key code is `SDLK_UNKNOWN`; `false`
   * otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto unknown() const noexcept -> bool
  {
    return m_key == SDLK_UNKNOWN;
  }

  /**
   * \brief Returns the name associated with the key code.
   *
   * \return the name associated with the key code.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return SDL_GetKeyName(m_key);
  }

  /**
   * \brief Returns the corresponding `SDL_Scancode`.
   *
   * \return the scan code associated with the internal key code.
   *
   * \see `SDL_GetScancodeFromKey`
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto to_scan_code() const noexcept -> SDL_Scancode
  {
    return SDL_GetScancodeFromKey(m_key);
  }

  /**
   * \brief Returns the internal key code.
   *
   * \return the internal key code.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto get() const noexcept -> SDL_KeyCode
  {
    return m_key;
  }

  /**
   * \brief Converts to `SDL_KeyCode`.
   *
   * \return the internal key code.
   *
   * \since 5.0.0
   */
  constexpr explicit operator SDL_KeyCode() const noexcept
  {
    return m_key;
  }

  /**
   * \brief Converts to `SDL_Keycode`.
   *
   * \return the internal key code.
   *
   * \note `SDL_Keycode` is just an alias for `i32`.
   *
   * \since 5.0.0
   */
  constexpr explicit operator SDL_Keycode() const noexcept
  {
    return m_key;
  }

  /**
   * \brief Converts to `SDL_Scancode`.
   *
   * \return the scan code associated with the internal key code.
   *
   * \see `SDL_GetScancodeFromKey`
   *
   * \since 5.0.0
   */
  explicit operator SDL_Scancode() const noexcept
  {
    return to_scan_code();
  }

  /**
   * \brief Serializes the key code.
   *
   * \details This function expects that the archive provides an overloaded
   * `operator()`, used for serializing data. This API is based on the Cereal
   * serialization library.
   *
   * \tparam Archive the type of the archive.
   *
   * \param archive the archive used to serialize the key code.
   *
   * \since 5.3.0
   */
  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(m_key);
  }

 private:
  SDL_KeyCode m_key{SDLK_UNKNOWN};
};

/**
 * \brief Returns a textual representation of a key code.
 *
 * \param keyCode the key code that will be converted.
 *
 * \return a textual representation of the key code.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto to_string(const key_code& keyCode) -> std::string
{
  return "[key_code | key: " + keyCode.name() + "]";
}

/**
 * \brief Prints a key code using a stream.
 *
 * \param stream the stream that will be used.
 * \param keyCode the key code that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
inline auto operator<<(std::ostream& stream, const key_code& keyCode)
    -> std::ostream&
{
  stream << to_string(keyCode);
  return stream;
}

/**
 * \brief Indicates whether or not two key codes are the same.
 *
 * \param lhs the left-hand side key code.
 * \param rhs the right-hand side key code.
 *
 * \return `true` if the key codes are the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator==(const key_code& lhs,
                                        const key_code& rhs) noexcept -> bool
{
  return lhs.get() == rhs.get();
}

/**
 * \brief Indicates whether or not two key codes aren't the same.
 *
 * \param lhs the left-hand side key code.
 * \param rhs the right-hand side key code.
 *
 * \return `true` if the key codes aren't the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const key_code& lhs,
                                        const key_code& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \namespace cen::keycodes
 *
 * \brief Provides a collection of `key_code` constants.
 *
 * \details Far from all key codes are provided. Instead, some of the most
 * commonly used key codes are available.
 *
 * \since 5.0.0
 */
namespace keycodes {

/**
 * \brief Represents an unknown key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code unknown;

/**
 * \brief Represents the key with the label "A".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code a{SDLK_a};

/**
 * \brief Represents the key with the label "B".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code b{SDLK_b};

/**
 * \brief Represents the key with the label "C".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code c{SDLK_c};

/**
 * \brief Represents the key with the label "D".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code d{SDLK_d};

/**
 * \brief Represents the key with the label "E".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code e{SDLK_e};

/**
 * \brief Represents the key with the label "F".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f{SDLK_f};

/**
 * \brief Represents the key with the label "G".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code g{SDLK_g};

/**
 * \brief Represents the key with the label "H".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code h{SDLK_h};

/**
 * \brief Represents the key with the label "I".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code i{SDLK_i};

/**
 * \brief Represents the key with the label "J".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code j{SDLK_j};

/**
 * \brief Represents the key with the label "K".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code k{SDLK_k};

/**
 * \brief Represents the key with the label "L".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code l{SDLK_l};

/**
 * \brief Represents the key with the label "M".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code m{SDLK_m};

/**
 * \brief Represents the key with the label "N".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code n{SDLK_n};

/**
 * \brief Represents the key with the label "O".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code o{SDLK_o};

/**
 * \brief Represents the key with the label "P".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code p{SDLK_p};

/**
 * \brief Represents the key with the label "Q".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code q{SDLK_q};

/**
 * \brief Represents the key with the label "R".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code r{SDLK_r};

/**
 * \brief Represents the key with the label "S".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code s{SDLK_s};

/**
 * \brief Represents the key with the label "T".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code t{SDLK_t};

/**
 * \brief Represents the key with the label "U".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code u{SDLK_u};

/**
 * \brief Represents the key with the label "V".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code v{SDLK_v};

/**
 * \brief Represents the key with the label "W".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code w{SDLK_w};

/**
 * \brief Represents the key with the label "X".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code x{SDLK_x};

/**
 * \brief Represents the key with the label "Y".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code y{SDLK_y};

/**
 * \brief Represents the key with the label "Z".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code z{SDLK_z};

/**
 * \brief Represents the key with the label "1".
 *
 * \note This is not for a potential "1" key on the key pad.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code one{SDLK_1};

/**
 * \brief Represents the key with the label "2".
 *
 * \note This is not for a potential "2" key on the key pad.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code two{SDLK_2};

/**
 * \brief Represents the key with the label "3".
 *
 * \note This is not for a potential "3" key on the key pad.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code three{SDLK_3};

/**
 * \brief Represents the key with the label "4".
 *
 * \note This is not for a potential "4" key on the key pad.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code four{SDLK_4};

/**
 * \brief Represents the key with the label "5".
 *
 * \note This is not for a potential "5" key on the key pad.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code five{SDLK_5};

/**
 * \brief Represents the key with the label "6".
 *
 * \note This is not for a potential "6" key on the key pad.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code six{SDLK_6};

/**
 * \brief Represents the key with the label "7".
 *
 * \note This is not for a potential "7" key on the key pad.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code seven{SDLK_7};

/**
 * \brief Represents the key with the label "8".
 *
 * \note This is not for a potential "8" key on the key pad.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code eight{SDLK_8};

/**
 * \brief Represents the key with the label "9".
 *
 * \note This is not for a potential "9" key on the key pad.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code nine{SDLK_9};

/**
 * \brief Represents the key with the label "0".
 *
 * \note This is not for a potential "0" key on the key pad.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code zero{SDLK_0};

/**
 * \brief Represents the function key "F1".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f1{SDLK_F1};

/**
 * \brief Represents the function key "F2".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f2{SDLK_F2};

/**
 * \brief Represents the function key "F3".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f3{SDLK_F3};

/**
 * \brief Represents the function key "F4".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f4{SDLK_F4};

/**
 * \brief Represents the function key "F5".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f5{SDLK_F5};

/**
 * \brief Represents the function key "F6".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f6{SDLK_F6};

/**
 * \brief Represents the function key "F7".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f7{SDLK_F7};

/**
 * \brief Represents the function key "F8".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f8{SDLK_F8};

/**
 * \brief Represents the function key "F9".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f9{SDLK_F9};

/**
 * \brief Represents the function key "F10".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f10{SDLK_F10};

/**
 * \brief Represents the function key "F11".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f11{SDLK_F11};

/**
 * \brief Represents the function key "F12".
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code f12{SDLK_F12};

/**
 * \brief Represents the left arrow key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code left{SDLK_LEFT};

/**
 * \brief Represents the right arrow key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code right{SDLK_RIGHT};

/**
 * \brief Represents the up arrow key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code up{SDLK_UP};

/**
 * \brief Represents the down arrow key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code down{SDLK_DOWN};

/**
 * \brief Represents the "Space" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code space{SDLK_SPACE};

/**
 * \brief Represents the "Enter" key.
 *
 * \note This key is also referred to as the "Return" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code enter{SDLK_RETURN};

/**
 * \brief Represents the "Escape" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code escape{SDLK_ESCAPE};

/**
 * \brief Represents the "Backspace" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code backspace{SDLK_BACKSPACE};

/**
 * \brief Represents the "Tab" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code tab{SDLK_TAB};

/**
 * \brief Represents the "Caps Lock" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code caps_lock{SDLK_CAPSLOCK};

/**
 * \brief Represents the left "Shift" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code left_shift{SDLK_LSHIFT};

/**
 * \brief Represents the right "Shift" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code right_shift{SDLK_RSHIFT};

/**
 * \brief Represents the left "CTRL" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code left_ctrl{SDLK_LCTRL};

/**
 * \brief Represents the right "CTRL" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code right_ctrl{SDLK_RCTRL};

/**
 * \brief Represents the left "Alt" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code left_alt{SDLK_LALT};

/**
 * \brief Represents the right "Alt" key.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code right_alt{SDLK_RALT};

/**
 * \brief Represents the left "GUI" key.
 *
 * \details On Windows, this is the "Windows key"; for macs it's the "CMD" key,
 * etc.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code left_gui{SDLK_LGUI};

/**
 * \brief Represents the right "GUI" key.
 *
 * \details On Windows, this is the "Windows" key; for macs it's the "CMD" key,
 * etc.
 *
 * \since 5.0.0
 *
 * \headerfile key.hpp
 */
inline constexpr key_code right_gui{SDLK_RGUI};

}  // namespace keycodes

/// \}

}  // namespace cen

#endif  // CENTURION_KEY_CODE_HEADER