// Copyright (C) 2025 Albin Johansson

#include "centurion/gpu/sampler.hpp"

namespace cen {

GpuSampler::GpuSampler(SDL_GPUDevice* const device,
                       SDL_GPUSampler* const sampler,
                       const HandleMode mode) noexcept :
  mHandle {device, sampler, mode}
{}

auto GpuSampler::device() const noexcept -> SDL_GPUDevice*
{
  return mHandle.device();
}

auto GpuSampler::get() noexcept -> SDL_GPUSampler*
{
  return mHandle.get();
}

auto GpuSampler::get() const noexcept -> const SDL_GPUSampler*
{
  return mHandle.get();
}

auto GpuSampler::const_get() const noexcept -> SDL_GPUSampler*
{
  return mHandle.get();
}

auto GpuSampler::mode() const noexcept -> HandleMode
{
  return mHandle.mode();
}

}  // namespace cen
