// Copyright (C) 2025 Albin Johansson

#include "centurion/gpu/compute_pass.hpp"

namespace cen {

GpuComputePass::GpuComputePass(SDL_GPUComputePass* const compute_pass,
                               const HandleMode mode) noexcept :
  mHandle {compute_pass, mode}
{}

auto GpuComputePass::get() noexcept -> SDL_GPUComputePass*
{
  return mHandle.get();
}

auto GpuComputePass::get() const noexcept -> const SDL_GPUComputePass*
{
  return mHandle.get();
}

auto GpuComputePass::const_get() const noexcept -> SDL_GPUComputePass*
{
  return mHandle.get();
}

auto GpuComputePass::mode() const noexcept -> HandleMode
{
  return mHandle.mode();
}

}  // namespace cen
