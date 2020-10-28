#include "texture.hpp"

#include <type_traits>

namespace cen {

static_assert(std::is_final_v<texture>);
static_assert(std::is_nothrow_move_constructible_v<texture>);
static_assert(std::is_nothrow_move_assignable_v<texture>);
static_assert(!std::is_nothrow_copy_constructible_v<texture>);
static_assert(!std::is_nothrow_copy_assignable_v<texture>);

}  // namespace cen
