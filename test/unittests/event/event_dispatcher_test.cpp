#include "events/event_dispatcher.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "log.hpp"

using dispatcher_t = cen::event_dispatcher<cen::quit_event,
                                           cen::controller_button_event,
                                           cen::window_event>;

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
  dispatcher_t dispatcher;

  // clang-format off
  dispatcher.bind<cen::quit_event>().to<&on_quit>();
  dispatcher.bind<cen::controller_button_event>()
            .to<&button_handler::on_event>(&buttonHandler);
  // clang-format on

  bool visitedLambda{};
  dispatcher.bind<cen::window_event>().to([&](const cen::window_event&) {
    visitedLambda = true;
  });

  cen::window_event windowEvent;
  ASSERT_TRUE(cen::event::push(windowEvent));

  cen::quit_event quitEvent;
  ASSERT_TRUE(cen::event::push(quitEvent));

  cen::controller_button_event buttonEvent;
  ASSERT_TRUE(cen::event::push(buttonEvent));

  dispatcher.poll();
  EXPECT_TRUE(buttonHandler.visited);
  EXPECT_TRUE(visitedFreeFunction);
  EXPECT_TRUE(visitedLambda);
}

TEST(EventDispatcher, Reset)
{
  dispatcher_t dispatcher;
  ASSERT_EQ(0, dispatcher.active_count());

  dispatcher.bind<cen::quit_event>().to([](cen::quit_event) {
  });

  dispatcher.bind<cen::window_event>().to([](cen::window_event) {
  });

  dispatcher.bind<cen::controller_button_event>().to(
      [](cen::controller_button_event) {
      });

  EXPECT_EQ(3, dispatcher.active_count());

  dispatcher.reset();
  EXPECT_EQ(0, dispatcher.active_count());

  EXPECT_NO_THROW(dispatcher.reset());
}

TEST(EventDispatcher, ActiveCount)
{
  dispatcher_t dispatcher;
  EXPECT_EQ(0, dispatcher.active_count());

  dispatcher.bind<cen::quit_event>().to([](cen::quit_event) {
  });
  EXPECT_EQ(1, dispatcher.active_count());

  // Bind same event to another lambda, should replace the previous handler
  dispatcher.bind<cen::quit_event>().to([](cen::quit_event) {
  });
  EXPECT_EQ(1, dispatcher.active_count());

  dispatcher.bind<cen::window_event>().to([](cen::window_event) {
  });
  EXPECT_EQ(2, dispatcher.active_count());
}

TEST(EventDispatcher, Size)
{
  cen::event_dispatcher zero;
  EXPECT_EQ(0, zero.size());

  cen::event_dispatcher<cen::quit_event> one;
  EXPECT_EQ(1, one.size());

  cen::event_dispatcher<cen::quit_event, cen::window_event> two;
  EXPECT_EQ(2, two.size());
}

TEST(EventDispatcher, ToString)
{
  dispatcher_t dispatcher;
  cen::log::put(cen::to_string(dispatcher));
}

TEST(EventDispatcher, StreamOperator)
{
  dispatcher_t dispatcher;
  std::cout << "COUT: " << dispatcher << '\n';
}
