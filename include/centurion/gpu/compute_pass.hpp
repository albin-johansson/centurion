// Copyright (C) 2025 Albin Johansson

#pragma once

#include <SDL3/SDL_gpu.h>
#include <centurion/util/handle.hpp>

namespace cen {

/// \addtogroup GPU
/// \{

/// Represents a GPU compute pass.
///
/// \see SDL_GPUComputePass
class GpuComputePass final
{
 public:
  /// Creates a null owning GPU compute pass.
  GpuComputePass() noexcept = default;

  /// Creates a GPU compute pass.
  ///
  /// \param[inout] compute_pass The target compute pass.
  /// \param[in]    mode         The handle mode to use.
  explicit GpuComputePass(SDL_GPUComputePass* compute_pass,
                          HandleMode mode = HandleMode::kOwning) noexcept;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUComputePass pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPUComputePass*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUComputePass pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPUComputePass*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPUComputePass pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPUComputePass*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  Handle<SDL_GPUComputePass*> mHandle {};
};

/// \}

}  // namespace cen
