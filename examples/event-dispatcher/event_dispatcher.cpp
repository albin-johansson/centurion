#include <centurion.hpp>

namespace {

// Here we specify that we want to subscribe to four different kinds of events
using event_dispatcher = cen::EventDispatcher<cen::quit_event,
                                              cen::WindowEvent,
                                              cen::KeyboardEvent,
                                              cen::MouseButtonEvent>;

void on_mouse_button_event(const cen::MouseButtonEvent& event)
{
  cen::log_info("MouseButtonEvent");
}

class Game final {
 public:
  Game()
  {
    // Member function handlers
    m_dispatcher.Bind<cen::quit_event>().To<&Game::on_quit_event>(this);
    m_dispatcher.Bind<cen::WindowEvent>().To<&Game::on_window_event>(this);

    // Lambda handler
    m_dispatcher.Bind<cen::KeyboardEvent>().To(
        [](const cen::KeyboardEvent& event) { cen::log_info("keyboard_event"); });

    // Free function handler
    m_dispatcher.Bind<cen::MouseButtonEvent>().To<&on_mouse_button_event>();
  }

  auto run() -> int
  {
    m_window.Show();

    while (m_running) {
      // All we need to do each frame to handle events is to poll the event dispatcher
      m_dispatcher.Poll();

      // Game logic goes here...
    }

    m_window.Hide();
    return 0;
  }

 private:
  cen::Window m_window;
  event_dispatcher m_dispatcher;
  bool m_running{true};

  // Invoked for each quit event
  void on_quit_event(const cen::quit_event& event)
  {
    cen::log_info("quit_event");
    m_running = false;
  }

  // Invoked for each window event
  void on_window_event(const cen::WindowEvent& event) { cen::log_info("window_event"); }
};

}  // namespace

int main(int, char**)
{
  const cen::sdl sdl;
  const cen::img img;
  const cen::mix mix;
  const cen::ttf ttf;
  Game game;
  return game.run();
}