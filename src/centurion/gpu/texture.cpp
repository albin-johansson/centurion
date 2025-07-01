// Copyright (C) 2025 Albin Johansson

#include "centurion/gpu/texture.hpp"

namespace cen {

GpuTexture::GpuTexture(SDL_GPUDevice* const device,
                       SDL_GPUTexture* const texture,
                       const HandleMode mode) noexcept :
  mHandle {device, texture, mode}
{}

void GpuTexture::set_name(const zstring name) noexcept
{
  SDL_SetGPUTextureName(mHandle.device(), mHandle.get(), name);
}

auto GpuTexture::device() const noexcept -> SDL_GPUDevice*
{
  return mHandle.device();
}

auto GpuTexture::get() noexcept -> SDL_GPUTexture*
{
  return mHandle.get();
}

auto GpuTexture::get() const noexcept -> const SDL_GPUTexture*
{
  return mHandle.get();
}

auto GpuTexture::const_get() const noexcept -> SDL_GPUTexture*
{
  return mHandle.get();
}

auto GpuTexture::mode() const noexcept -> HandleMode
{
  return mHandle.mode();
}

}  // namespace cen
