// Copyright (C) 2025 Albin Johansson

#pragma once

#include <span>

#include <SDL3/SDL_gpu.h>
#include <centurion/gpu/buffer.hpp>
#include <centurion/gpu/sampler.hpp>
#include <centurion/util/common.hpp>
#include <centurion/util/handle.hpp>

namespace cen {

/// \addtogroup GPU
/// \{

/// Represents a GPU device.
///
/// \see SDL_GPUDevice
class GpuDevice final
{
 public:
  /// Creates a GPU device.
  ///
  /// \param[inout] device The target device.
  /// \param[in]    mode   The handle mode to use.
  explicit GpuDevice(SDL_GPUDevice* device = nullptr,
                     HandleMode mode = HandleMode::kOwning) noexcept;

  /// \see SDL_WaitForGPUIdle
  [[nodiscard]]
  auto wait_for_idle() noexcept -> bool;

  /// \see SDL_CreateGPUBuffer
  [[nodiscard]]
  auto create_buffer(const SDL_GPUBufferCreateInfo& create_info) noexcept -> GpuBuffer;

  /// \see SDL_CreateGPUTransferBuffer
  [[nodiscard]]
  auto create_transfer_buffer(const SDL_GPUTransferBufferCreateInfo& create_info) noexcept
      -> GpuTransferBuffer;

  /// \see SDL_CreateGPUSampler
  [[nodiscard]]
  auto create_sampler(const SDL_GPUSamplerCreateInfo& create_info) noexcept -> GpuSampler;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUDevice pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPUDevice*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUDevice pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPUDevice*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPUDevice pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPUDevice*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  GpuHandle<SDL_GPUDevice*> mHandle;
};

/// \}

}  // namespace cen
