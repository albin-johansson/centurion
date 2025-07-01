// Copyright (C) 2025 Albin Johansson

#pragma once

#include <SDL3/SDL_gpu.h>
#include <centurion/util/common.hpp>
#include <centurion/util/handle.hpp>

namespace cen {

/// \addtogroup GPU
/// \{

/// Represents a GPU buffer.
///
/// \see SDL_GPUBuffer
class GpuBuffer final
{
 public:
  /// Creates a null owning GPU buffer.
  GpuBuffer() noexcept;

  /// Creates a GPU buffer.
  ///
  /// \param[inout] device The associated device.
  /// \param[inout] buffer The target buffer.
  /// \param[in]    mode   The handle mode to use.
  explicit GpuBuffer(SDL_GPUDevice* device,
                     SDL_GPUBuffer* buffer,
                     HandleMode mode = HandleMode::kOwning) noexcept;

  /// \see SDL_SetGPUBufferName
  void set_name(zstring name) noexcept;

  /// Returns the associated device handle.
  ///
  /// \return
  /// A possibly null device handle.
  [[nodiscard]]
  auto device() const noexcept -> SDL_GPUDevice*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUBuffer pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPUBuffer*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUBuffer pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPUBuffer*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPUBuffer pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPUBuffer*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  GpuHandle<SDL_GPUBuffer*> mHandle {};
};

/// \}

}  // namespace cen
