#include "message_box.hpp"

#include "centurion_utils.hpp"
#include "colors.hpp"
#include "error.hpp"

namespace centurion::messagebox {
namespace {

/**
 * @brief Creates and returns an `SDL_MessageBoxButtonData` instance based on
 * the specified attributes.
 *
 * @param hint the button data hint that will be used.
 * @param id the ID of the button.
 * @param text the text that will be displayed on the button, the empty
 * string is used if null.
 *
 * @since 4.0.0
 */
inline auto create_button_data(button_data_hint hint,
                               int id,
                               czstring text) noexcept
    -> SDL_MessageBoxButtonData
{
  return {static_cast<u32>(hint), id, text};
}

}  // namespace

color_scheme::color_scheme() noexcept
{
  set_color(color_type::background, colors::black);
  set_color(color_type::button_border, colors::black);
  set_color(color_type::button_background, colors::black);
  set_color(color_type::button_selected, colors::black);
}

void color_scheme::set_color(color_type type, const color& color) noexcept
{
  m_scheme.colors[index(type)] = static_cast<SDL_MessageBoxColor>(color);
}

auto color_scheme::convert() const noexcept -> SDL_MessageBoxColorScheme
{
  return m_scheme;
}

message_box::message_box() : m_config{std::make_unique<message_box_config>()}
{}

message_box::message_box(czstring title, czstring message) : message_box{}

{
  set_title(title);
  set_message(message);
}

auto message_box::create_buttons() const noexcept
    -> std::vector<SDL_MessageBoxButtonData>
{
  std::vector<SDL_MessageBoxButtonData> result;
  result.reserve(m_buttons.size());

  for (const auto& b : m_buttons) {
    result.push_back(b);
  }

  return result;
}

auto message_box::create_data(SDL_Window* window,
                              const SDL_MessageBoxButtonData* data,
                              const SDL_MessageBoxColorScheme* scheme)
    const noexcept -> SDL_MessageBoxData
{
  const auto flags = static_cast<u32>(m_config->type) |
                     static_cast<u32>(m_config->buttonOrder);
  return {flags,
          window,
          m_title,
          m_message,
          static_cast<int>(m_buttons.size()),
          data,
          scheme};
}

auto message_box::show(SDL_Window* window) -> int
{
  if (m_buttons.empty()) {
    m_buttons.emplace_back(
        create_button_data(button_data_hint::return_key, 0, "OK"));
  }

  const auto buttons = create_buttons();

  std::optional<SDL_MessageBoxColorScheme> optScheme;
  if (m_colorScheme) {
    optScheme.emplace(m_colorScheme->convert());
  }

  const auto scheme = optScheme ? &*optScheme : nullptr;
  const auto data = create_data(window, &buttons.front(), scheme);

  int button = -1;
  if (SDL_ShowMessageBox(&data, &button) == -1) {
    throw detail::core_error("Failed to show message box!");
  }

  return button;
}

void message_box::show(czstring title,
                       czstring message,
                       const message_box_config& config,
                       SDL_Window* window) noexcept
{
  const auto flags =
      static_cast<u32>(config.type) | static_cast<u32>(config.buttonOrder);
  SDL_ShowSimpleMessageBox(flags,
                           title ? title : "Centurion message box",
                           message ? message : "N/A",
                           window);
}

void message_box::add_button(button_data_hint hint,
                             int id,
                             czstring text) noexcept
{
  m_buttons.emplace_back(create_button_data(hint, id, text));
}

void message_box::set_title(czstring title) noexcept
{
  m_title = title ? title : m_title;
}

void message_box::set_message(czstring message) noexcept
{
  m_message = message ? message : m_message;
}

void message_box::set_type(type type) noexcept
{
  m_config->type = type;
}

void message_box::set_button_order(button_order order) noexcept
{
  m_config->buttonOrder = order;
}

void message_box::set_color_scheme(std::optional<color_scheme> scheme) noexcept
{
  this->m_colorScheme = scheme;
}

auto message_box::get_type() const noexcept -> message_box::type
{
  return m_config->type;
}

auto message_box::get_button_order() const noexcept -> message_box::button_order
{
  return m_config->buttonOrder;
}

}  // namespace centurion::messagebox
