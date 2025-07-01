// Copyright (C) 2025 Albin Johansson

#pragma once

#include <SDL3/SDL_gpu.h>
#include <centurion/util/handle.hpp>

namespace cen {

/// \addtogroup GPU
/// \{

/// Represents a GPU render pass.
///
/// \see SDL_GPURenderPass
class GpuRenderPass final
{
 public:
  /// Creates a null owning GPU render pass.
  GpuRenderPass() noexcept = default;

  /// Creates a GPU render pass.
  ///
  /// \param[inout] render_pass The target render pass.
  /// \param[in]    mode        The handle mode to use.
  explicit GpuRenderPass(SDL_GPURenderPass* render_pass,
                         HandleMode mode = HandleMode::kOwning) noexcept;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPURenderPass pointer.
  [[nodiscard]]
  auto get() noexcept -> SDL_GPURenderPass*;

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null SDL_GPURenderPass pointer.
  [[nodiscard]]
  auto get() const noexcept -> const SDL_GPURenderPass*;

  /// Returns the associated handle.
  ///
  /// \note
  /// Use of this function is discouraged, since it can be used to bypass
  /// const-correctness.
  ///
  /// \return
  /// A possibly null SDL_GPURenderPass pointer.
  [[nodiscard]]
  auto const_get() const noexcept -> SDL_GPURenderPass*;

  //// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode;

 private:
  Handle<SDL_GPURenderPass*> mHandle {};
};

/// \}

}  // namespace cen
