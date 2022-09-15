/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_MESSAGE_BOX_HPP_
#define CENTURION_MESSAGE_BOX_HPP_

#include <SDL.h>

#include <algorithm>    // max, any_of
#include <optional>     // optional, nullopt
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view
#include <utility>      // move
#include <vector>       // vector

#include "color.hpp"
#include "common.hpp"
#include "window.hpp"

namespace cen {

enum class message_box_type : uint32
{
  error = SDL_MESSAGEBOX_ERROR,
  warning = SDL_MESSAGEBOX_WARNING,
  information = SDL_MESSAGEBOX_INFORMATION
};

[[nodiscard]] constexpr auto to_string(const message_box_type type) -> std::string_view
{
  switch (type) {
    case message_box_type::error:
      return "error";

    case message_box_type::warning:
      return "warning";

    case message_box_type::information:
      return "information";

    default:
      throw exception{"Did not recognize message box type!"};
  }
}

inline auto operator<<(std::ostream& stream, const message_box_type type) -> std::ostream&
{
  return stream << to_string(type);
}

enum class message_box_button_order : uint32
{
#if SDL_VERSION_ATLEAST(2, 0, 12)
  left_to_right = SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
  right_to_left = SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT
#else
  left_to_right,
  right_to_left
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
};

[[nodiscard]] constexpr auto to_string(const message_box_button_order order)
    -> std::string_view
{
  switch (order) {
    case message_box_button_order::left_to_right:
      return "left_to_right";

    case message_box_button_order::right_to_left:
      return "right_to_left";

    default:
      throw exception{"Did not recognize message box button order!"};
  }
}

inline auto operator<<(std::ostream& stream, const message_box_button_order order)
    -> std::ostream&
{
  return stream << to_string(order);
}

enum class message_box_color_type : int
{
  background = SDL_MESSAGEBOX_COLOR_BACKGROUND,
  text = SDL_MESSAGEBOX_COLOR_TEXT,
  button_border = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
  button_background = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
  button_selected = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED
};

[[nodiscard]] constexpr auto to_string(const message_box_color_type type) -> std::string_view
{
  switch (type) {
    case message_box_color_type::background:
      return "background";

    case message_box_color_type::text:
      return "text";

    case message_box_color_type::button_border:
      return "button_border";

    case message_box_color_type::button_background:
      return "button_background";

    case message_box_color_type::button_selected:
      return "button_selected";

    default:
      throw exception{"Did not recognize message box color type!"};
  }
}

inline auto operator<<(std::ostream& stream, const message_box_color_type type)
    -> std::ostream&
{
  return stream << to_string(type);
}

class message_box_color_scheme final
{
 public:
  message_box_color_scheme() noexcept
  {
    set_color(message_box_color_type::background, colors::white);
    set_color(message_box_color_type::text, colors::white);
    set_color(message_box_color_type::button_background, colors::white);
    set_color(message_box_color_type::button_border, colors::white);
    set_color(message_box_color_type::button_selected, colors::white);
  }

  void set_color(const message_box_color_type id, const color& color) noexcept
  {
    assert(to_underlying(id) < 5);
    mScheme.colors[to_underlying(id)] = color.as_message_box_color();
  }

  [[nodiscard]] auto data() noexcept -> SDL_MessageBoxColorScheme* { return &mScheme; }

  [[nodiscard]] auto data() const noexcept -> const SDL_MessageBoxColorScheme*
  {
    return &mScheme;
  }

  [[nodiscard]] auto get() noexcept -> SDL_MessageBoxColorScheme& { return mScheme; }

  [[nodiscard]] auto get() const noexcept -> const SDL_MessageBoxColorScheme&
  {
    return mScheme;
  }

 private:
  SDL_MessageBoxColorScheme mScheme{};
};

/// Represents a modal message box that can be used display information, warnings and errors.
class message_box final
{
 public:
  using button_id = int;

  enum button_flags : uint32
  {
    return_key_default = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
    escape_key_default = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
  };

  message_box() = default;

  message_box(std::string title, std::string message)
      : mTitle{std::move(title)}
      , mMessage{std::move(message)}
  {}

  template <typename T>
  static void show(const basic_window<T>& parent,
                   const char* title,
                   const char* message,
                   const message_box_type type = default_type(),
                   const message_box_button_order order = default_order())
  {
    show(parent.get(), title, message, type, order);
  }

  template <typename T>
  static void show(const basic_window<T>& parent,
                   const std::string& title,
                   const std::string& message,
                   const message_box_type type = default_type(),
                   const message_box_button_order order = default_order())
  {
    show(parent.get(), title.c_str(), message.c_str(), type, order);
  }

  static void show(const char* title,
                   const char* message,
                   const message_box_type type = default_type(),
                   const message_box_button_order order = default_order())
  {
    show(nullptr, title, message, type, order);
  }

  static void show(const std::string& title,
                   const std::string& message,
                   const message_box_type type = default_type(),
                   const message_box_button_order order = default_order())
  {
    show(nullptr, title.c_str(), message.c_str(), type, order);
  }

  template <typename T>
  auto show(const basic_window<T>& parent) -> maybe<button_id>
  {
    return show(parent.get());
  }

  auto show() -> maybe<button_id> { return show(nullptr); }

  void add_button(const button_id id,
                  std::string text,
                  const button_flags button = button_flags::return_key_default)
  {
    if (!has_button(id)) {
      mButtons.emplace_back(id, std::move(text), button);
    }
    else {
      throw exception{"Duplicate message box button ID!"};
    }
  }

  [[nodiscard]] auto has_button(const button_id id) const -> bool
  {
    return std::any_of(mButtons.begin(), mButtons.end(), [id](const button& button) noexcept {
      return button.id == id;
    });
  }

  void set_title(std::string title) { mTitle = std::move(title); }
  void set_message(std::string message) { mMessage = std::move(message); }

  void set_color_scheme(const message_box_color_scheme& scheme) noexcept
  {
    mColorScheme = scheme;
  }

  void set_type(const message_box_type type) noexcept { mType = type; }

  void set_button_order(const message_box_button_order order) noexcept
  {
    mButtonOrder = order;
  }

  [[nodiscard]] auto title() const -> const std::string& { return mTitle; }

  [[nodiscard]] auto message() const -> const std::string& { return mMessage; }

  [[nodiscard]] auto type() const noexcept -> message_box_type { return mType; }

  [[nodiscard]] auto button_order() const noexcept -> message_box_button_order
  {
    return mButtonOrder;
  }

  [[nodiscard]] constexpr static auto default_type() noexcept -> message_box_type
  {
    return message_box_type::information;
  }

  [[nodiscard]] constexpr static auto default_order() noexcept -> message_box_button_order
  {
    return message_box_button_order::left_to_right;
  }

 private:
  struct button final
  {
    button_id id;
    button_flags flags;
    std::string text;

    button(const button_id id, std::string text, const button_flags flags)
        : id{id}
        , flags{flags}
        , text{std::move(text)}
    {}

    [[nodiscard]] auto convert() const noexcept -> SDL_MessageBoxButtonData
    {
      SDL_MessageBoxButtonData result{};

      result.flags = to_underlying(flags);
      result.buttonid = id;
      result.text = text.c_str();

      return result;
    }
  };

  std::vector<button> mButtons;
  std::string mTitle{"Message box"};
  std::string mMessage;
  maybe<message_box_color_scheme> mColorScheme;
  message_box_type mType{default_type()};
  message_box_button_order mButtonOrder{default_order()};

  [[nodiscard]] constexpr static auto to_flags(const message_box_type type,
                                               const message_box_button_order order) noexcept
      -> uint32
  {
    return to_underlying(type) | to_underlying(order);
  }

  static void show(SDL_Window* parent,
                   const char* title,
                   const char* message,
                   const message_box_type type,
                   const message_box_button_order order)
  {
    assert(title);
    assert(message);

    const auto res = SDL_ShowSimpleMessageBox(to_flags(type, order), title, message, parent);
    if (res == -1) {
      throw sdl_error{};
    }
  }

  auto show(SDL_Window* parent) -> maybe<button_id>
  {
    SDL_MessageBoxData data{};

    data.window = parent;
    data.title = mTitle.c_str();
    data.message = mMessage.c_str();
    data.flags = to_flags(mType, mButtonOrder);
    data.colorScheme = mColorScheme ? mColorScheme->data() : nullptr;

    std::vector<SDL_MessageBoxButtonData> buttonData;
    buttonData.reserve(8);

    if (mButtons.empty()) {
      add_button(0, "OK", button_flags::return_key_default);
    }

    for (const auto& button : mButtons) {
      buttonData.emplace_back(button.convert());
    }

    data.buttons = buttonData.data();
    data.numbuttons = isize(buttonData);

    button_id button{-1};
    if (SDL_ShowMessageBox(&data, &button) == -1) {
      throw sdl_error{};
    }

    if (button != -1) {
      return button;
    }
    else {
      return nothing;
    }
  }
};

}  // namespace cen

#endif  // CENTURION_MESSAGE_BOX_HPP_
