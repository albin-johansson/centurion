// Copyright (C) 2025 Albin Johansson

#pragma once

#include <SDL3/SDL_gpu.h>
#include <centurion/util/handle.hpp>

namespace cen {

/// \addtogroup GPU
/// \{

/// Represents a GPU graphics pipeline.
///
/// \see SDL_GPUGraphicsPipeline
class GpuGraphicsPipeline final
{
 public:
  /// Creates a null owning GPU graphics pipeline.
  GpuGraphicsPipeline() noexcept = default;

  /// Creates a GPU graphics pipeline.
  ///
  /// \param[inout] device   The associated device.
  /// \param[inout] pipeline The target graphics pipeline.
  /// \param[in]    mode     The handle mode to use.
  explicit GpuGraphicsPipeline(SDL_GPUDevice* device,
                               SDL_GPUGraphicsPipeline* pipeline,
                               HandleMode mode = HandleMode::kOwning) noexcept;

  /// Returns the associated device handle.
  ///
  /// \return
  /// A possibly null SDL_GPUDevice pointer.
  [[nodiscard]]
  auto device() const noexcept -> SDL_GPUDevice*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUGraphicsPipeline pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPUGraphicsPipeline*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUGraphicsPipeline pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPUGraphicsPipeline*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPUGraphicsPipeline pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPUGraphicsPipeline*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  GpuHandle<SDL_GPUGraphicsPipeline*> mHandle {};
};

/// Represents a GPU compute pipeline.
///
/// \see SDL_GPUComputePipeline
class GpuComputePipeline final
{
 public:
  /// Creates a null owning GPU compute pipeline.
  GpuComputePipeline() noexcept = default;

  /// Creates a GPU graphics pipeline.
  ///
  /// \param[inout] device   The associated device.
  /// \param[inout] pipeline The target compute pipeline.
  /// \param[in]    mode     The handle mode to use.
  explicit GpuComputePipeline(SDL_GPUDevice* device,
                              SDL_GPUComputePipeline* pipeline,
                              HandleMode mode = HandleMode::kOwning) noexcept;

  /// Returns the associated device handle.
  ///
  /// \return
  /// A possibly null SDL_GPUDevice pointer.
  [[nodiscard]]
  auto device() const noexcept -> SDL_GPUDevice*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUComputePipeline pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPUComputePipeline*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUComputePipeline pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPUComputePipeline*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPUComputePipeline pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPUComputePipeline*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  GpuHandle<SDL_GPUComputePipeline*> mHandle {};
};

/// \}

}  // namespace cen
