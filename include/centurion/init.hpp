// Copyright (C) 2025 Albin Johansson

#pragma once

#include <optional>
#include <utility>

#include <SDL3/SDL_init.h>

#include "centurion/internal/defer.hpp"

namespace cen {

/// \addtogroup Init
/// \{

/// Manages an SDL library instance.
///
/// Use `SDL::init` to load the core SDL library.
/// \code{cpp}
/// int main(int argc, char* argv[]) {
///   const auto sdl = cen::SDL::init(SDL_INIT_VIDEO);
///   if (!sdl.has_value()) {
///     return EXIT_FAILURE;
///   }
///
///   // ...
///
///   return EXIT_SUCCESS;
/// }
/// \endcode
class SDL final
{
 public:
  /// Calls `SDL_Quit`.
  ~SDL() noexcept = default;

  /// Default move constructor.
  SDL(SDL&&) noexcept = default;

  /// Deleted copy constructor.
  SDL(const SDL&) = delete;

  /// Default move assignment operator.
  auto operator=(SDL&&) noexcept -> SDL& = default;

  /// Deleted copy assignment operator.
  auto operator=(const SDL&) -> SDL& = delete;

  /// \see SDL_Init
  [[nodiscard]]
  static auto init(SDL_InitFlags flags) noexcept -> std::optional<SDL>;

 private:
  internal::DeferVoidFn mQuit;

  SDL() noexcept;
};

/// \}

}  // namespace cen
