// Copyright (C) 2025 Albin Johansson

#pragma once

#include <SDL3/SDL_gpu.h>
#include <centurion/util/common.hpp>
#include <centurion/util/handle.hpp>

namespace cen {

/// \addtogroup GPU
/// \{

/// Represents a GPU texture.
///
/// \see SDL_GPUTexture
class GpuTexture final
{
 public:
  /// Creates a null owning GPU texture.
  GpuTexture() noexcept = default;

  /// Creates a GPU texture.
  ///
  /// \param[inout] device  The associated device.
  /// \param[inout] texture The target texture.
  /// \param[in]    mode    The handle mode to use.
  explicit GpuTexture(SDL_GPUDevice* device,
                      SDL_GPUTexture* texture,
                      HandleMode mode = HandleMode::kOwning) noexcept;

  /// \see SDL_SetGPUTextureName
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
  /// A possibly null SDL_GPUTexture pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPUTexture*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPUTexture pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPUTexture*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPUTexture pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPUTexture*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  GpuHandle<SDL_GPUTexture*> mHandle {};
};

/// \}

}  // namespace cen
