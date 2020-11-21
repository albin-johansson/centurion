#include "thread.hpp"

#include <catch.hpp>
#include <iostream>
#include <type_traits>

namespace {

auto dummy = [](int*) {
  using namespace cen::literals;
  cen::thread::sleep(10_ms);
};

}

TEST_CASE("thread:: ctor with no user data pointer", "[thread]")
{
  cen::thread t1{[] {
  }};

  cen::thread t2{[] {
    return 0;
  }};
}

TEST_CASE("thread:: ctor with user data pointer", "[thread]")
{
  auto value = std::make_unique<std::string>("foobar");
  cen::thread thread{[](std::string* ptr) {
                       CHECK(ptr != nullptr);
                       CHECK(*ptr == "foobar");
                     },
                     value.get()};
}

TEST_CASE("thread::detach", "[thread]")
{
  int i{};
  cen::thread thread{dummy, &i};

  thread.detach();

  CHECK(!thread.joinable());
  CHECK(!thread.was_joined());
  CHECK(thread.was_detached());

  CHECK_NOTHROW(thread.detach());
}

TEST_CASE("thread::join", "[thread]")
{
  int i{};
  cen::thread thread{dummy, &i};

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
    int i{};
    cen::thread thread{dummy, &i};

    CHECK(thread.joinable());

    thread.join();

    CHECK(!thread.joinable());
  }

  SECTION("Shouldn't be joinable after detach")
  {
    int i{};
    cen::thread thread{dummy, &i};

    CHECK(thread.joinable());

    thread.detach();

    CHECK(!thread.joinable());
  }
}

TEST_CASE("thread::was_joined", "[thread]")
{
  int i{};
  cen::thread thread{dummy, &i};

  CHECK(!thread.was_joined());

  thread.join();

  CHECK(thread.was_joined());
}

TEST_CASE("thread::was_detached", "[thread]")
{
  int i{};
  cen::thread thread{dummy, &i};

  CHECK(!thread.was_detached());

  thread.detach();

  CHECK(thread.was_detached());
}

TEST_CASE("thread::get_id", "[thread]")
{
  int i{};
  cen::thread thread{dummy, &i};

  CHECK(thread.get_id() == SDL_GetThreadID(thread.get()));
}

TEST_CASE("thread::name", "[thread]")
{
  SECTION("Custom name")
  {
    //    const auto name = "foobar";
    //    const cen::thread thread{dummy, name};
    //    CHECK(thread.name() == name);
  }

  SECTION("Default name")
  {
    int i{};
    const cen::thread thread{dummy, &i};
    CHECK(thread.name() == "thread");
  }
}

TEST_CASE("thread::get", "[thread]")
{
  SECTION("Non-const")
  {
    int i{};
    cen::thread thread{dummy, &i};
    CHECK(thread.get());
  }

  SECTION("Const")
  {
    int i{};
    cen::thread thread{dummy, &i};
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

TEST_CASE("thread to_string", "[!mayfail][thread]")
{
  //  cen::thread thread{dummy, "myThread"};
  //  std::cout << "to_string: " << cen::to_string(thread) << '\n';
}

TEST_CASE("thread stream operator", "[!mayfail][thread]")
{
  //  cen::thread thread{dummy, "myThread"};
  //  std::cout << "<< operator: " << thread << '\n';
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