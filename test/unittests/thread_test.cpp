#include "thread.hpp"

#include <catch.hpp>
#include <iostream>
#include <type_traits>

#include "cen.hpp"

namespace {

auto dummy = [](void*) noexcept -> int { return 0; };

}

static_assert(std::is_same_v<cen::thread::id, SDL_threadID>);
static_assert(std::is_same_v<cen::thread::task_type, SDL_ThreadFunction>);

TEST_CASE("thread::detach", "[thread]")
{
  cen::thread thread{dummy};

  thread.detach();

  CHECK(!thread.joinable());
  CHECK(!thread.was_joined());
  CHECK(thread.was_detached());

  CHECK_NOTHROW(thread.detach());
}

TEST_CASE("thread::join", "[thread]")
{
  cen::thread thread{dummy};

  thread.join();

  CHECK(!thread.joinable());
  CHECK(thread.was_joined());
  CHECK(!thread.was_detached());

  CHECK(thread.join() == 0);
}

TEST_CASE("thread::joinable", "[thread]")
{
  SECTION("Shouldn't be joinable after join")
  {
    cen::thread thread{dummy};

    CHECK(thread.joinable());

    thread.join();

    CHECK(!thread.joinable());
  }

  SECTION("Shouldn't be joinable after detach")
  {
    cen::thread thread{dummy};

    CHECK(thread.joinable());

    thread.detach();

    CHECK(!thread.joinable());
  }
}

TEST_CASE("thread::was_joined", "[thread]")
{
  cen::thread thread{dummy};

  CHECK(!thread.was_joined());

  thread.join();

  CHECK(thread.was_joined());
}

TEST_CASE("thread::was_detached", "[thread]")
{
  cen::thread thread{dummy};

  CHECK(!thread.was_detached());

  thread.detach();

  CHECK(thread.was_detached());
}

TEST_CASE("thread::get_id", "[thread]")
{
  cen::thread thread{dummy};

  CHECK(thread.get_id() == SDL_GetThreadID(thread.get()));
}

TEST_CASE("thread::name", "[thread]")
{
  SECTION("Custom name")
  {
    const auto name = "foobar";
    const cen::thread thread{dummy, name};
    CHECK(thread.name() == name);
  }

  SECTION("Default name")
  {
    const cen::thread thread{dummy};
    CHECK(thread.name() == "thread");
  }
}

TEST_CASE("thread::get", "[thread]")
{
  SECTION("Non-const")
  {
    cen::thread thread{dummy};
    CHECK(thread.get());
  }

  SECTION("Const")
  {
    const cen::thread thread{dummy};
    CHECK(thread.get());
  }
}

TEST_CASE("thread::sleep", "[sleep]")
{
  CHECK_NOTHROW(cen::thread::sleep(cen::milliseconds<cen::u32>{10}));
  CHECK_NOTHROW(cen::thread::sleep(cen::milliseconds<cen::u32>{0}));
}

TEST_CASE("thread::set_priority", "[thread]")
{
  CHECK(cen::thread::set_priority(cen::thread_priority::low));
}

TEST_CASE("thread::current_id", "[thread]")
{
  CHECK_NOTHROW(cen::thread::current_id() == SDL_ThreadID());
}

TEST_CASE("thread to_string", "[thread]")
{
  cen::thread thread{dummy, "myThread"};
  std::cout << "to_string: " << cen::to_string(thread) << '\n';
}

TEST_CASE("thread stream operator", "[thread]")
{
  cen::thread thread{dummy, "myThread"};
  std::cout << "<< operator: " << thread << '\n';
}

TEST_CASE("thread_priority values", "[thread]")
{
  SECTION("==")
  {
    CHECK(cen::thread_priority::low == SDL_THREAD_PRIORITY_LOW);
    CHECK(cen::thread_priority::normal == SDL_THREAD_PRIORITY_NORMAL);
    CHECK(cen::thread_priority::high == SDL_THREAD_PRIORITY_HIGH);
    CHECK(cen::thread_priority::critical == SDL_THREAD_PRIORITY_TIME_CRITICAL);

    CHECK(SDL_THREAD_PRIORITY_LOW == cen::thread_priority::low);
    CHECK(SDL_THREAD_PRIORITY_NORMAL == cen::thread_priority::normal);
    CHECK(SDL_THREAD_PRIORITY_HIGH == cen::thread_priority::high);
    CHECK(SDL_THREAD_PRIORITY_TIME_CRITICAL == cen::thread_priority::critical);
  }

  SECTION("!=")
  {
    CHECK(cen::thread_priority::high != SDL_THREAD_PRIORITY_TIME_CRITICAL);
    CHECK(SDL_THREAD_PRIORITY_LOW != cen::thread_priority::normal);
  }
}