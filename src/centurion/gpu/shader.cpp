// Copyright (C) 2025 Albin Johansson

#include "centurion/gpu/shader.hpp"

namespace cen {

GpuShader::GpuShader(SDL_GPUDevice* const device,
                     SDL_GPUShader* const shader,
                     const HandleMode mode) noexcept :
  mHandle {device, shader, mode}
{}

auto GpuShader::device() const noexcept -> SDL_GPUDevice*
{
  return mHandle.device();
}

auto GpuShader::get() noexcept -> SDL_GPUShader*
{
  return mHandle.get();
}

auto GpuShader::get() const noexcept -> const SDL_GPUShader*
{
  return mHandle.get();
}

auto GpuShader::const_get() const noexcept -> SDL_GPUShader*
{
  return mHandle.get();
}

auto GpuShader::mode() const noexcept -> HandleMode
{
  return mHandle.mode();
}

}  // namespace cen
