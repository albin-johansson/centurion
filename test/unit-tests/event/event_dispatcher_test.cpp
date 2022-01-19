#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/logging.hpp"
#include "event.hpp"

using EventDispatcher =
    cen::event_dispatcher<cen::quit_event, cen::controller_button_event, cen::window_event>;

namespace {

inline bool gVisitedFreeFunction{};

void OnQuit(const cen::quit_event&)
{
  gVisitedFreeFunction = true;
}

struct ButtonHandler final {
  void OnEvent(const cen::controller_button_event&) { visited = true; }

  bool visited{};
};

}  // namespace

TEST(EventDispatcher, Bind)
{
  /* Ensure that it is possible to connect free functions, member functions, and
     lambdas as event handlers. */

  cen::event_handler::flush_all();

  ButtonHandler handler;
  EventDispatcher dispatcher;

  dispatcher.bind<cen::quit_event>().to<&OnQuit>();
  dispatcher.bind<cen::controller_button_event>().to<&ButtonHandler::OnEvent>(&handler);

  bool visitedLambda{};
  dispatcher.bind<cen::window_event>().to(
      [&](const cen::window_event&) { visitedLambda = true; });

  cen::window_event windowEvent;
  ASSERT_TRUE(cen::event_handler::push(windowEvent));

  cen::quit_event quitEvent;
  ASSERT_TRUE(cen::event_handler::push(quitEvent));

  cen::controller_button_event buttonEvent;
  ASSERT_TRUE(cen::event_handler::push(buttonEvent));

  dispatcher.poll();
  ASSERT_TRUE(handler.visited);
  ASSERT_TRUE(gVisitedFreeFunction);
  ASSERT_TRUE(visitedLambda);
}

TEST(EventDispatcher, Reset)
{
  EventDispatcher dispatcher;
  ASSERT_EQ(0, dispatcher.active_count());

  dispatcher.bind<cen::quit_event>().to([](cen::quit_event) {});
  dispatcher.bind<cen::window_event>().to([](cen::window_event) {});
  dispatcher.bind<cen::controller_button_event>().to([](cen::controller_button_event) {});

  ASSERT_EQ(3, dispatcher.active_count());

  dispatcher.reset();
  ASSERT_EQ(0, dispatcher.active_count());

  ASSERT_NO_THROW(dispatcher.reset());
}

TEST(EventDispatcher, ActiveCount)
{
  EventDispatcher dispatcher;
  ASSERT_EQ(0, dispatcher.active_count());

  dispatcher.bind<cen::quit_event>().to([](cen::quit_event) {});
  ASSERT_EQ(1, dispatcher.active_count());

  // Bind same event to another lambda, should replace the previous handler
  dispatcher.bind<cen::quit_event>().to([](cen::quit_event) {});
  ASSERT_EQ(1, dispatcher.active_count());

  dispatcher.bind<cen::window_event>().to([](cen::window_event) {});
  ASSERT_EQ(2, dispatcher.active_count());
}

TEST(EventDispatcher, Size)
{
  cen::event_dispatcher zero;
  ASSERT_EQ(0, zero.size());

  cen::event_dispatcher<cen::quit_event> one;
  ASSERT_EQ(1, one.size());

  cen::event_dispatcher<cen::quit_event, cen::window_event> two;
  ASSERT_EQ(2, two.size());
}

TEST(EventDispatcher, ToString)
{
  EventDispatcher dispatcher;
  cen::log_info_raw(cen::to_string(dispatcher));
}

TEST(EventDispatcher, StreamOperator)
{
  EventDispatcher dispatcher;
  std::cout << dispatcher << '\n';
}
