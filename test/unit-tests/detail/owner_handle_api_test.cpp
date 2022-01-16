#include "detail/owner_handle_api.hpp"

#include <gtest/gtest.h>

#include "memory.hpp"

inline int delete_count = 0;

namespace cen {

template <>
struct Deleter<int> final {
  void operator()(const int* ptr) noexcept
  {
    ++delete_count;
    delete ptr;
  }
};

}  // namespace cen

using Owner = cen::detail::pointer<cen::detail::owner_tag, int>;
using Handle = cen::detail::pointer<cen::detail::handle_tag, int>;

static_assert(std::is_nothrow_default_constructible_v<Owner>);
static_assert(std::is_nothrow_default_constructible_v<Handle>);

static_assert(!std::is_copy_constructible_v<Owner>);
static_assert(std::is_nothrow_copy_constructible_v<Handle>);

static_assert(std::is_nothrow_move_constructible_v<Owner>);
static_assert(std::is_nothrow_move_constructible_v<Handle>);

static_assert(noexcept(Owner{nullptr}));
static_assert(noexcept(Handle{nullptr}));

TEST(OwnerHandleAPI, Constructor)
{
  ASSERT_NO_THROW(Owner{nullptr});
  ASSERT_NO_THROW(Handle{nullptr});

  {
    int i = 42;

    Handle handle{&i};
    const auto& cHandle = handle;

    ASSERT_TRUE(handle);
    ASSERT_TRUE(cHandle);
    ASSERT_TRUE(handle.get());
    ASSERT_TRUE(cHandle.get());
    ASSERT_TRUE(handle.operator->());
    ASSERT_TRUE(cHandle.operator->());
    ASSERT_NO_FATAL_FAILURE(handle.operator*());
    ASSERT_NO_FATAL_FAILURE(cHandle.operator*());
  }

  {
    Handle handle{nullptr};
    const auto& cHandle = handle;

    ASSERT_FALSE(handle);
    ASSERT_FALSE(cHandle);
    ASSERT_FALSE(handle.get());
    ASSERT_FALSE(cHandle.get());
    ASSERT_FALSE(handle.operator->());
    ASSERT_FALSE(cHandle.operator->());
  }
}

TEST(OwnerHandleAPI, DeleteCorrectness)
{
  Owner{new int{7}};

  int i = 7;
  Handle{&i};

  ASSERT_EQ(1, delete_count);
}

TEST(OwnerHandleAPI, Get)
{
  int i = 7;
  Handle handle{&i};
  ASSERT_EQ(&i, handle.get());
}
