#include "detail/owner_handle_api.hpp"

#include <gtest/gtest.h>

namespace {

inline int deleteCount = 0;

struct int_deleter final
{
  void operator()(const int* ptr) noexcept
  {
    ++deleteCount;
    delete ptr;
  }
};

}  // namespace

using cen::detail::pointer_manager;
using owner_t = pointer_manager<std::true_type, int, int_deleter>;
using handle_t = pointer_manager<std::false_type, int, int_deleter>;

static_assert(std::is_nothrow_default_constructible_v<handle_t>);
static_assert(std::is_nothrow_default_constructible_v<owner_t>);

static_assert(std::is_nothrow_copy_constructible_v<handle_t>);
static_assert(!std::is_copy_constructible_v<owner_t>);

static_assert(std::is_nothrow_move_constructible_v<handle_t>);
static_assert(std::is_nothrow_move_constructible_v<owner_t>);

static_assert(noexcept(owner_t{nullptr}));
static_assert(noexcept(handle_t{nullptr}));

TEST(OwnerHandleAPI, Constructor)
{
  EXPECT_NO_THROW(owner_t{nullptr});
  EXPECT_NO_THROW(handle_t{nullptr});

  {
    int i = 42;

    handle_t handle{&i};
    const auto& cHandle = handle;

    EXPECT_TRUE(handle);
    EXPECT_TRUE(cHandle);
    EXPECT_TRUE(handle.get());
    EXPECT_TRUE(cHandle.get());
    EXPECT_TRUE(handle.operator->());
    EXPECT_TRUE(cHandle.operator->());
    EXPECT_NO_FATAL_FAILURE(handle.operator*());
    EXPECT_NO_FATAL_FAILURE(cHandle.operator*());
  }

  {
    handle_t handle{nullptr};
    const auto& cHandle = handle;

    EXPECT_FALSE(handle);
    EXPECT_FALSE(cHandle);
    EXPECT_FALSE(handle.get());
    EXPECT_FALSE(cHandle.get());
    EXPECT_FALSE(handle.operator->());
    EXPECT_FALSE(cHandle.operator->());
  }
}

TEST(OwnerHandleAPI, DeleteCorrectness)
{
  owner_t{new int{7}};

  int i = 7;
  handle_t{&i};

  EXPECT_EQ(1, deleteCount);
}

TEST(OwnerHandleAPI, Get)
{
  int i = 7;
  handle_t handle{&i};
  EXPECT_EQ(&i, handle.get());
}
