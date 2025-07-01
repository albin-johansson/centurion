// Copyright (C) 2025 Albin Johansson

#include "centurion/gpu/device.hpp"

#include <cassert>

namespace cen {

GpuDevice::GpuDevice(SDL_GPUDevice* const device, const HandleMode mode) noexcept :
  mHandle {device, device, mode}
{}

auto GpuDevice::wait_for_idle() noexcept -> bool
{
  return SDL_WaitForGPUIdle(mHandle.get());
}

auto GpuDevice::create_buffer(const SDL_GPUBufferCreateInfo& create_info) noexcept
    -> GpuBuffer
{
  assert(mHandle.get());
  auto* device = mHandle.get();
  return GpuBuffer {device, SDL_CreateGPUBuffer(device, &create_info)};
}

auto GpuDevice::create_transfer_buffer(
    const SDL_GPUTransferBufferCreateInfo& create_info) noexcept -> GpuTransferBuffer
{
  assert(mHandle.get());
  auto* device = mHandle.get();
  return GpuTransferBuffer {device, SDL_CreateGPUTransferBuffer(device, &create_info)};
}

auto GpuDevice::create_sampler(const SDL_GPUSamplerCreateInfo& create_info) noexcept
    -> GpuSampler
{
  assert(mHandle.get());
  auto* device = mHandle.get();
  return GpuSampler {device, SDL_CreateGPUSampler(device, &create_info)};
}

auto GpuDevice::get() noexcept -> SDL_GPUDevice*
{
  return mHandle.get();
}

auto GpuDevice::get() const noexcept -> const SDL_GPUDevice*
{
  return mHandle.get();
}

auto GpuDevice::const_get() const noexcept -> SDL_GPUDevice*
{
  return mHandle.get();
}

auto GpuDevice::mode() const noexcept -> HandleMode
{
  return mHandle.mode();
}

}  // namespace cen
