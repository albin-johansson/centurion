#include <array>  // array
#include <centurion.hpp>
#include <cstddef>   // size_t
#include <optional>  // optional

namespace {

constexpr std::array colors = {cen::colors::hot_pink,
                               cen::colors::dark_olive_green,
                               cen::colors::dark_turquoise};

}  // namespace

int main(int, char**)
{
  const cen::sdl sdl;

  cen::window window {"event_handler demo"};
  cen::renderer renderer = window.make_renderer();

  window.show();

  // Create our event handler, which provides our event management API
  cen::event_handler handler;

  std::size_t colorIndex = 0;
  std::optional<cen::ipoint> mousePos;

  bool running = true;
  while (running) {
    // Go through the event queue, handling the different pending events
    while (handler.poll()) {
      if (handler.is<cen::quit_event>()) {
        running = false;
        break;
      }
      else if (handler.is(cen::event_type::key_down)) {
        // We received a keyboard event, so get the internal event representation.
        const auto& keyboardEvent = handler.get<cen::keyboard_event>();
        if (!keyboardEvent.repeated()) {
          colorIndex = (colorIndex + 1u) % colors.size();
        }
      }
      else if (const auto* buttonEvent = handler.try_get<cen::mouse_button_event>()) {
        if (buttonEvent->pressed()) {
          mousePos = buttonEvent->position();
        }
      }
    }

    renderer.clear_with(colors.at(colorIndex));

    if (mousePos) {
      renderer.set_color(colors.at((colorIndex + 1u) % colors.size()));

      cen::irect rect {*mousePos, {6, 6}};
      rect.offset_x(-3);
      rect.offset_y(-3);

      renderer.fill_rect(rect);
    }

    renderer.present();
  }

  window.hide();

  return 0;
}