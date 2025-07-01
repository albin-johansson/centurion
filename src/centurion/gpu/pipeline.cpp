// Copyright (C) 2025 Albin Johansson

#include "centurion/gpu/pipeline.hpp"

namespace cen {

GpuGraphicsPipeline::GpuGraphicsPipeline(SDL_GPUDevice* const device,
                                         SDL_GPUGraphicsPipeline* const pipeline,
                                         const HandleMode mode) noexcept :
  mHandle {device, pipeline, mode}
{}

auto GpuGraphicsPipeline::device() const noexcept -> SDL_GPUDevice*
{
  return mHandle.device();
}

auto GpuGraphicsPipeline::get() noexcept -> SDL_GPUGraphicsPipeline*
{
  return mHandle.get();
}

auto GpuGraphicsPipeline::get() const noexcept -> const SDL_GPUGraphicsPipeline*
{
  return mHandle.get();
}

auto GpuGraphicsPipeline::const_get() const noexcept -> SDL_GPUGraphicsPipeline*
{
  return mHandle.get();
}

auto GpuGraphicsPipeline::mode() const noexcept -> HandleMode
{
  return mHandle.mode();
}

GpuComputePipeline::GpuComputePipeline(SDL_GPUDevice* const device,
                                       SDL_GPUComputePipeline* const pipeline,
                                       const HandleMode mode) noexcept :
  mHandle {device, pipeline, mode}
{}

auto GpuComputePipeline::device() const noexcept -> SDL_GPUDevice*
{
  return mHandle.device();
}

auto GpuComputePipeline::get() noexcept -> SDL_GPUComputePipeline*
{
  return mHandle.get();
}

auto GpuComputePipeline::get() const noexcept -> const SDL_GPUComputePipeline*
{
  return mHandle.get();
}

auto GpuComputePipeline::const_get() const noexcept -> SDL_GPUComputePipeline*
{
  return mHandle.get();
}

auto GpuComputePipeline::mode() const noexcept -> HandleMode
{
  return mHandle.mode();
}

}  // namespace cen
