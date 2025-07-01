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
  /// A possibly null SDL_GPUDevice pointer.
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

/// Represents a GPU transfer buffer.
///
/// \see SDL_GPUTransferBuffer
class GpuTransferBuffer final
{
 public:
  /// Creates a null owning GPU transfer buffer.
  GpuTransferBuffer() noexcept = default;

  /// Creates a GPU transfer buffer.
  ///
  /// \param[inout] device The associated device.
  /// \param[inout] buffer The target buffer.
  /// \param[in]    mode   The handle mode to use.
  explicit GpuTransferBuffer(SDL_GPUDevice* device,
                             SDL_GPUTransferBuffer* buffer,
                             HandleMode mode = HandleMode::kOwning) noexcept;

  /// \see SDL_MapGPUTransferBuffer
  [[nodiscard]]
  auto map(bool cycle) noexcept -> void*;

  /// \see SDL_UnmapGPUTransferBuffer
  void unmap() noexcept;

  /// Returns the associated device handle.
  ///
  /// \return
  /// A possibly null SDL_GPUDevice pointer.
  [[nodiscard]]
  auto device() const noexcept -> SDL_GPUDevice*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUTransferBuffer pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPUTransferBuffer*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUTransferBuffer pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPUTransferBuffer*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPUTransferBuffer pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPUTransferBuffer*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  GpuHandle<SDL_GPUTransferBuffer*> mHandle {};
};

/// \}

}  // namespace cen
