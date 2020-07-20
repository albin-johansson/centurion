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
 * @file message_box.hpp
 *
 * @brief Provides the message box API.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_MESSAGE_BOX_HEADER
#define CENTURION_MESSAGE_BOX_HEADER

#include <SDL.h>

#include <vector>

#include "centurion_api.hpp"
#include "centurion_utils.hpp"
#include "color.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * @namespace centurion::messagebox
 *
 * @ingroup graphics
 *
 * @brief Contains the message box API components.
 */
namespace centurion::messagebox {

/**
 * @addtogroup graphics
 * @{
 */

/**
 * @enum button_data_hint
 *
 * @brief Mirrors the `SDL_MessageBoxButtonFlags` enum.
 *
 * @since 3.0.0
 *
 * @headerfile message_box.hpp
 */
enum class button_data_hint {
  none = 0,
  return_key = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
  escape_key = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
};

/**
 * @brief Indicates whether or not the flags represent the same value.
 *
 * @param lhs the left-hand side message box button data hint.
 * @param rhs the right-hand side message box button data hint.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    button_data_hint lhs,
    SDL_MessageBoxButtonFlags rhs) noexcept -> bool
{
  return static_cast<SDL_MessageBoxButtonFlags>(lhs) == rhs;
}

/**
 * @copydoc operator==(button_data_hint, SDL_MessageBoxButtonFlags)
 */
[[nodiscard]] inline constexpr auto operator==(SDL_MessageBoxButtonFlags lhs,
                                               button_data_hint rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not the flags represent the same value.
 *
 * @param lhs the left-hand side message box button data hint.
 * @param rhs the right-hand side message box button data hint.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    button_data_hint lhs,
    SDL_MessageBoxButtonFlags rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(button_data_hint, SDL_MessageBoxButtonFlags)
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_MessageBoxButtonFlags lhs,
                                               button_data_hint rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @enum color_type
 *
 * @brief Mirrors the `SDL_MessageBoxColorType` enum.
 *
 * @since 3.0.0
 *
 * @headerfile message_box.hpp
 */
enum class color_type {
  background = SDL_MESSAGEBOX_COLOR_BACKGROUND,
  button_border = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
  button_background = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
  button_selected = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

/**
 * @brief Indicates whether or not two message box are colors the same.
 *
 * @param lhs the left-hand side message box color.
 * @param rhs the right-hand side message box color.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator==(SDL_MessageBoxColorType lhs,
                                               color_type rhs) noexcept -> bool
{
  return lhs == static_cast<SDL_MessageBoxColorType>(rhs);
}

/**
 * @copydoc operator==(SDL_MessageBoxColorType, color_type)
 */
[[nodiscard]] inline constexpr auto operator==(
    color_type lhs,
    SDL_MessageBoxColorType rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two message box colors aren't the same.
 *
 * @param lhs the left-hand side message box color.
 * @param rhs the right-hand side message box color.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_MessageBoxColorType lhs,
                                               color_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(SDL_MessageBoxColorType, color_type)
 */
[[nodiscard]] inline constexpr auto operator!=(
    color_type lhs,
    SDL_MessageBoxColorType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @class color_scheme
 *
 * @brief A simple wrapper around an `SDL_MessageBoxColorScheme` instance.
 *
 * @since 3.0.0
 *
 * @headerfile message_box.hpp
 */
class color_scheme final {
 public:
  /**
   * @brief Creates a `color_scheme` instance.
   *
   * @since 3.0.0
   */
  CENTURION_API
  color_scheme() noexcept;

  /**
   * @brief Sets the color of a color scheme component.
   *
   * @param type the color scheme component that will be set.
   * @param color the color that will be used.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_color(color_type type, const color& color) noexcept;

  /**
   * @brief Creates and returns the `SDL_MessageBoxColorScheme` equivalent of
   * the color scheme.
   *
   * @return a `SDL_MessageBoxColorScheme` instance that is equivalent to the
   * color scheme.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto convert() const noexcept -> SDL_MessageBoxColorScheme;

 private:
  SDL_MessageBoxColorScheme m_scheme{};

  /**
   * @brief Returns the array index associated with the supplied color scheme
   * type.
   *
   * @param type color scheme type to obtain the index for.
   *
   * @return the array index associated with the supplied color scheme type.
   *
   * @since 3.0.0
   */
  [[nodiscard]] static auto index(color_type type) noexcept -> int
  {
    return static_cast<int>(type);
  }
};

struct message_box_config;

/**
 * @class message_box
 *
 * @brief Represents a modal message box that can be used display
 * information, warnings and errors.
 *
 * @since 3.0.0
 *
 * @headerfile message_box.hpp
 */
class message_box final {
 public:
  /**
   * @enum button_order
   *
   * @brief Provides hints for how the buttons in a message box should be
   * aligned, either left-to-right or right-to-left.
   *
   * @since 4.0.0
   *
   * @headerfile message_box.hpp
   */
  enum class button_order { left_to_right, right_to_left };

  /**
   * @enum type
   *
   * @brief Serves as a hint of the purpose of a message box. Message boxes
   * can indicate errors, warnings and general information.
   *
   * @since 4.0.0
   *
   * @headerfile message_box.hpp
   */
  enum class type {
    error = SDL_MESSAGEBOX_ERROR,
    warning = SDL_MESSAGEBOX_WARNING,
    information = SDL_MESSAGEBOX_INFORMATION
  };

  /**
   * @brief Creates a `message_box` instance.
   *
   * @since 3.0.0
   */
  CENTURION_API
  message_box();

  /**
   * @brief Creates a message box with the specified title and message.
   *
   * @param title the title of the message box, can be null. "Centurion message
   * box" is used if the supplied string is null.
   * @param message the message of the message box, can be null. "N/A" is
   * used if the supplied string is null.
   *
   * @since 3.0.0
   */
  CENTURION_API
  explicit message_box(czstring title, czstring message = nullptr);

  /**
   * @brief Displays the message box.
   *
   * @details If no buttons have been added, the message box will feature an
   * "OK" button.
   *
   * @note This method will block the invoking thread until the user closes
   * the message box.
   *
   * @param window a pointer to the parent window, can safely be null to
   * indicate no parent.
   *
   * @return the ID of the pressed button; -1 if no button was pressed.
   *
   * @throws centurion_exception if the message box cannot be displayed.
   *
   * @since 3.0.0
   */
  CENTURION_API
  auto show(SDL_Window* window = nullptr) -> int;

  /**
   * @brief Creates and displays a message box.
   *
   * @details This method provides a simpler way to create message boxes,
   * compared to creating instances of the `message_box` class.
   *
   * @note This method will block the invoking thread until the user closes
   * the message box.
   *
   * @param title the title of the message box window, can be null. "Centurion
   * message box" is used if the supplied string is null.
   * @param message the message of the message box window, can be null. "N/A"
   * is used if the supplied string is null.
   * @param config the configuration hints of the message box.
   * @param window a pointer to the parent window, can safely be null to
   * indicate no parent.
   *
   * @since 3.0.0
   */
  CENTURION_API
  static void show(czstring title,
                   czstring message,
                   const message_box_config& config,
                   SDL_Window* window = nullptr) noexcept;

  /**
   * @brief Adds a button to the message box.
   *
   * @note If you don't explicitly add a button, there will be an "OK" button
   * added automatically.
   *
   * @param hint the data hint of the button.
   * @param id the ID of the button.
   * @param text the text of the button, if null then the empty string is used.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void add_button(button_data_hint hint, int id, czstring text) noexcept;

  /**
   * @brief Sets the title of the message box.
   *
   * @details This method has no effect if the supplied string is null.
   *
   * @param title the title of the message box, can be null.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_title(czstring title) noexcept;

  /**
   * @brief Sets the message of the message box.
   *
   * @details This method has no effect if the supplied string is null.
   *
   * @param message the message of the message box, can be null.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_message(czstring message) noexcept;

  /**
   * @brief Sets the type of message that the message box represents.
   *
   * @note By default, this property is set to `type::information`.
   *
   * @param type the type of the message box.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_type(type type) noexcept;

  /**
   * @brief Sets the button order of the buttons in the message box.
   *
   * @note By default, this property is set to `button_order::left_to_right`.
   *
   * @param order the button order that will be used.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_button_order(button_order order) noexcept;

  /**
   * @brief Sets the color scheme that will be used by the message box.
   *
   * @note Color schemes aren't supported on all platforms, so the default
   * value is `nothing` for the color scheme.
   *
   * @param scheme the color scheme that will be used; `nothing` indicates
   * that the system defaults should be used.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_color_scheme(std::optional<color_scheme> scheme) noexcept;

  /**
   * @brief Returns the title of the message box.
   *
   * @details The default title is "Centurion message box".
   *
   * @return the title of the message box.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto title() const noexcept -> czstring { return m_title; }

  /**
   * @brief Returns the message of the message box.
   *
   * @details The default message is "N/A".
   *
   * @return the message of the message box.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto message() const noexcept -> czstring { return m_message; }

  /**
   * @brief Returns the color scheme that is used by the message box.
   *
   * @note Color schemes aren't supported on all platforms, so the default
   * value is `nothing` for the color scheme.
   *
   * @return the color scheme that is used by the message box; `nothing` if
   * there is none.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get_color_scheme() const noexcept
      -> std::optional<color_scheme>
  {
    return m_colorScheme;
  }

  /**
   * @brief Returns the type of the message box.
   *
   * @note By default, this property is set to `type::information`.
   *
   * @return the type of the message box.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto get_type() const noexcept -> type;

  /**
   * @brief Returns the button order that is used by the buttons in the message
   * box.
   *
   * @details By default, this property is set to `button_order::left_to_right`.
   *
   * @return the button order that is used by the buttons in the message box.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto get_button_order() const noexcept -> button_order;

 private:
  std::optional<color_scheme> m_colorScheme;
  std::vector<SDL_MessageBoxButtonData> m_buttons;
  czstring m_title{"Centurion message box"};
  czstring m_message{"N/A"};
  std::unique_ptr<message_box_config> m_config;

  /**
   * @brief Creates and returns a vector of `SDL_MessageBoxButtonData`
   * instances.
   *
   * @return a vector of `SDL_MessageBoxButtonData` instances.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto create_buttons() const noexcept
      -> std::vector<SDL_MessageBoxButtonData>;

  /**
   * @brief Creates and returns an `SDL_MessageBoxData` based on the
   * `message_box`.
   *
   * @param window the parent window, can safely be null.
   * @param data a pointer to the first element in the array of buttons.
   * @param scheme a pointer to the color scheme that will be used, set to null
   * by default.
   *
   * @return an `SDL_MessageBoxData` based on the `message_box`.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto create_data(
      SDL_Window* window,
      const SDL_MessageBoxButtonData* data,
      const SDL_MessageBoxColorScheme* scheme = nullptr) const noexcept
      -> SDL_MessageBoxData;
};

/**
 * @struct message_box_config
 *
 * @brief Represents a configuration specification for message boxes and
 * provides the desired type and button order of a message box.
 *
 * @since 4.0.0
 *
 * @headerfile message_box.hpp
 */
struct message_box_config final {
  message_box::type type = message_box::type::information;
  message_box::button_order buttonOrder =
      message_box::button_order::left_to_right;
};

static_assert(std::is_final_v<color_scheme>);
static_assert(std::is_nothrow_default_constructible_v<color_scheme>);
static_assert(std::is_nothrow_destructible_v<color_scheme>);

/// @}

}  // namespace centurion::messagebox

#endif  // CENTURION_MESSAGE_BOX_HEADER
