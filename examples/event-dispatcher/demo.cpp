#include <centurion.hpp>

namespace {

// Here we specify that we want to subscribe to four different kinds of events
using event_dispatcher = cen::event_dispatcher<cen::quit_event,
                                               cen::window_event,
                                               cen::keyboard_event,
                                               cen::mouse_button_event>;

void on_mouse_button_event(const cen::mouse_button_event& event)
{
  cen::log_info("mouse_button_event");
}

// Our AAA game class
class aaa_game final {
 public:
  aaa_game()
  {
    // Member function handlers
    m_dispatcher.bind<cen::quit_event>().to<&aaa_game::on_quit_event>(this);
    m_dispatcher.bind<cen::window_event>().to<&aaa_game::on_window_event>(this);

    // Lambda handler
    m_dispatcher.bind<cen::keyboard_event>().to(
        [](const cen::keyboard_event&) { cen::log_info("keyboard_event"); });

    // Free function handler
    m_dispatcher.bind<cen::mouse_button_event>().to<&on_mouse_button_event>();
  }

  auto run() -> int
  {
    m_window.show();

    while (m_running) {
      // All we need to do each frame to handle events is to poll the event dispatcher
      m_dispatcher.poll();

      // Game logic goes here...
    }

    m_window.hide();
    return 0;
  }

 private:
  cen::window m_window;
  event_dispatcher m_dispatcher;
  bool m_running{true};

  // Invoked for each quit event
  void on_quit_event(const cen::quit_event&)
  {
    cen::log_info("quit_event");
    m_running = false;
  }

  // Invoked for each window event
  void on_window_event(const cen::window_event&) { cen::log_info("window_event"); }
};

}  // namespace

int main(int, char**)
{
  const cen::sdl sdl;
  const cen::img img;
  const cen::mix mix;
  const cen::ttf ttf;

  aaa_game game;
  return game.run();
}