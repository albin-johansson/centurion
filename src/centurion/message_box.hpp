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

/**
 * \defgroup message-box Message box
 *
 * \brief Provides message box support.
 */

/// \addtogroup message-box
/// \{

/**
 * \brief Represents different message box types.
 */
enum class message_box_type : uint32 {
  error = SDL_MESSAGEBOX_ERROR,
  warning = SDL_MESSAGEBOX_WARNING,
  information = SDL_MESSAGEBOX_INFORMATION
};

/// \name Message box type functions
/// \{

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

/// \} End of message box type functions

enum class message_box_button_order : uint32 {
#if SDL_VERSION_ATLEAST(2, 0, 12)
  left_to_right = SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
  right_to_left = SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT
#else
  left_to_right,
  right_to_left
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
};

/// \name Message box button order functions
/// \{

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

/// \} End of message box button order functions

enum class message_box_color_type : int {
  background = SDL_MESSAGEBOX_COLOR_BACKGROUND,
  text = SDL_MESSAGEBOX_COLOR_TEXT,
  button_border = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
  button_background = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
  button_selected = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED
};

/// \name Message box color type functions
/// \{

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

/// \} End of message box color type functions

/**
 * \brief Represents color schemes used by message boxes.
 */
class message_box_color_scheme final {
 public:
  /**
   * \brief Creates a color scheme using only white.
   */
  message_box_color_scheme() noexcept
  {
    set_color(message_box_color_type::background, colors::white);
    set_color(message_box_color_type::text, colors::white);
    set_color(message_box_color_type::button_background, colors::white);
    set_color(message_box_color_type::button_border, colors::white);
    set_color(message_box_color_type::button_selected, colors::white);
  }

  /**
   * \brief Updates a color.
   *
   * \param id the identifier of the color that will be updated.
   * \param color the new color (the alpha component is ignored).
   */
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

/**
 * \brief Represents a modal message box that can be used display information, warnings
 * and errors.
 *
 * \details An example usage of this class can be found \subpage page-message-box "here".
 *
 * \note The appearance of message boxes varies depending on the platform, and certain
 * styling options are not available on all platforms.
 */
class message_box final {
 public:
  using button_id = int;

  enum button_flags : uint32 {
    return_key_default = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
    escape_key_default = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
  };

  /// \name Construction
  /// \{

  /**
   * \brief Creates a basic message box.
   */
  message_box() = default;

  /**
   * \brief Creates a message box.
   *
   * \param title the title of the message box.
   * \param message the message of the message box.
   */
  message_box(std::string title, std::string message)
      : mTitle{std::move(title)}
      , mMessage{std::move(message)}
  {}

  /// \} End of construction

  /// \name Direct message box API
  /// \{

  /**
   * \brief Displays a message box.
   *
   * \param parent the parent window.
   * \param title the message box title.
   * \param message the message that will be displayed.
   * \param type the message box type.
   * \param order the button order that will be used.
   *
   * \throws sdl_error if the message box cannot be shown.
   */
  template <typename T>
  static void show(const basic_window<T>& parent,
                   const char* title,
                   const char* message,
                   const message_box_type type = default_type(),
                   const message_box_button_order order = default_order())
  {
    show(parent.ptr(), title, message, type, order);
  }

  /**
   * \brief Displays a message box.
   *
   * \param parent the parent window.
   * \param title the message box title.
   * \param message the message that will be displayed.
   * \param type the message box type.
   * \param order the button order that will be used.
   *
   * \throws sdl_error if the message box cannot be shown.
   */
  template <typename T>
  static void show(const basic_window<T>& parent,
                   const std::string& title,
                   const std::string& message,
                   const message_box_type type = default_type(),
                   const message_box_button_order order = default_order())
  {
    show(parent.ptr(), title.c_str(), message.c_str(), type, order);
  }

  /**
   * \brief Displays a message box.
   *
   * \param title the message box title.
   * \param message the message that will be displayed.
   * \param type the message box type.
   * \param order the button order that will be used.
   *
   * \throws sdl_error if the message box cannot be shown.
   */
  static void show(const char* title,
                   const char* message,
                   const message_box_type type = default_type(),
                   const message_box_button_order order = default_order())
  {
    show(nullptr, title, message, type, order);
  }

  /**
   * \brief Displays a message box.
   *
   * \param title the message box title.
   * \param message the message that will be displayed.
   * \param type the message box type.
   * \param order the button order that will be used.
   *
   * \throws sdl_error if the message box cannot be shown.
   */
  static void show(const std::string& title,
                   const std::string& message,
                   const message_box_type type = default_type(),
                   const message_box_button_order order = default_order())
  {
    show(nullptr, title.c_str(), message.c_str(), type, order);
  }

  /// \} End of direct message box API

  /// \name Instance-based message box API
  /// \{

  /**
   * \brief Shows the message box.
   *
   * \param parent the parent window.
   *
   * \return the identifier of the pressed button; an empty optional is returned if something
   * goes wrong.
   */
  template <typename T>
  auto show(const basic_window<T>& parent) -> std::optional<button_id>
  {
    return show(parent.get());
  }

  /**
   * \brief Shows the message box.
   *
   * \return the identifier of the pressed button; an empty optional is returned if something
   * goes wrong.
   */
  auto show() -> std::optional<button_id> { return show(nullptr); }

  /// \} End of instance-based message box API

  /// \name Mutators
  /// \{

  /**
   * \brief Adds a button to the message box.
   *
   * \param id the unique identifier used by the button.
   * \param text the button label.
   * \param button the button flags.
   *
   * \throws exception if the button identifier is already taken.
   */
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

  /// \} End of mutators

  /// \name Queries
  /// \{

  /**
   * \brief Indicates whether the message box has a button.
   *
   * \param id the identifier of the button to look for.
   *
   * \return `true` if the button was found; `false` otherwise.
   */
  [[nodiscard]] auto has_button(const button_id id) const -> bool
  {
    return std::any_of(mButtons.begin(), mButtons.end(), [id](const button& button) noexcept {
      return button.id == id;
    });
  }

  /// \} End of queries

  /// \name Setters
  /// \{

  /**
   * \brief Sets the title of the message box.
   *
   * \param title the new title.
   */
  void set_title(std::string title) { mTitle = std::move(title); }

  /**
   * \brief Sets the message of the message box.
   *
   * \param message the new message.
   */
  void set_message(std::string message) { mMessage = std::move(message); }

  /**
   * \brief Sets the color scheme used by the message box.
   *
   * \param scheme the new color scheme.
   */
  void set_color_scheme(const message_box_color_scheme& scheme) noexcept
  {
    mColorScheme = scheme;
  }

  /**
   * \brief Sets the type of the message box.
   *
   * \param type the new type.
   */
  void set_type(const message_box_type type) noexcept { mType = type; }

  /**
   * \brief Sets the button order used by the message box.
   *
   * \param order the new button order.
   */
  void set_button_order(const message_box_button_order order) noexcept
  {
    mButtonOrder = order;
  }

  /// \} End of setters

  /// \name Getters
  /// \{

  /**
   * \brief Returns the title of the message box.
   *
   * \return the message box title.
   */
  [[nodiscard]] auto title() const -> const std::string& { return mTitle; }

  /**
   * \brief Returns the message associated with the message box.
   *
   * \return the message box message.
   */
  [[nodiscard]] auto message() const -> const std::string& { return mMessage; }

  /**
   * \brief Returns the type of the message box.
   *
   * \return the message box type.
   */
  [[nodiscard]] auto type() const noexcept -> message_box_type { return mType; }

  /**
   * \brief Returns the button order used by the message box.
   *
   * \return the button order.
   */
  [[nodiscard]] auto button_order() const noexcept -> message_box_button_order
  {
    return mButtonOrder;
  }

  /// \} End of getters

  /// \name Defaults
  /// \{

  /**
   * \brief Returns the default message box type.
   *
   * \return the default type.
   */
  [[nodiscard]] constexpr static auto default_type() noexcept -> message_box_type
  {
    return message_box_type::information;
  }

  /**
   * \brief Returns the default message box button order.
   *
   * \return the default button order.
   */
  [[nodiscard]] constexpr static auto default_order() noexcept -> message_box_button_order
  {
    return message_box_button_order::left_to_right;
  }

  /// \} End of defaults

 private:
  struct button final {
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
  std::optional<message_box_color_scheme> mColorScheme;
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

  auto show(SDL_Window* parent) -> std::optional<button_id>
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
      return std::nullopt;
    }
  }
};

/// \} End of group message-box

}  // namespace cen

#endif  // CENTURION_MESSAGE_BOX_HPP_
