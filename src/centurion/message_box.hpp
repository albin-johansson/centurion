#ifndef CENTURION_MESSAGE_BOX_HPP_
#define CENTURION_MESSAGE_BOX_HPP_

#include <SDL.h>

#include <algorithm>    // max, any_of
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view
#include <utility>      // move
#include <vector>       // vector

#include "color.hpp"
#include "common.hpp"
#include "window.hpp"

namespace cen {

enum class MessageBoxType : Uint32 {
  Error = SDL_MESSAGEBOX_ERROR,
  Warning = SDL_MESSAGEBOX_WARNING,
  Information = SDL_MESSAGEBOX_INFORMATION
};

enum class MessageBoxButtonOrder : Uint32 {
#if SDL_VERSION_ATLEAST(2, 0, 12)
  LeftToRight = SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
  RightToLeft = SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT
#else
  LeftToRight,
  RightToLeft
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
};

enum class MessageBoxColorType : int {
  Background = SDL_MESSAGEBOX_COLOR_BACKGROUND,
  Text = SDL_MESSAGEBOX_COLOR_TEXT,
  ButtonBorder = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
  ButtonBackground = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
  ButtonSelected = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED
};

class MessageBoxColorScheme final {
 public:
  /** Creates a color scheme that only uses white. */
  MessageBoxColorScheme() noexcept
  {
    SetColor(MessageBoxColorType::Background, colors::white);
    SetColor(MessageBoxColorType::Text, colors::white);
    SetColor(MessageBoxColorType::ButtonBackground, colors::white);
    SetColor(MessageBoxColorType::ButtonBorder, colors::white);
    SetColor(MessageBoxColorType::ButtonSelected, colors::white);
  }

  void SetColor(const MessageBoxColorType id, const Color& color) noexcept
  {
    mScheme.colors[ToUnderlying(id)] = color.AsMessageBoxColor();
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

class MessageBox final {
 public:
  using button_id = int;

  enum ButtonFlags : Uint32 {
    ReturnKeyDefault = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
    EscapeKeyDefault = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
  };

  MessageBox() = default;

  MessageBox(std::string title, std::string message)
      : mTitle{std::move(title)}
      , mMessage{std::move(message)}
  {}

  template <typename T>
  static void Show(const BasicWindow<T>& parent,
                   const std::string& title,
                   const std::string& message,
                   const MessageBoxType type = GetDefaultType(),
                   const MessageBoxButtonOrder buttonOrder = GetDefaultOrder())
  {
    Show(parent.ptr(), title, message, type, buttonOrder);
  }

  static void Show(const std::string& title,
                   const std::string& message,
                   const MessageBoxType type = GetDefaultType(),
                   const MessageBoxButtonOrder buttonOrder = GetDefaultOrder())
  {
    Show(nullptr, title, message, type, buttonOrder);
  }

  template <typename T>
  auto Show(const BasicWindow<T>& parent) -> std::optional<button_id>
  {
    return Show(parent.get());
  }

  auto Show() -> std::optional<button_id> { return Show(nullptr); }

  void AddButton(const button_id id,
                 std::string text,
                 const ButtonFlags button = ButtonFlags::ReturnKeyDefault)
  {
    mButtons.emplace_back(id, std::move(text), button);
  }

  void SetTitle(std::string title) { mTitle = std::move(title); }

  void SetMessage(std::string message) { mMessage = std::move(message); }

  void SetColorScheme(const MessageBoxColorScheme& scheme) noexcept { mColorScheme = scheme; }

  void SetType(const MessageBoxType type) noexcept { mType = type; }

  void SetButtonOrder(const MessageBoxButtonOrder order) noexcept { mButtonOrder = order; }

  [[nodiscard]] auto HasButton(const button_id id) const -> bool
  {
    return std::any_of(mButtons.begin(), mButtons.end(), [id](const Button& button) noexcept {
      return button.id == id;
    });
  }

  [[nodiscard]] auto GetTitle() const -> const std::string& { return mTitle; }

  [[nodiscard]] auto GetMessage() const -> const std::string& { return mMessage; }

  [[nodiscard]] auto GetType() const noexcept -> MessageBoxType { return mType; }

  [[nodiscard]] auto GetButtonOrder() const noexcept -> MessageBoxButtonOrder
  {
    return mButtonOrder;
  }

  [[nodiscard]] constexpr static auto GetDefaultType() noexcept -> MessageBoxType
  {
    return MessageBoxType::Information;
  }

  [[nodiscard]] constexpr static auto GetDefaultOrder() noexcept -> MessageBoxButtonOrder
  {
    return MessageBoxButtonOrder::LeftToRight;
  }

 private:
  struct Button final {
    button_id id;
    ButtonFlags flags;
    std::string text;

    Button(const button_id id, std::string text, const ButtonFlags flags)
        : id{id}
        , flags{flags}
        , text{std::move(text)}
    {}

    [[nodiscard]] auto Convert() const noexcept -> SDL_MessageBoxButtonData
    {
      SDL_MessageBoxButtonData result{};

      result.flags = ToUnderlying(flags);
      result.buttonid = id;
      result.text = text.c_str();

      return result;
    }
  };

  std::vector<Button> mButtons;
  std::string mTitle{"Message box"};
  std::string mMessage{"N/A"};
  std::optional<MessageBoxColorScheme> mColorScheme;
  MessageBoxType mType{GetDefaultType()};
  MessageBoxButtonOrder mButtonOrder{GetDefaultOrder()};

  [[nodiscard]] constexpr static auto ToFlags(const MessageBoxType type,
                                              const MessageBoxButtonOrder buttonOrder) noexcept
      -> Uint32
  {
    return ToUnderlying(type) | ToUnderlying(buttonOrder);
  }

  static void Show(SDL_Window* parent,
                   const std::string& title,
                   const std::string& message,
                   const MessageBoxType type,
                   const MessageBoxButtonOrder buttonOrder)
  {
    const auto res = SDL_ShowSimpleMessageBox(ToFlags(type, buttonOrder),
                                              title.c_str(),
                                              message.c_str(),
                                              parent);
    if (res == -1) {
      throw SDLError{};
    }
  }

  auto Show(SDL_Window* parent) -> std::optional<button_id>
  {
    SDL_MessageBoxData data{};

    data.window = parent;
    data.title = mTitle.c_str();
    data.message = mMessage.c_str();
    data.flags = ToFlags(mType, mButtonOrder);
    data.colorScheme = mColorScheme ? mColorScheme->data() : nullptr;

    std::vector<SDL_MessageBoxButtonData> buttonData;
    buttonData.reserve(8);

    if (mButtons.empty()) {
      AddButton(0, "OK", ButtonFlags::ReturnKeyDefault);
    }

    for (const auto& button : mButtons) {
      buttonData.emplace_back(button.Convert());
    }

    data.buttons = buttonData.data();
    data.numbuttons = isize(buttonData);

    button_id button{-1};
    if (SDL_ShowMessageBox(&data, &button) == -1) {
      throw SDLError{};
    }

    if (button != -1) {
      return button;
    }
    else {
      return std::nullopt;
    }
  }
};

[[nodiscard]] constexpr auto to_string(const MessageBoxType type) -> std::string_view
{
  switch (type) {
    case MessageBoxType::Error:
      return "Error";

    case MessageBoxType::Warning:
      return "Warning";

    case MessageBoxType::Information:
      return "Information";

    default:
      throw Error{"Did not recognize message box type!"};
  }
}

inline auto operator<<(std::ostream& stream, const MessageBoxType type) -> std::ostream&
{
  return stream << to_string(type);
}

[[nodiscard]] constexpr auto to_string(const MessageBoxButtonOrder order) -> std::string_view
{
  switch (order) {
    case MessageBoxButtonOrder::LeftToRight:
      return "LeftToRight";

    case MessageBoxButtonOrder::RightToLeft:
      return "RightToLeft";

    default:
      throw Error{"Did not recognize message box button order!"};
  }
}

inline auto operator<<(std::ostream& stream, const MessageBoxButtonOrder order)
    -> std::ostream&
{
  return stream << to_string(order);
}

[[nodiscard]] constexpr auto to_string(const MessageBoxColorType type) -> std::string_view
{
  switch (type) {
    case MessageBoxColorType::Background:
      return "Background";

    case MessageBoxColorType::Text:
      return "Text";

    case MessageBoxColorType::ButtonBorder:
      return "ButtonBorder";

    case MessageBoxColorType::ButtonBackground:
      return "ButtonBackground";

    case MessageBoxColorType::ButtonSelected:
      return "ButtonSelected";

    default:
      throw Error{"Did not recognize message box color type!"};
  }
}

inline auto operator<<(std::ostream& stream, const MessageBoxColorType type) -> std::ostream&
{
  return stream << to_string(type);
}

}  // namespace cen

#endif  // CENTURION_MESSAGE_BOX_HPP_
