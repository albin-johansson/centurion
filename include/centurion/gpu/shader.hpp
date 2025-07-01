// Copyright (C) 2025 Albin Johansson

#pragma once

#include <SDL3/SDL_gpu.h>
#include <centurion/util/handle.hpp>

namespace cen {

/// \addtogroup GPU
/// \{

/// Represents a GPU shader.
///
/// \see SDL_GPUShader
class GpuShader final
{
 public:
  /// Creates a null owning GPU shader.
  GpuShader() noexcept = default;

  /// Creates a GPU shader.
  ///
  /// \param[inout] device The associated device.
  /// \param[inout] shader The target shader.
  /// \param[in]    mode   The handle mode to use.
  explicit GpuShader(SDL_GPUDevice* device,
                     SDL_GPUShader* shader,
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
  /// A possibly null SDL_GPUShader pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPUShader*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUShader pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPUShader*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPUShader pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPUShader*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  GpuHandle<SDL_GPUShader*> mHandle {};
};

/// \}

}  // namespace cen
