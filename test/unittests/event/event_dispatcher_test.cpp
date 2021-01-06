#include "event_dispatcher.hpp"

#include <gtest/gtest.h>

namespace {

using dispatcher_t =
    cen::experimental::event_dispatcher<cen::quit_event,
                                        cen::controller_button_event,
                                        cen::controller_axis_event>;

void on_quit(const cen::quit_event&)
{
  std::cout << "Received quit_event!\n";
}

class button_handler final
{
 public:
  void on_event(const cen::controller_button_event&)
  {
    std::cout << "Received controller_button_event!\n";
  }
};

}  // namespace

TEST(EventDispatcher, Foo)
{
  cen::event::flush_all();

  button_handler buttonHandler;
  dispatcher_t dispatcher;

//  dispatcher.on<cen::quit_event>().bind<&on_quit>();
//
//  dispatcher.on<cen::controller_button_event>().bind<&button_handler::on_event>(
//      &buttonHandler);
//
//  dispatcher.on<cen::controller_axis_event>().bind(
//      [](const cen::controller_axis_event& event) {
//        std::cout << "Received controller_axis_event!\n";
//      });

  dispatcher.reset();

  dispatcher.bind<cen::quit_event, &on_quit>();
  dispatcher.bind<cen::controller_button_event, &button_handler::on_event>(
      &buttonHandler);
  dispatcher.bind<cen::quit_event>([](const cen::quit_event& event) {
    std::cout << "Quit!\n";
  });

  SDL_Event e{};

  e.type = SDL_CONTROLLERAXISMOTION;
  SDL_PushEvent(&e);

  e.type = SDL_QUIT;
  SDL_PushEvent(&e);

  e.type = SDL_CONTROLLERBUTTONDOWN;
  SDL_PushEvent(&e);

  dispatcher.poll();
}
