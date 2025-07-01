// Copyright (C) 2025 Albin Johansson

#include "centurion/gpu/render_pass.hpp"

namespace cen {

GpuRenderPass::GpuRenderPass(SDL_GPURenderPass* const render_pass,
                             const HandleMode mode) noexcept :
  mHandle {render_pass, mode}
{}

auto GpuRenderPass::get() noexcept -> SDL_GPURenderPass*
{
  return mHandle.get();
}

auto GpuRenderPass::get() const noexcept -> const SDL_GPURenderPass*
{
  return mHandle.get();
}

auto GpuRenderPass::const_get() const noexcept -> SDL_GPURenderPass*
{
  return mHandle.get();
}

auto GpuRenderPass::mode() const noexcept -> HandleMode
{
  return mHandle.mode();
}

}  // namespace cen
