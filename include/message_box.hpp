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

#ifndef CENTURION_MESSAGE_BOX_HEADER
#define CENTURION_MESSAGE_BOX_HEADER

#include <SDL.h>

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "centurion_api.hpp"
#include "color.hpp"
#include "detail/utils.hpp"
#include "types.hpp"
#include "window.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \addtogroup graphics
 * \{
 */

/**
 * \class message_box
 *
 * \brief Represents a modal message box that can be used display
 * information, warnings and errors.
 *
 * \since 3.0.0
 *
 * \headerfile message_box.hpp
 */
class message_box final
{
 public:
  /**
   * \typedef button_id
   *
   * \brief Used for message box button identifiers.
   *
   * \since 5.0.0
   */
  using button_id = int;

  /**
   * \enum button_order
   *
   * \brief Provides hints for how the buttons in a message box should be
   * aligned, either left-to-right or right-to-left.
   *
   * \since 4.0.0
   *
   * \headerfile message_box.hpp
   */
  enum class button_order
  {
    left_to_right,
    right_to_left
  };

  /**
   * \enum type
   *
   * \brief Serves as a hint of the purpose of a message box. Message boxes
   * can indicate errors, warnings and general information.
   *
   * \since 5.0.0
   *
   * \headerfile message_box.hpp
   */
  enum class type
  {
    error = SDL_MESSAGEBOX_ERROR,
    warning = SDL_MESSAGEBOX_WARNING,
    information = SDL_MESSAGEBOX_INFORMATION
  };

  /**
   * \enum default_button
   *
   * \brief Mirrors the `SDL_MessageBoxButtonFlags` enum.
   *
   * \since 3.0.0
   *
   * \headerfile message_box.hpp
   */
  enum class default_button
  {
    return_key = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
    escape_key = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
  };

  /**
   * \enum color_id
   *
   * \brief Mirrors the `SDL_MessageBoxColorType` enum.
   *
   * \since 5.0.0
   *
   * \headerfile message_box.hpp
   */
  enum class color_id
  {
    background = SDL_MESSAGEBOX_COLOR_BACKGROUND,
    text = SDL_MESSAGEBOX_COLOR_TEXT,
    button_border = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    button_background = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    button_selected = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED
  };

  /**
   * \class color_scheme
   *
   * \brief A simple wrapper around a `SDL_MessageBoxColorScheme` instance.
   *
   * \since 5.0.0
   *
   * \headerfile message_box.hpp
   */
  class color_scheme final
  {
   public:
    /**
     * \brief Creates a color scheme that uses `white` for all colors.
     *
     * \since 5.0.0
     */
    CENTURION_API
    color_scheme() noexcept;

    /**
     * \brief Sets the color associated with the specified ID.
     *
     * \param id the ID of the color that will be set.
     * \param color the color that will be adapted.
     *
     * \since 5.0.0
     */
    CENTURION_API
    void set_color(color_id id, const color& color) noexcept;

    /**
     * \brief Returns a pointer to the internal `SDL_MessageBoxColorScheme`.
     *
     * \return a pointer to the internal `SDL_MessageBoxColorScheme`.
     *
     * \since 5.0.0
     */
    CENTURION_QUERY
    auto get() noexcept -> SDL_MessageBoxColorScheme*;

   private:
    SDL_MessageBoxColorScheme m_scheme{};
  };

  /**
   * \brief Creates a default-initialized message box.
   *
   * \since 5.0.0
   */
  message_box() = default;

  /**
   * \brief Creates a message box with the specified title and message.
   *
   * \param title the title that will be used.
   * \param message the message that will be used.
   *
   * \since 5.0.0
   */
  CENTURION_API
  message_box(std::string title, std::string message);

  /**
   * \brief Displays a message box.
   *
   * \tparam T the traits used by the window.
   *
   * \param parent the parent window.
   * \param title the title of the message box.
   * \param message the message that will be displayed.
   * \param type the type of the message box, defaults to `information`.
   * \param buttonOrder the button order that will be used, defaults to
   * `left_to_right`.
   *
   * \throws sdl_error if something goes wrong when showing the message box.
   *
   * \since 5.0.0
   */
  template <typename T>
  static void show(const basic_window<T>& parent,
                   const std::string& title,
                   const std::string& message,
                   type type = default_type(),
                   button_order buttonOrder = default_order());

  /**
   * \brief Displays a message box.
   *
   * \param title the title of the message box.
   * \param message the message that will be displayed.
   * \param type the type of the message box, defaults to `information`.
   * \param buttonOrder the button order that will be used, defaults to
   * `left_to_right`.
   *
   * \throws sdl_error if something goes wrong when showing the message box.
   *
   * \since 5.0.0
   */
  CENTURION_API
  static void show(const std::string& title,
                   const std::string& message,
                   type type = default_type(),
                   button_order buttonOrder = default_order());

  /**
   * \brief Displays a message box.
   *
   * \tparam T the traits used by the window.
   *
   * \param parent the parent window.
   *
   * \return the ID of the pressed button; `std::nullopt` if no button was
   * pressed.
   *
   * \throws sdl_error if something goes wrong when showing the message box.
   *
   * \since 5.0.0
   */
  template <typename T>
  auto show(const basic_window<T>& parent) -> std::optional<button_id>;

  /**
   * \brief Displays a message box.
   *
   * \details If no buttons have been added by the time this function is
   * called, then an "OK" button is automatically added.
   *
   * \return the ID of the pressed button; `std::nullopt` if no button was
   * pressed.
   *
   * \throws sdl_error if something goes wrong when showing the message box.
   *
   * \since 5.0.0
   */
  CENTURION_API
  auto show() -> std::optional<button_id>;

  /**
   * \brief Adds a button to the message box.
   *
   * \param id the ID of the button.
   * \param text the text of the button.
   * \param button the default button hint.
   *
   * \see `button_flags`
   *
   * \since 5.0.0
   */
  CENTURION_API
  void add_button(button_id id,
                  std::string text,
                  default_button button = default_button::return_key);

  /**
   * \brief Sets the title of the message box.
   *
   * \param title the title that will be used.
   *
   * \since 5.0.0
   */
  CENTURION_API
  void set_title(std::string title);

  void set_title(std::nullptr_t) = delete;

  /**
   * \brief Sets the message of the message box.
   *
   * \param message the message that will be used.
   *
   * \since 5.0.0
   */
  CENTURION_API
  void set_message(std::string message);

  void set_message(std::nullptr_t) = delete;

  /**
   * \brief Sets the color scheme that will be used by the message box.
   *
   * \note This is not supported on all platforms, so this property is simply
   * not set by default.
   *
   * \param colorScheme the color scheme that will be used.
   *
   * \since 5.0.0
   */
  CENTURION_API
  void set_color_scheme(const color_scheme& colorScheme) noexcept;

  /**
   * \brief Sets the type of the message box.
   *
   * \param type the new type of the message box.
   *
   * \since 5.0.0
   */
  CENTURION_API
  void set_type(type type) noexcept;

  /**
   * \brief Sets the button order of the message box.
   *
   * \param order the new button order of the message box.
   *
   * \since 5.0.0
   */
  CENTURION_API
  void set_button_order(button_order order) noexcept;

  /**
   * \brief Indicates whether or not the message box has a button associated
   * with the specified ID.
   *
   * \param id the ID that will be checked.
   *
   * \return `true` if there is a button associated with the supplied ID;
   * `false` otherwise.
   *
   * \since 5.0.0
   */
  CENTURION_QUERY
  auto has_button(button_id id) const noexcept -> bool;

  /**
   * \brief Returns the title of the message box.
   *
   * \details The default title is "Message box".
   *
   * \return the title of the message box.
   *
   * \since 5.0.0
   */
  CENTURION_QUERY
  auto get_title() const -> std::string_view;

  /**
   * \brief Returns the message of the message box.
   *
   * \details The default message is "N/A".
   *
   * \return the message of the message box.
   *
   * \since 5.0.0
   */
  CENTURION_QUERY
  auto get_message() const -> std::string_view;

  /**
   * \brief Returns the type of the message box.
   *
   * \details The default type is "information".
   *
   * \return the type of the message box.
   *
   * \since 5.0.0
   */
  CENTURION_QUERY
  auto get_type() const noexcept -> type;

  /**
   * \brief Returns the button order of the message box.
   *
   * \details The default button order is "left_to_right".
   *
   * \return the button order used by the message box.
   *
   * \since 5.0.0
   */
  CENTURION_QUERY
  auto get_button_order() const noexcept -> button_order;

 private:
  /**
   *
   */
  class button final
  {
   public:
    CENTURION_API
    button(button_id id, std::string text, default_button defaultButton);

    /**
     * \brief Returns the ID associated with the button.
     *
     * \return the ID of the button.
     *
     * \since 5.0.0
     */
    CENTURION_QUERY
    auto id() const noexcept -> button_id;

    /**
     * \brief Returns an `SDL_MessageBoxButtonData` instance that corresponds
     * to the button.
     *
     * \note The returned instance holds a pointer to the string text
     * associated with the button, so it mustn't outlive the lifetime of the
     * button.
     *
     * \return an `SDL_MessageBoxButtonData` instance.
     *
     * \since 5.0.0
     */
    CENTURION_QUERY
    auto convert() const noexcept -> SDL_MessageBoxButtonData;

   private:
    button_id m_id;
    default_button m_defaultButton;
    std::string m_text;
  };

  std::vector<button> m_buttons;
  std::string m_title{"Message box"};
  std::string m_message{"N/A"};
  std::optional<color_scheme> m_colorScheme;
  type m_type{default_type()};
  button_order m_buttonOrder{default_order()};

  [[nodiscard]] constexpr static auto default_flags() noexcept -> u32
  {
    return static_cast<u32>(default_button::return_key) |
           static_cast<u32>(button_order::left_to_right);
  }

  [[nodiscard]] constexpr static auto default_type() noexcept -> type
  {
    return type::information;
  }

  [[nodiscard]] constexpr static auto default_order() noexcept -> button_order
  {
    return button_order::left_to_right;
  }

  [[nodiscard]] constexpr static auto to_flags(
      type type,
      button_order buttonOrder) noexcept -> u32
  {
    return static_cast<u32>(type) | static_cast<u32>(buttonOrder);
  }

  CENTURION_API
  static void show(SDL_Window* parent,
                   const std::string& title,
                   const std::string& message,
                   type type,
                   button_order buttonOrder);

  CENTURION_API
  auto show(SDL_Window* parent) -> std::optional<button_id>;
};

template <typename T>
void message_box::show(const basic_window<T>& parent,
                       const std::string& title,
                       const std::string& message,
                       type type,
                       button_order buttonOrder)
{
  show(parent.ptr(), title, message, type, buttonOrder);
}

template <typename T>
auto message_box::show(const basic_window<T>& parent)
    -> std::optional<button_id>
{
  return show(parent.ptr());
}

static_assert(std::is_default_constructible_v<message_box>);
static_assert(std::is_final_v<message_box>);

/**
 * \brief Indicates whether or not the flags represent the same value.
 *
 * \param lhs the left-hand side message box button flag.
 * \param rhs the right-hand side message box button flag.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    message_box::default_button lhs,
    SDL_MessageBoxButtonFlags rhs) noexcept -> bool
{
  return static_cast<SDL_MessageBoxButtonFlags>(lhs) == rhs;
}

/**
 * \copydoc operator==(message_box::default_button, SDL_MessageBoxButtonFlags)
 */
[[nodiscard]] inline constexpr auto operator==(
    SDL_MessageBoxButtonFlags lhs,
    message_box::default_button rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the flags represent the same value.
 *
 * \param lhs the left-hand side message box button flag.
 * \param rhs the right-hand side message box button flag.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    message_box::default_button lhs,
    SDL_MessageBoxButtonFlags rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(message_box::default_button, SDL_MessageBoxButtonFlags)
 */
[[nodiscard]] inline constexpr auto operator!=(
    SDL_MessageBoxButtonFlags lhs,
    message_box::default_button rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \brief Indicates whether or not two message box are colors the same.
 *
 * \param lhs the left-hand side message box color.
 * \param rhs the right-hand side message box color.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    SDL_MessageBoxColorType lhs,
    message_box::color_id rhs) noexcept -> bool
{
  return lhs == static_cast<SDL_MessageBoxColorType>(rhs);
}

/**
 * \copydoc operator==(SDL_MessageBoxColorType, message_box::color_id)
 */
[[nodiscard]] inline constexpr auto operator==(
    message_box::color_id lhs,
    SDL_MessageBoxColorType rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two message box colors aren't the same.
 *
 * \param lhs the left-hand side message box color.
 * \param rhs the right-hand side message box color.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    SDL_MessageBoxColorType lhs,
    message_box::color_id rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(SDL_MessageBoxColorType, message_box::color_id)
 */
[[nodiscard]] inline constexpr auto operator!=(
    message_box::color_id lhs,
    SDL_MessageBoxColorType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_MESSAGE_BOX_HEADER
