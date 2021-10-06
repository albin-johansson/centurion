#ifndef CENTURION_MESSAGE_BOX_HEADER
#define CENTURION_MESSAGE_BOX_HEADER

#include <SDL.h>

#include <algorithm>    // max, any_of
#include <cstddef>      // nullptr_t
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view
#include <utility>      // move
#include <vector>       // vector

#include "../compiler/features.hpp"
#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/to_underlying.hpp"
#include "../detail/stack_resource.hpp"
#include "button_order.hpp"
#include "color.hpp"
#include "colors.hpp"
#include "message_box_type.hpp"
#include "window.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \class message_box
 *
 * \brief Represents a modal message box that can be used display information, warnings
 * and errors.
 *
 * \note The appearance of message boxes varies depending on the platform, and certain
 * styling options are not available on all platforms.
 *
 * \since 3.0.0
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
   * \enum default_button
   *
   * \brief Provides identifiers that represent default buttons of message boxes.
   *
   * \see `SDL_MessageBoxButtonFlags`
   *
   * \since 3.0.0
   */
  enum class default_button : u32
  {
    return_key = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
    escape_key = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
  };

  /**
   * \enum color_id
   *
   * \brief Represents different message box aspects that can be colored.
   *
   * \see `SDL_MessageBoxColorType`
   *
   * \since 5.0.0
   */
  enum class color_id : int
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
      m_scheme.colors[to_underlying(id)] = static_cast<SDL_MessageBoxColor>(color);
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
   * \param parent the parent window.
   * \param title the title of the message box.
   * \param message the message that will be displayed.
   * \param type the type of the message box, defaults to `information`.
   * \param buttonOrder the button order that will be used, defaults to `left_to_right`.
   *
   * \throws sdl_error if something goes wrong when showing the message box.
   *
   * \since 5.0.0
   */
  template <typename T>
  static void show(const basic_window<T>& parent,
                   const std::string& title,
                   const std::string& message,
                   const message_box_type type = default_type(),
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
   * \param buttonOrder the button order that will be used, defaults to `left_to_right`.
   *
   * \throws sdl_error if something goes wrong when showing the message box.
   *
   * \since 5.0.0
   */
  static void show(const std::string& title,
                   const std::string& message,
                   const message_box_type type = default_type(),
                   const button_order buttonOrder = default_order())
  {
    show(nullptr, title, message, type, buttonOrder);
  }

  /**
   * \brief Displays a message box.
   *
   * \param parent the parent window.
   *
   * \return the ID of the pressed button; `std::nullopt` if no button was pressed.
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
   * \details If no buttons have been added by the time this function is called, then an
   * "OK" button is automatically added.
   *
   * \return the ID of the pressed button; `std::nullopt` if no button was pressed.
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

  [[maybe_unused]] void set_title(std::nullptr_t) = delete;

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

  [[maybe_unused]] void set_message(std::nullptr_t) = delete;

  /**
   * \brief Sets the color scheme that will be used by the message box.
   *
   * \note This is not supported on all platforms, so this property is simply not set by
   * default.
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
  void set_type(const message_box_type type) noexcept
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
   * \brief Indicates whether or not the message box has a button associated with the
   * specified ID.
   *
   * \param id the ID that will be checked.
   *
   * \return `true` if there is a button associated with the supplied ID; `false`
   * otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto has_button(const button_id id) const -> bool
  {
    return std::any_of(m_buttons.begin(),
                       m_buttons.end(),
                       [id](const button& button) noexcept { return button.id() == id; });
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
   * \brief Returns the message of the message box.
   *
   * \details The default message is "n/a".
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
   * \brief Returns the type of the message box.
   *
   * \details The default type is "information".
   *
   * \return the type of the message box.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto type() const noexcept -> message_box_type
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
  class button final
  {
   public:
    button(const button_id id, std::string text, const default_button defaultButton)
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
     * \brief Returns an `SDL_MessageBoxButtonData` instance that corresponds to the
     * button.
     *
     * \note The returned instance holds a pointer to the string text associated with the
     * button, so it mustn't outlive the lifetime of the button.
     *
     * \return an `SDL_MessageBoxButtonData` instance.
     *
     * \since 5.0.0
     */
    [[nodiscard]] auto convert() const noexcept -> SDL_MessageBoxButtonData
    {
      SDL_MessageBoxButtonData result{};

      result.flags = to_underlying(m_defaultButton);
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
  std::string m_message{"n/a"};
  std::optional<color_scheme> m_colorScheme;
  message_box_type m_type{default_type()};
  button_order m_buttonOrder{default_order()};

  [[nodiscard]] constexpr static auto default_type() noexcept -> message_box_type
  {
    return message_box_type::information;
  }

  [[nodiscard]] constexpr static auto default_order() noexcept -> button_order
  {
    return button_order::left_to_right;
  }

  [[nodiscard]] constexpr static auto to_flags(const message_box_type type,
                                               const button_order buttonOrder) noexcept -> u32
  {
    return to_underlying(type) | to_underlying(buttonOrder);
  }

  static void show(SDL_Window* parent,
                   const std::string& title,
                   const std::string& message,
                   const message_box_type type,
                   const button_order buttonOrder)
  {
    if (-1 == SDL_ShowSimpleMessageBox(to_flags(type, buttonOrder),
                                       title.c_str(),
                                       message.c_str(),
                                       parent))
    {
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

#if CENTURION_HAS_FEATURE_MEMORY_RESOURCE
    // Realistically 1-3 buttons, stack buffer for 8 buttons, just in case.
    detail::stack_resource<8 * sizeof(SDL_MessageBoxButtonData)> resource;
    std::pmr::vector<SDL_MessageBoxButtonData> buttonData{resource.get()};
#else
    std::vector<SDL_MessageBoxButtonData> buttonData;
    buttonData.reserve(8);
#endif  // CENTURION_HAS_STD_MEMORY_RESOURCE

    if (m_buttons.empty()) {
      add_button(0, "OK", default_button::return_key);
    }

    for (const auto& button : m_buttons) {
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

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied default button.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(message_box::default_button::return_key) == "return_key"`.
 *
 * \param button the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const message_box::default_button button)
    -> std::string_view
{
  switch (button) {
    case message_box::default_button::return_key:
      return "return_key";

    case message_box::default_button::escape_key:
      return "escape_key";

    default:
      throw cen_error{"Did not recognize message box default button!"};
  }
}

/**
 * \brief Returns a textual version of the supplied color ID
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(message_box::color_id::text) == "text"`.
 *
 * \param id the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const message_box::color_id id) -> std::string_view
{
  switch (id) {
    case message_box::color_id::background:
      return "background";

    case message_box::color_id::text:
      return "text";

    case message_box::color_id::button_border:
      return "button_border";

    case message_box::color_id::button_background:
      return "button_background";

    case message_box::color_id::button_selected:
      return "button_selected";

    default:
      throw cen_error{"Did not recognize message box color ID!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a default button enumerator.
 *
 * \param stream the output stream that will be used.
 * \param button the enumerator that will be printed.
 *
 * \see `to_string(message_box::default_button)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const message_box::default_button button)
    -> std::ostream&
{
  return stream << to_string(button);
}

/**
 * \brief Prints a textual representation of a color ID enumerator.
 *
 * \param stream the output stream that will be used.
 * \param id the enumerator that will be printed.
 *
 * \see `to_string(message_box::color_id)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const message_box::color_id id) -> std::ostream&
{
  return stream << to_string(id);
}

/// \} End of streaming

/// \name Message box default button comparison operators
/// \{

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
[[nodiscard]] constexpr auto operator==(const message_box::default_button lhs,
                                        const SDL_MessageBoxButtonFlags rhs) noexcept -> bool
{
  return static_cast<SDL_MessageBoxButtonFlags>(lhs) == rhs;
}

/// \copydoc operator==(message_box::default_button, SDL_MessageBoxButtonFlags)
[[nodiscard]] constexpr auto operator==(const SDL_MessageBoxButtonFlags lhs,
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
[[nodiscard]] constexpr auto operator!=(const message_box::default_button lhs,
                                        const SDL_MessageBoxButtonFlags rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(message_box::default_button, SDL_MessageBoxButtonFlags)
[[nodiscard]] constexpr auto operator!=(const SDL_MessageBoxButtonFlags lhs,
                                        const message_box::default_button rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of message box default button comparison operators

/// \name Message box color ID comparison operators
/// \{

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
[[nodiscard]] constexpr auto operator==(const SDL_MessageBoxColorType lhs,
                                        const message_box::color_id rhs) noexcept -> bool
{
  return lhs == static_cast<SDL_MessageBoxColorType>(rhs);
}

/// \copydoc operator==(SDL_MessageBoxColorType, message_box::color_id)
[[nodiscard]] constexpr auto operator==(const message_box::color_id lhs,
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
[[nodiscard]] constexpr auto operator!=(const SDL_MessageBoxColorType lhs,
                                        const message_box::color_id rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(SDL_MessageBoxColorType, message_box::color_id)
[[nodiscard]] constexpr auto operator!=(const message_box::color_id lhs,
                                        const SDL_MessageBoxColorType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of message box color ID comparison operators

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_MESSAGE_BOX_HEADER
