// Copyright (C) 2025 Albin Johansson

#pragma once

#include <SDL3/SDL_gpu.h>
#include <centurion/util/handle.hpp>

namespace cen {

/// \addtogroup GPU
/// \{

/// Represents a GPU fence.
///
/// \see SDL_GPUFence
class GpuFence final
{
 public:
  /// Creates a null owning GPU fence.
  GpuFence() noexcept = default;

  /// Creates a GPU fence.
  ///
  /// \param[inout] device The associated device.
  /// \param[inout] fence  The target fence.
  /// \param[in]    mode   The handle mode to use.
  GpuFence(SDL_GPUDevice* device,
           SDL_GPUFence* fence,
           HandleMode mode = HandleMode::kOwning) noexcept;

  /// Returns the associated device handle.
  ///
  /// \return
  /// A possibly null device handle.
  [[nodiscard]]
  auto device() const noexcept -> SDL_GPUDevice*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUFence pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPUFence*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUFence pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPUFence*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPUFence pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPUFence*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  GpuHandle<SDL_GPUFence*> mHandle;
};

/// \}

}  // namespace cen
