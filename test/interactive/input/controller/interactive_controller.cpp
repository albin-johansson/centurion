#include <array>    // array
#include <cstddef>  // size_t

#include "centurion.hpp"
#include "controller.hpp"
#include "event.hpp"
#include "event_dispatcher.hpp"
#include "renderer.hpp"
#include "window.hpp"

namespace {

class interactive_controller final
{
 public:
  interactive_controller()
      : m_window{"Controller demo"}
      , m_renderer{m_window}
      , m_rect{{0, 0}, {100, 100}}
  {
    cen::controller::load_mappings("resources/controllers.txt");

    // clang-format off
    m_dispatcher.bind<cen::quit_event>()
                .to<&interactive_controller::on_quit_event>(this);

    m_dispatcher.bind<cen::controller_button_event>()
                .to<&interactive_controller::on_controller_button_event>(this);

    m_dispatcher.bind<cen::controller_axis_event>()
                .to<&interactive_controller::on_controller_axis_event>(this);
    // clang-format on
  }

  void run()
  {
    cen::event event;
    cen::controller controller;

    m_window.show();

    while (m_running) {
      m_dispatcher.poll();

      controller.set_led(m_currentColor);

      m_rect.set_x(m_rect.x() + m_dx);
      m_rect.set_y(m_rect.y() + m_dy);

      render();
    }

    m_window.hide();
  }

 private:
  inline static constexpr cen::i16 m_deadZone = 15'000;
  inline static constexpr auto m_step = 0.0002f;

  inline static constexpr std::array m_colors{cen::colors::pink,
                                              cen::colors::steel_blue,
                                              cen::colors::red};

  cen::window m_window;
  cen::renderer m_renderer;
  cen::frect m_rect;
  float m_dx{};
  float m_dy{};
  std::size_t m_colorIndex{};
  cen::color m_currentColor{m_colors.at(m_colorIndex)};
  bool m_running{true};

  using dispatcher_t = cen::event_dispatcher<cen::quit_event,
                                             cen::controller_button_event,
                                             cen::controller_axis_event>;
  dispatcher_t m_dispatcher;

  void render()
  {
    m_renderer.clear_with(m_currentColor);

    m_renderer.set_color(cen::colors::dark_red);
    m_renderer.fill_rect(m_rect);

    m_renderer.present();
  }

  void change_color()
  {
    ++m_colorIndex;
    m_currentColor = m_colors.at(m_colorIndex % m_colors.size());
  }

  void update_position(const cen::controller_axis_event& event)
  {
    const auto value = event.value();  // -32'768 to 32'767
    const auto axis = event.axis();

    const auto updateWith = [](float& diff, const int value) {
      if ((value < -m_deadZone) || (value > m_deadZone)) {
        diff = static_cast<float>(value) * m_step;
      } else {
        diff = 0;
      }
    };

    if (axis == cen::controller_axis::left_x) {
      updateWith(m_dx, value);

    } else if (axis == cen::controller_axis::left_y) {
      updateWith(m_dy, value);
    }
  }

  void on_quit_event(const cen::quit_event& event)
  {
    m_running = false;
  }

  void on_controller_button_event(const cen::controller_button_event& event)
  {
    if (event.released()) {
      change_color();
    }
  }

  void on_controller_axis_event(const cen::controller_axis_event& event)
  {
    update_position(event);
  }
};

}  // namespace

int main(int, char**)
{
  const cen::library lib;

  interactive_controller ic;
  ic.run();

  return 0;
}