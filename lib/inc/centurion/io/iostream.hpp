// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>

#include <SDL3/SDL.h>

#include "centurion/core/error.hpp"
#include "centurion/core/memory.hpp"

namespace cen::inline v8_0_0 {

enum class seek_mode : int
{
  start = SDL_IO_SEEK_SET,
  current = SDL_IO_SEEK_CUR,
  end = SDL_IO_SEEK_END,
};

class iostream_base
{
 public:
  using size_type = std::size_t;
  using difference_type = std::int64_t;

  virtual ~iostream_base() noexcept = default;

  // SDL_SeekIO
  auto seek(seek_mode mode, difference_type offset = 0) noexcept
      -> std::optional<difference_type>;

  // SDL_TellIO
  [[nodiscard]]
  auto tell() const noexcept -> std::optional<difference_type>;

  // SDL_ReadIO
  auto read(void* data, size_type size) noexcept -> size_type;

  // SDL_ReadU8
  [[nodiscard]]
  auto read_u8() noexcept -> std::optional<std::uint8_t>;

  // SDL_ReadU16LE
  [[nodiscard]]
  auto read_u16_le() noexcept -> std::optional<std::uint16_t>;

  // SDL_ReadU16BE
  [[nodiscard]]
  auto read_u16_be() noexcept -> std::optional<std::uint16_t>;

  // SDL_Reads16LE
  [[nodiscard]]
  auto read_s16_le() noexcept -> std::optional<std::int16_t>;

  // SDL_Reads16BE
  [[nodiscard]]
  auto read_s16_be() noexcept -> std::optional<std::int16_t>;

  // SDL_ReadU32LE
  [[nodiscard]]
  auto read_u32_le() noexcept -> std::optional<std::uint32_t>;

  // SDL_ReadU32BE
  [[nodiscard]]
  auto read_u32_be() noexcept -> std::optional<std::uint32_t>;

  // SDL_Reads32LE
  [[nodiscard]]
  auto read_s32_le() noexcept -> std::optional<std::int32_t>;

  // SDL_Reads32BE
  [[nodiscard]]
  auto read_s32_be() noexcept -> std::optional<std::int32_t>;

  // SDL_ReadU64LE
  [[nodiscard]]
  auto read_u64_le() noexcept -> std::optional<std::uint64_t>;

  // SDL_ReadU64BE
  [[nodiscard]]
  auto read_u64_be() noexcept -> std::optional<std::uint64_t>;

  // SDL_Reads64LE
  [[nodiscard]]
  auto read_s64_le() noexcept -> std::optional<std::int64_t>;

  // SDL_Reads64BE
  [[nodiscard]]
  auto read_s64_be() noexcept -> std::optional<std::int64_t>;

  // SDL_WriteIO
  auto write(const void* data, size_type size) noexcept -> size_type;

  // SDL_WriteU8
  auto write_u8(std::uint8_t value) noexcept -> result;

  // SDL_WriteU16LE
  auto write_u16_le(std::uint16_t value) noexcept -> result;

  // SDL_WriteU16BE
  auto write_u16_be(std::uint16_t value) noexcept -> result;

  // SDL_WriteS16LE
  auto write_s16_le(std::int16_t value) noexcept -> result;

  // SDL_WriteS16BE
  auto write_s16_be(std::int16_t value) noexcept -> result;

  // SDL_WriteU32LE
  auto write_u32_le(std::uint32_t value) noexcept -> result;

  // SDL_WriteU32BE
  auto write_u32_be(std::uint32_t value) noexcept -> result;

  // SDL_WriteS32LE
  auto write_s32_le(std::int32_t value) noexcept -> result;

  // SDL_WriteS32BE
  auto write_s32_be(std::int32_t value) noexcept -> result;

  // SDL_WriteU64LE
  auto write_u64_le(std::uint64_t value) noexcept -> result;

  // SDL_WriteU64BE
  auto write_u64_be(std::uint64_t value) noexcept -> result;

  // SDL_WriteS64LE
  auto write_s64_le(std::int64_t value) noexcept -> result;

  // SDL_WriteS64BE
  auto write_s64_be(std::int64_t value) noexcept -> result;

  // SDL_GetIOSize
  [[nodiscard]]
  auto size() const noexcept -> std::optional<difference_type>;

  // SDL_GetIOStatus
  [[nodiscard]]
  auto status() const noexcept -> SDL_IOStatus;

  // SDL_GetIOProperties
  [[nodiscard]]
  auto get_properties() const noexcept -> std::optional<SDL_PropertiesID>;

  [[nodiscard]]
  auto get() noexcept -> SDL_IOStream*;

  [[nodiscard]]
  auto get() const noexcept -> const SDL_IOStream*;

  [[nodiscard]]
  virtual auto unsafe_get() const noexcept -> SDL_IOStream* = 0;
};

class iostream final : public iostream_base
{
 public:
  // SDL_IOFromFile
  [[nodiscard]]
  static auto from_file(const char* file,
                        const char* mode) noexcept -> std::optional<iostream>;

  // SDL_IOFromMem
  [[nodiscard]]
  static auto from_memory(void* data,
                          size_type size) noexcept -> std::optional<iostream>;

  // SDL_IOFromConstMem
  [[nodiscard]]
  static auto from_const_memory(const void* data, size_type size) noexcept
      -> std::optional<iostream>;

  // SDL_IOFromDynamicMem
  [[nodiscard]]
  static auto from_dynamic_memory() noexcept -> std::optional<iostream>;

  [[nodiscard]]
  auto unsafe_get() const noexcept -> SDL_IOStream* override;

 private:
  struct iostream_deleter
  {
    void operator()(SDL_IOStream* stream) const noexcept;
  };

  std::unique_ptr<SDL_IOStream, iostream_deleter> m_stream;

  explicit iostream(SDL_IOStream* ptr) noexcept;
};

class iostream_ref final : public iostream_base
{
 public:
  explicit iostream_ref(SDL_IOStream* ptr = nullptr) noexcept;

  /* implicit */ iostream_ref(iostream& other) noexcept;

  [[nodiscard]]
  auto is_null() const noexcept -> bool;

  [[nodiscard]]
  explicit operator bool() const noexcept;

  [[nodiscard]]
  auto unsafe_get() const noexcept -> SDL_IOStream* override;

 private:
  SDL_IOStream* m_stream;
};

using iostream_cref = const iostream_ref&;

struct file_data final
{
  unique_sdl_ptr<void> data;
  std::size_t size;
};

// SDL_LoadFile
[[nodiscard]]
auto load_file(const char* file) noexcept -> std::optional<file_data>;

// SDL_LoadFile_IO
[[nodiscard]]
auto load_file(iostream_ref stream) noexcept -> std::optional<file_data>;

}  // namespace cen::inline v8_0_0
