#include "thread.hpp"

#include <catch.hpp>
#include <iostream>
#include <type_traits>

#include "centurion_as_ctn.hpp"

namespace {

auto dummy = [](void*) noexcept -> int { return 0; };

}

static_assert(std::is_same_v<ctn::thread::id, SDL_threadID>);
static_assert(std::is_same_v<ctn::thread::task_type, SDL_ThreadFunction>);

TEST_CASE("thread::detach", "[thread]")
{
  ctn::thread thread{dummy};

  thread.detach();

  CHECK(!thread.joinable());
  CHECK(!thread.was_joined());
  CHECK(thread.was_detached());

  CHECK_NOTHROW(thread.detach());
}

TEST_CASE("thread::join", "[thread]")
{
  ctn::thread thread{dummy};

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
    ctn::thread thread{dummy};

    CHECK(thread.joinable());

    thread.join();

    CHECK(!thread.joinable());
  }

  SECTION("Shouldn't be joinable after detach")
  {
    ctn::thread thread{dummy};

    CHECK(thread.joinable());

    thread.detach();

    CHECK(!thread.joinable());
  }
}

TEST_CASE("thread::was_joined", "[thread]")
{
  ctn::thread thread{dummy};

  CHECK(!thread.was_joined());

  thread.join();

  CHECK(thread.was_joined());
}

TEST_CASE("thread::was_detached", "[thread]")
{
  ctn::thread thread{dummy};

  CHECK(!thread.was_detached());

  thread.detach();

  CHECK(thread.was_detached());
}

TEST_CASE("thread::get_id", "[thread]")
{
  ctn::thread thread{dummy};

  CHECK(thread.get_id() == SDL_GetThreadID(thread.get()));
}

TEST_CASE("thread::name", "[thread]")
{
  SECTION("Custom name")
  {
    const auto name = "foobar";
    const ctn::thread thread{dummy, name};
    CHECK(thread.name() == name);
  }

  SECTION("Default name")
  {
    const ctn::thread thread{dummy};
    CHECK(thread.name() == "thread");
  }
}

TEST_CASE("thread::get", "[thread]")
{
  SECTION("Non-const")
  {
    ctn::thread thread{dummy};
    CHECK(thread.get());
  }

  SECTION("Const")
  {
    const ctn::thread thread{dummy};
    CHECK(thread.get());
  }
}

TEST_CASE("thread::sleep", "[sleep]")
{
  CHECK_NOTHROW(ctn::thread::sleep(ctn::milliseconds<ctn::u32>{10}));
  CHECK_NOTHROW(ctn::thread::sleep(ctn::milliseconds<ctn::u32>{0}));
}

TEST_CASE("thread::set_priority", "[thread]")
{
  CHECK(ctn::thread::set_priority(ctn::thread_priority::low));
}

TEST_CASE("thread::current_id", "[thread]")
{
  CHECK_NOTHROW(ctn::thread::current_id() == SDL_ThreadID());
}

TEST_CASE("thread to_string", "[thread]")
{
  ctn::thread thread{dummy, "myThread"};
  std::cout << "to_string: " << ctn::to_string(thread) << '\n';
}

TEST_CASE("thread stream operator", "[thread]")
{
  ctn::thread thread{dummy, "myThread"};
  std::cout << "<< operator: " << thread << '\n';
}

TEST_CASE("thread_priority values", "[thread]")
{
  SECTION("==")
  {
    CHECK(ctn::thread_priority::low == SDL_THREAD_PRIORITY_LOW);
    CHECK(ctn::thread_priority::normal == SDL_THREAD_PRIORITY_NORMAL);
    CHECK(ctn::thread_priority::high == SDL_THREAD_PRIORITY_HIGH);
    CHECK(ctn::thread_priority::critical == SDL_THREAD_PRIORITY_TIME_CRITICAL);

    CHECK(SDL_THREAD_PRIORITY_LOW == ctn::thread_priority::low);
    CHECK(SDL_THREAD_PRIORITY_NORMAL == ctn::thread_priority::normal);
    CHECK(SDL_THREAD_PRIORITY_HIGH == ctn::thread_priority::high);
    CHECK(SDL_THREAD_PRIORITY_TIME_CRITICAL == ctn::thread_priority::critical);
  }

  SECTION("!=")
  {
    CHECK(ctn::thread_priority::high != SDL_THREAD_PRIORITY_TIME_CRITICAL);
    CHECK(SDL_THREAD_PRIORITY_LOW != ctn::thread_priority::normal);
  }
}