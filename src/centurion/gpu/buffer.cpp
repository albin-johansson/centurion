// Copyright (C) 2025 Albin Johansson

#include "centurion/gpu/buffer.hpp"

namespace cen {

GpuBuffer::GpuBuffer(SDL_GPUDevice* const device,
                     SDL_GPUBuffer* const buffer,
                     const HandleMode mode) noexcept :
  mHandle {device, buffer, mode}
{}

GpuBuffer::GpuBuffer() noexcept :
  GpuBuffer {nullptr, nullptr, HandleMode::kOwning}
{}

void GpuBuffer::set_name(const zstring name) noexcept
{
  SDL_SetGPUBufferName(mHandle.device(), mHandle.get(), name);
}

auto GpuBuffer::device() const noexcept -> SDL_GPUDevice*
{
  return mHandle.device();
}

auto GpuBuffer::get() noexcept -> SDL_GPUBuffer*
{
  return mHandle.get();
}

auto GpuBuffer::get() const noexcept -> const SDL_GPUBuffer*
{
  return mHandle.get();
}

auto GpuBuffer::const_get() const noexcept -> SDL_GPUBuffer*
{
  return mHandle.get();
}

auto GpuBuffer::mode() const noexcept -> HandleMode
{
  return mHandle.mode();
}

}  // namespace cen
