#include "error.h"
#include <type_traits>
#include <SDL.h>

namespace centurion {

static_assert(std::is_final_v<Error>);
static_assert(std::is_nothrow_destructible_v<Error>);
static_assert(!std::is_constructible_v<Error>);
static_assert(!std::is_copy_constructible_v<Error>);
static_assert(!std::is_move_constructible_v<Error>);
static_assert(!std::is_copy_assignable_v<Error>);
static_assert(!std::is_move_assignable_v<Error>);

const char* Error::descriptionf() noexcept {
  const auto* err = SDL_GetError();
  return err ? err : "";
}

std::string Error::description() noexcept {
  return {descriptionf()};
}

std::string Error::msg() noexcept {
  return "Error: " + description();
}

}
