#include "events/event_dispatcher.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/log.hpp"

using event_dispatcher =
    cen::event_dispatcher<cen::quit_event, cen::controller_button_event, cen::window_event>;

namespace {

inline bool visitedFreeFunction{};

void on_quit(const cen::quit_event&)
{
  visitedFreeFunction = true;
}

struct button_handler final
{
  void on_event(const cen::controller_button_event&)
  {
    visited = true;
  }

  bool visited{};
};

}  // namespace

TEST(EventDispatcher, Bind)
{
  /* Ensure that it is possible to connect free functions, member functions and
   * lambdas as event handlers.
   */

  cen::event::flush_all();

  button_handler buttonHandler;
  event_dispatcher dispatcher;

  // clang-format off
  dispatcher.bind<cen::quit_event>().to<&on_quit>();
  dispatcher.bind<cen::controller_button_event>()
            .to<&button_handler::on_event>(&buttonHandler);
  // clang-format on

  bool visitedLambda{};
  dispatcher.bind<cen::window_event>().to(
      [&](const cen::window_event&) { visitedLambda = true; });

  cen::window_event windowEvent;
  ASSERT_TRUE(cen::event::push(windowEvent));

  cen::quit_event quitEvent;
  ASSERT_TRUE(cen::event::push(quitEvent));

  cen::controller_button_event buttonEvent;
  ASSERT_TRUE(cen::event::push(buttonEvent));

  dispatcher.poll();
  ASSERT_TRUE(buttonHandler.visited);
  ASSERT_TRUE(visitedFreeFunction);
  ASSERT_TRUE(visitedLambda);
}

TEST(EventDispatcher, Reset)
{
  event_dispatcher dispatcher;
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
  event_dispatcher dispatcher;
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
  event_dispatcher dispatcher;
  cen::log::put(cen::to_string(dispatcher));
}

TEST(EventDispatcher, StreamOperator)
{
  event_dispatcher dispatcher;
  std::clog << dispatcher << '\n';
}
