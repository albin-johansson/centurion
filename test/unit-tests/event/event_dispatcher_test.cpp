#include "events/event_dispatcher.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/logging.hpp"

using EventDispatcher =
    cen::EventDispatcher<cen::quit_event, cen::ControllerButtonEvent, cen::window_event>;

namespace {

inline bool gVisitedFreeFunction{};

void OnQuit(const cen::quit_event&)
{
  gVisitedFreeFunction = true;
}

struct ButtonHandler final {
  void OnEvent(const cen::ControllerButtonEvent&) { visited = true; }

  bool visited{};
};

}  // namespace

TEST(EventDispatcher, Bind)
{
  /* Ensure that it is possible to connect free functions, member functions, and
     lambdas as event handlers. */

  cen::Event::FlushAll();

  ButtonHandler handler;
  EventDispatcher dispatcher;

  dispatcher.Bind<cen::quit_event>().To<&OnQuit>();
  dispatcher.Bind<cen::ControllerButtonEvent>().To<&ButtonHandler::OnEvent>(&handler);

  bool visitedLambda{};
  dispatcher.Bind<cen::window_event>().To(
      [&](const cen::window_event&) { visitedLambda = true; });

  cen::window_event windowEvent;
  ASSERT_TRUE(cen::Event::Push(windowEvent));

  cen::quit_event quitEvent;
  ASSERT_TRUE(cen::Event::Push(quitEvent));

  cen::ControllerButtonEvent buttonEvent;
  ASSERT_TRUE(cen::Event::Push(buttonEvent));

  dispatcher.Poll();
  ASSERT_TRUE(handler.visited);
  ASSERT_TRUE(gVisitedFreeFunction);
  ASSERT_TRUE(visitedLambda);
}

TEST(EventDispatcher, Reset)
{
  EventDispatcher dispatcher;
  ASSERT_EQ(0, dispatcher.GetActiveCount());

  dispatcher.Bind<cen::quit_event>().To([](cen::quit_event) {});
  dispatcher.Bind<cen::window_event>().To([](cen::window_event) {});
  dispatcher.Bind<cen::ControllerButtonEvent>().To([](cen::ControllerButtonEvent) {});

  ASSERT_EQ(3, dispatcher.GetActiveCount());

  dispatcher.Reset();
  ASSERT_EQ(0, dispatcher.GetActiveCount());

  ASSERT_NO_THROW(dispatcher.Reset());
}

TEST(EventDispatcher, GetActiveCount)
{
  EventDispatcher dispatcher;
  ASSERT_EQ(0, dispatcher.GetActiveCount());

  dispatcher.Bind<cen::quit_event>().To([](cen::quit_event) {});
  ASSERT_EQ(1, dispatcher.GetActiveCount());

  // Bind same event to another lambda, should replace the previous handler
  dispatcher.Bind<cen::quit_event>().To([](cen::quit_event) {});
  ASSERT_EQ(1, dispatcher.GetActiveCount());

  dispatcher.Bind<cen::window_event>().To([](cen::window_event) {});
  ASSERT_EQ(2, dispatcher.GetActiveCount());
}

TEST(EventDispatcher, GetSize)
{
  cen::EventDispatcher zero;
  ASSERT_EQ(0, zero.GetSize());

  cen::EventDispatcher<cen::quit_event> one;
  ASSERT_EQ(1, one.GetSize());

  cen::EventDispatcher<cen::quit_event, cen::window_event> two;
  ASSERT_EQ(2, two.GetSize());
}

TEST(EventDispatcher, ToString)
{
  EventDispatcher dispatcher;
  cen::log_info_raw(cen::to_string(dispatcher));
}

TEST(EventDispatcher, StreamOperator)
{
  EventDispatcher dispatcher;
  std::clog << dispatcher << '\n';
}
