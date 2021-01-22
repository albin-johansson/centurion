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

#ifndef CENTURION_MESSAGE_BOX_HEADER
#define CENTURION_MESSAGE_BOX_HEADER

#include <SDL.h>

#include <algorithm>    // max, any_of
#include <optional>     // optional
#include <string>       // string
#include <string_view>  // string_view
#include <utility>      // move
#include <vector>       // vector

#include "centurion_cfg.hpp"
#include "color.hpp"
#include "colors.hpp"
#include "detail/stack_resource.hpp"
#include "exception.hpp"
#include "window.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup graphics
/// \{

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
    left_to_right = SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
    right_to_left = SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT
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
    color_scheme() noexcept
    {
      set_color(color_id::background, colors::white);
      set_color(color_id::text, colors::white);
      set_color(color_id::button_background, colors::white);
      set_color(color_id::button_border, colors::white);
      set_color(color_id::button_selected, colors::white);
    }

    /**
     * \brief Sets the color associated with the specified ID.
     *
     * \param id the ID of the color that will be set.
     * \param color the color that will be adapted.
     *
     * \since 5.0.0
     */
    void set_color(const color_id id, const color& color) noexcept
    {
      m_scheme.colors[static_cast<int>(id)] =
          static_cast<SDL_MessageBoxColor>(color);
    }

    /**
     * \brief Returns a pointer to the internal `SDL_MessageBoxColorScheme`.
     *
     * \return a pointer to the internal `SDL_MessageBoxColorScheme`.
     *
     * \since 5.0.0
     */
    [[nodiscard]] auto get() noexcept -> SDL_MessageBoxColorScheme*
    {
      return &m_scheme;
    }

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
  message_box(std::string title, std::string message)
      : m_title{std::move(title)}
      , m_message{std::move(message)}
  {}

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
                   const type type = default_type(),
                   const button_order buttonOrder = default_order())
  {
    show(parent.ptr(), title, message, type, buttonOrder);
  }

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
  static void show(const std::string& title,
                   const std::string& message,
                   const type type = default_type(),
                   const button_order buttonOrder = default_order())
  {
    show(nullptr, title, message, type, buttonOrder);
  }

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
  auto show(const basic_window<T>& parent) -> std::optional<button_id>
  {
    return show(parent.get());
  }

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
  auto show() -> std::optional<button_id>
  {
    return show(nullptr);
  }

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
  void add_button(const button_id id,
                  std::string text,
                  const default_button button = default_button::return_key)
  {
    m_buttons.emplace_back(id, std::move(text), button);
  }

  void set_title(std::nullptr_t) = delete;

  /**
   * \brief Sets the title of the message box.
   *
   * \param title the title that will be used.
   *
   * \since 5.0.0
   */
  void set_title(std::string title)
  {
    m_title = std::move(title);
  }

  /**
   * \brief Sets the message of the message box.
   *
   * \param message the message that will be used.
   *
   * \since 5.0.0
   */
  void set_message(std::string message)
  {
    m_message = std::move(message);
  }

  void set_message(std::nullptr_t) = delete;

  /**
   * \brief Sets the color scheme that will be used by the message box.
   *
   * \note This is not supported on all platforms, so this property is simply
   * not set by default.
   *
   * \param scheme the color scheme that will be used.
   *
   * \since 5.0.0
   */
  void set_color_scheme(const color_scheme& scheme) noexcept
  {
    m_colorScheme = scheme;
  }

  /**
   * \brief Sets the type of the message box.
   *
   * \param type the new type of the message box.
   *
   * \since 5.0.0
   */
  void set_type(const type type) noexcept
  {
    m_type = type;
  }

  /**
   * \brief Sets the button order of the message box.
   *
   * \param order the new button order of the message box.
   *
   * \since 5.0.0
   */
  void set_button_order(const button_order order) noexcept
  {
    m_buttonOrder = order;
  }

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
  [[nodiscard]] auto has_button(const button_id id) const -> bool
  {
    return std::any_of(m_buttons.begin(),
                       m_buttons.end(),
                       [id](const button& button) noexcept {
                         return button.id() == id;
                       });
  }

  /**
   * \brief Returns the title of the message box.
   *
   * \details The default title is "Message box".
   *
   * \return the title of the message box.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto title() const -> std::string_view
  {
    return m_title;
  }

  /**
   * \brief Returns the title of the message box.
   *
   * \details The default title is "Message box".
   *
   * \return the title of the message box.
   *
   * \deprecated Since 5.1.0, use `title()` instead.
   *
   * \since 5.0.0
   */
  [[nodiscard, deprecated]] auto get_title() const -> std::string_view
  {
    return title();
  }

  /**
   * \brief Returns the message of the message box.
   *
   * \details The default message is "N/A".
   *
   * \return the message of the message box.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto message() const -> std::string_view
  {
    return m_message;
  }

  /**
   * \brief Returns the message of the message box.
   *
   * \details The default message is "N/A".
   *
   * \return the message of the message box.
   *
   * \deprecated Since 5.1.0, use `message()` instead.
   *
   * \since 5.0.0
   */
  [[nodiscard, deprecated]] auto get_message() const -> std::string_view
  {
    return message();
  }

  /**
   * \brief Returns the type of the message box.
   *
   * \details The default type is "information".
   *
   * \return the type of the message box.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_type() const noexcept -> type
  {
    return m_type;
  }

  /**
   * \brief Returns the button order of the message box.
   *
   * \details The default button order is "left_to_right".
   *
   * \return the button order used by the message box.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_button_order() const noexcept -> button_order
  {
    return m_buttonOrder;
  }

 private:
  /**
   *
   */
  class button final
  {
   public:
    button(const button_id id,
           std::string text,
           const default_button defaultButton)
        : m_id{id}
        , m_defaultButton{defaultButton}
        , m_text{std::move(text)}
    {}

    /**
     * \brief Returns the ID associated with the button.
     *
     * \return the ID of the button.
     *
     * \since 5.0.0
     */
    [[nodiscard]] auto id() const noexcept -> button_id
    {
      return m_id;
    }

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
    [[nodiscard]] auto convert() const noexcept -> SDL_MessageBoxButtonData
    {
      SDL_MessageBoxButtonData result{};

      result.flags = static_cast<u32>(m_defaultButton);
      result.buttonid = m_id;
      result.text = m_text.c_str();

      return result;
    }

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

  [[nodiscard]] constexpr static auto default_type() noexcept -> type
  {
    return type::information;
  }

  [[nodiscard]] constexpr static auto default_order() noexcept -> button_order
  {
    return button_order::left_to_right;
  }

  [[nodiscard]] constexpr static auto to_flags(
      const type type,
      const button_order buttonOrder) noexcept -> u32
  {
    return static_cast<u32>(type) | static_cast<u32>(buttonOrder);
  }

  static void show(SDL_Window* parent,
                   const std::string& title,
                   const std::string& message,
                   const type type,
                   const button_order buttonOrder)
  {
    if (const auto result =
            SDL_ShowSimpleMessageBox(to_flags(type, buttonOrder),
                                     title.c_str(),
                                     message.c_str(),
                                     parent);
        result == -1) {
      throw sdl_error{};
    }
  }

  auto show(SDL_Window* parent) -> std::optional<button_id>
  {
    SDL_MessageBoxData data{};

    data.window = parent;
    data.title = m_title.c_str();
    data.message = m_message.c_str();
    data.flags = to_flags(m_type, m_buttonOrder);
    data.colorScheme = m_colorScheme ? m_colorScheme->get() : nullptr;

    // Realistically 1-3 buttons, stack buffer for 8 buttons, just in case.
    detail::stack_resource<8 * sizeof(SDL_MessageBoxButtonData)> resource;
    std::pmr::vector<SDL_MessageBoxButtonData> buttonData{resource.get()};

    if (m_buttons.empty()) {
      add_button(0, "OK", default_button::return_key);
    }

    for (const auto& button : m_buttons) {
      buttonData.emplace_back(button.convert());
    }

    data.buttons = buttonData.data();
    data.numbuttons = static_cast<int>(buttonData.size());

    button_id button{-1};
    if (SDL_ShowMessageBox(&data, &button) == -1) {
      throw sdl_error{};
    }

    if (button != -1) {
      return button;
    } else {
      return std::nullopt;
    }
  }
};

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
[[nodiscard]] constexpr auto operator==(
    const message_box::default_button lhs,
    const SDL_MessageBoxButtonFlags rhs) noexcept -> bool
{
  return static_cast<SDL_MessageBoxButtonFlags>(lhs) == rhs;
}

/**
 * \copydoc operator==(message_box::default_button, SDL_MessageBoxButtonFlags)
 */
[[nodiscard]] constexpr auto operator==(
    const SDL_MessageBoxButtonFlags lhs,
    const message_box::default_button rhs) noexcept -> bool
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
[[nodiscard]] constexpr auto operator!=(
    const message_box::default_button lhs,
    const SDL_MessageBoxButtonFlags rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(message_box::default_button, SDL_MessageBoxButtonFlags)
 */
[[nodiscard]] constexpr auto operator!=(
    const SDL_MessageBoxButtonFlags lhs,
    const message_box::default_button rhs) noexcept -> bool
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
[[nodiscard]] constexpr auto operator==(
    const SDL_MessageBoxColorType lhs,
    const message_box::color_id rhs) noexcept -> bool
{
  return lhs == static_cast<SDL_MessageBoxColorType>(rhs);
}

/**
 * \copydoc operator==(SDL_MessageBoxColorType, message_box::color_id)
 */
[[nodiscard]] constexpr auto operator==(
    const message_box::color_id lhs,
    const SDL_MessageBoxColorType rhs) noexcept -> bool
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
[[nodiscard]] constexpr auto operator!=(
    const SDL_MessageBoxColorType lhs,
    const message_box::color_id rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(SDL_MessageBoxColorType, message_box::color_id)
 */
[[nodiscard]] constexpr auto operator!=(
    const message_box::color_id lhs,
    const SDL_MessageBoxColorType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_MESSAGE_BOX_HEADER
