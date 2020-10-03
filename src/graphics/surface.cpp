#include "surface.hpp"

#include <type_traits>

namespace cen {

static_assert(std::is_copy_constructible_v<surface>);
static_assert(std::is_copy_assignable_v<surface>);

static_assert(std::is_nothrow_move_constructible_v<surface>);
static_assert(std::is_nothrow_move_assignable_v<surface>);

static_assert(std::is_copy_constructible_v<surface_handle>);
static_assert(std::is_copy_assignable_v<surface_handle>);

static_assert(std::is_nothrow_move_constructible_v<surface_handle>);
static_assert(std::is_nothrow_move_assignable_v<surface_handle>);

}  // namespace cen
