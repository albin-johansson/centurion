// Copyright (C) 2025 Albin Johansson

module;

#include <centurion/gpu/buffer.hpp>
#include <centurion/util/common.hpp>
#include <centurion/util/handle.hpp>

export module centurion;

export namespace cen {

// centurion/gpu/buffer.hpp
using cen::GpuBuffer;

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

}  // namespace cen
