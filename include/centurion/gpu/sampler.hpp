// Copyright (C) 2025 Albin Johansson

#pragma once

#include <SDL3/SDL_gpu.h>
#include <centurion/util/handle.hpp>

namespace cen {

/// \addtogroup GPU
/// \{

/// Represents a GPU sampler.
///
/// \see SDL_GPUSampler
class GpuSampler final
{
 public:
  /// Creates a null owning GPU sampler.
  GpuSampler() noexcept;

  /// Creates a GPU sampler.
  ///
  /// \param[inout] device  The associated device.
  /// \param[inout] sampler The target sampler.
  /// \param[in]    mode    The handle mode to use.
  GpuSampler(SDL_GPUDevice* device,
             SDL_GPUSampler* sampler,
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
  /// A possibly null SDL_GPUSampler pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPUSampler*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUSampler pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPUSampler*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPUSampler pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPUSampler*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  GpuHandle<SDL_GPUSampler*> mHandle;
};

/// \}

}  // namespace cen
