// Copyright (C) 2025 Albin Johansson

#include "centurion/gpu/fence.hpp"

namespace cen {

GpuFence::GpuFence(SDL_GPUDevice* const device,
                   SDL_GPUFence* const fence,
                   const HandleMode mode) noexcept :
  mHandle {device, fence, mode}
{}

auto GpuFence::device() const noexcept -> SDL_GPUDevice*
{
  return mHandle.device();
}

auto GpuFence::get() noexcept -> SDL_GPUFence*
{
  return mHandle.get();
}

auto GpuFence::get() const noexcept -> const SDL_GPUFence*
{
  return mHandle.get();
}

auto GpuFence::const_get() const noexcept -> SDL_GPUFence*
{
  return mHandle.get();
}

auto GpuFence::mode() const noexcept -> HandleMode
{
  return mHandle.mode();
}

}  // namespace cen
