// Copyright (C) 2025 Albin Johansson

#pragma once

#include <type_traits>

#include <SDL3/SDL_gpu.h>

namespace cen {

/// \addtogroup GPU
/// \{

/// The underlying type of `cen::GpuPresentMode`.
using GpuPresentModeRepr = std::underlying_type_t<SDL_GPUPresentMode>;

/// \see SDL_GPUPresentMode
enum class GpuPresentMode : GpuPresentModeRepr
{
  kVSync = SDL_GPU_PRESENTMODE_VSYNC,
  kImmediate = SDL_GPU_PRESENTMODE_IMMEDIATE,
  kMailbox = SDL_GPU_PRESENTMODE_MAILBOX,
};

/// The underlying type of `cen::GpuSwapchainComposition`.
using GpuSwapchainCompositionRepr = std::underlying_type_t<SDL_GPUSwapchainComposition>;

/// \see SDL_GPUSwapchainComposition
enum class GpuSwapchainComposition : GpuSwapchainCompositionRepr
{
  kSdr = SDL_GPU_SWAPCHAINCOMPOSITION_SDR,
  kSdrLinear = SDL_GPU_SWAPCHAINCOMPOSITION_SDR_LINEAR,
  kHdrExtendedLinear = SDL_GPU_SWAPCHAINCOMPOSITION_HDR_EXTENDED_LINEAR,
  kHdr10St2084 = SDL_GPU_SWAPCHAINCOMPOSITION_HDR10_ST2084,
};

/// \}

}  // namespace cen
