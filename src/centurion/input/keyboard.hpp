#ifndef CENTURION_KEYBOARD_HEADER
#define CENTURION_KEYBOARD_HEADER

// clang-format off
#include "../compiler/features.hpp"
// clang-format on

#include <SDL.h>

#include <algorithm>  // copy
#include <array>      // array
#include <ostream>    // ostream
#include <string>     // string, to_string

#ifdef CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../compiler/compiler.hpp"
#include "../core/integers.hpp"
#include "key_code.hpp"
#include "key_modifier.hpp"
#include "scan_code.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class keyboard
 *
 * \brief Provides information about the keyboard state.
 *
 * \details Using the keyboard state is an alternative to using events for
 * keyboard input.
 *
 * \see `mouse`
 * \see `has_screen_keyboard()`
 *
 * \since 3.0.0
 */
class keyboard final
{
 public:
  /**
   * \brief Creates a `keyboard` instance.
   *
   * \since 3.0.0
   */
  keyboard() noexcept
  {
    m_states = SDL_GetKeyboardState(&m_nKeys);
  }

  /**
   * \brief Updates the state of the key state object.
   *
   * \note `SDL_PumpEvents` isn't invoked by this function.
   *
   * \since 3.0.0
   */
  void update()
  {
    std::copy(m_states, m_states + m_nKeys, m_previous.begin());
  }

  /**
   * \brief Indicates whether or not the specified key is being pressed.
   *
   * \details This function returns false if the supplied key isn't recognized.
   *
   * \param code the scan code that will be checked.
   *
   * \return `true` if the key is being pressed; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_pressed(const scan_code& code) const noexcept -> bool
  {
    return check_state(code,
                       [this](const SDL_Scancode sc) noexcept { return m_states[sc]; });
  }

  /**
   * \brief Indicates whether or not the specified key is being pressed.
   *
   * \details This function returns false if the supplied key isn't recognized.
   *
   * \note This function is slightly slower that the `scan_code` version.
   *
   * \param code the key code that will be checked.
   *
   * \return `true` if the key is being pressed; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_pressed(const key_code& code) const noexcept -> bool
  {
    return is_pressed(code.to_scan_code());
  }

  /**
   * \brief Indicates whether or not the specified key has been pressed during more than
   * one update of the key state.
   *
   * \details This function returns false if the supplied key isn't recognized.
   *
   * \param code the scan code that will be checked.
   *
   * \return `true` if the key has been held down; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_held(const scan_code& code) const noexcept(on_msvc()) -> bool
  {
    return check_state(code, [this](const SDL_Scancode sc) noexcept(on_msvc()) {
      return m_states[sc] && m_previous[sc];
    });
  }

  /**
   * \brief Indicates whether or not the specified key has been pressed during more than
   * one update of the key state.
   *
   * \details This function returns false if the supplied key isn't recognized.
   *
   * \note This function is slightly slower that the `scan_code` version.
   *
   * \param code the key code that will be checked.
   *
   * \return `true` if the key has been held down; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_held(const key_code& code) const noexcept(on_msvc()) -> bool
  {
    return is_held(code.to_scan_code());
  }

  /**
   * \brief Indicates whether or not a key just became pressed in the last update of the
   * key state.
   *
   * \details This function returns false if the supplied key isn't recognized.
   *
   * \param code the scan code that will be checked.
   *
   * \return `true` if the key has just been pressed; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto just_pressed(const scan_code& code) const noexcept(on_msvc()) -> bool
  {
    return check_state(code, [this](const SDL_Scancode sc) noexcept(on_msvc()) {
      return m_states[sc] && !m_previous[sc];
    });
  }

  /**
   * \brief Indicates whether or not a key just became pressed in the last update of the
   * key state.
   *
   * \details This function returns false if the supplied key isn't recognized.
   *
   * \note This function is slightly slower that the `scan_code` version.
   *
   * \param code the key code that will be checked.
   *
   * \return `true` if the key has just been pressed; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto just_pressed(const key_code& code) const noexcept(on_msvc()) -> bool
  {
    return just_pressed(code.to_scan_code());
  }

  /**
   * \brief Indicates whether or not the specified key was released in the last update of
   * the key state.
   *
   * \details This function returns false if the supplied key isn't recognized.
   *
   * \param code the scan code that will be checked.
   *
   * \return `true` if the key was released; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto just_released(const scan_code& code) const noexcept(on_msvc())
      -> bool
  {
    return check_state(code, [this](const SDL_Scancode sc) noexcept(on_msvc()) {
      return !m_states[sc] && m_previous[sc];
    });
  }

  /**
   * \brief Indicates whether or not the specified key was released in the last update of
   * the key state.
   *
   * \details This function returns false if the supplied key isn't recognized.
   *
   * \note This function is slightly slower that the `scan_code` version.
   *
   * \param code the key code that will be checked.
   *
   * \return `true` if the key was released; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto just_released(const key_code& code) const noexcept(on_msvc()) -> bool
  {
    return just_released(code.to_scan_code());
  }

  /**
   * \brief Indicates whether or not any of the specified modifiers are active.
   *
   * \note Multiple key modifiers can be active at the same time.
   *
   * \param modifiers the modifiers that will be checked.
   *
   * \return `true` if any of the modifiers are active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] static auto is_active(const key_mod modifiers) noexcept -> bool
  {
    return static_cast<SDL_Keymod>(modifiers) & SDL_GetModState();
  }

  /**
   * \brief Returns the total amount of keys.
   *
   * \return the total amount of keys.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto key_count() const noexcept -> int
  {
    return m_nKeys;
  }

 private:
  const u8* m_states{};
  std::array<u8, cen::scan_code::count()> m_previous{};
  int m_nKeys{};

  template <typename Predicate>
  auto check_state(const cen::scan_code& code, Predicate&& predicate) const
      noexcept(noexcept(predicate(code.get()))) -> bool
  {
    const auto sc = code.get();
    if (sc >= 0 && sc < m_nKeys)
    {
      return predicate(sc);
    }
    else
    {
      return false;
    }
  }
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a keyboard.
 *
 * \param keyboard the keyboard instance that will be converted.
 *
 * \return a string that represents the keyboard.
 *
 * \since 6.2.0
 */
[[nodiscard]] inline auto to_string(const keyboard& keyboard) -> std::string
{
#ifdef CENTURION_HAS_FEATURE_FORMAT
  return std::format("keyboard{{#keys: {}}}", keyboard.key_count());
#else
  return "keyboard{#keys: " + std::to_string(keyboard.key_count()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a keyboard.
 *
 * \param stream the output stream that will be used.
 * \param keyboard the keyboard that will be printed.
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const keyboard& keyboard) -> std::ostream&
{
  return stream << to_string(keyboard);
}

/// \} End of streaming

/**
 * \typedef key_state
 *
 * \brief This is provided for backwards compatibility with Centurion 5.
 *
 * \deprecated This is deprecated since Centurion 6.0.0.
 */
using key_state [[deprecated]] = keyboard;

/**
 * \brief Indicates whether or not the platform has screen keyboard support.
 *
 * \return `true` if the current platform has some form of screen keyboard support;
 * `false` otherwise.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto has_screen_keyboard() noexcept -> bool
{
  return SDL_HasScreenKeyboardSupport() == SDL_TRUE;
}

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_KEYBOARD_HEADER
