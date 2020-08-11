#include "game_controller.hpp"

#include "centurion_exception.hpp"

namespace centurion {

game_controller::game_controller(int joystickIndex)
    : m_controller{SDL_GameControllerOpen(joystickIndex)}
{
  if (!m_controller) {
    throw sdl_error{"Failed to open game controller!"};
  }
}

game_controller::~game_controller() noexcept
{
  if (m_controller) {
    SDL_GameControllerClose(m_controller);
  }
}

auto game_controller::name() const noexcept -> czstring
{
  return SDL_GameControllerName(m_controller);
}

auto game_controller::name(int joystickIndex) noexcept -> czstring
{
  return SDL_GameControllerNameForIndex(joystickIndex);
}

auto game_controller::get_button_state(
    game_controller_button button) const noexcept -> button_state
{
  const auto state = SDL_GameControllerGetButton(
      m_controller, static_cast<SDL_GameControllerButton>(button));
  return static_cast<button_state>(state);
}

auto game_controller::is_button_pressed(
    game_controller_button button) const noexcept -> bool
{
  return get_button_state(button) == button_state::pressed;
}

auto game_controller::is_button_released(
    game_controller_button button) const noexcept -> bool
{
  return get_button_state(button) == button_state::released;
}

auto game_controller::get_joystick() noexcept -> SDL_Joystick*
{
  return SDL_GameControllerGetJoystick(m_controller);
}

void game_controller::update() noexcept
{
  SDL_GameControllerUpdate();
}

void game_controller::set_polling(bool polling) noexcept
{
  SDL_GameControllerEventState(polling ? SDL_ENABLE : SDL_DISABLE);
}

auto game_controller::is_valid(int joystickIndex) noexcept -> bool
{
  return SDL_IsGameController(joystickIndex);
}

auto game_controller::is_polling() noexcept -> bool
{
  return SDL_GameControllerEventState(SDL_QUERY);
}

}  // namespace centurion
