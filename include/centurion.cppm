// Copyright (C) 2025 Albin Johansson

module;

#include <centurion/gpu/buffer.hpp>
#include <centurion/gpu/device.hpp>
#include <centurion/gpu/sampler.hpp>
#include <centurion/gpu/swapchain.hpp>
#include <centurion/util/common.hpp>
#include <centurion/util/handle.hpp>

export module centurion;

export namespace cen {

// NOLINTBEGIN(*-unused-using-decls)

// centurion/gpu/buffer.hpp
using cen::GpuBuffer;

// centurion/gpu/device.hpp
using cen::GpuDevice;

// centurion/gpu/sampler.hpp
using cen::GpuSampler;

// centurion/gpu/swapchain.hpp
using cen::GpuPresentMode;
using cen::GpuPresentModeRepr;
using cen::GpuSwapchainComposition;
using cen::GpuSwapchainCompositionRepr;

// centurion/util/common.hpp
using cen::i16;
using cen::i32;
using cen::i64;
using cen::i8;
using cen::u16;
using cen::u32;
using cen::u64;
using cen::u8;
using cen::zstring;

// centurion/util/handle.hpp
using cen::GpuHandle;
using cen::GpuHandleDeleter;
using cen::Handle;
using cen::HandleDeleter;
using cen::HandleMode;

// NOLINTEND(*-unused-using-decls)

}  // namespace cen
