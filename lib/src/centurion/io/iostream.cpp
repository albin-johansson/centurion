// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/io/iostream.hpp"

#include "centurion/core/error.hpp"
#include "centurion/detail/enum.hpp"

namespace cen::inline v8_0_0 {

auto iostream_base::seek(const seek_mode mode,
                         const difference_type offset) noexcept
    -> std::optional<difference_type>
{
  const auto final_offset =
      SDL_SeekIO(get(), offset, detail::to_underlying(mode));

  if (final_offset < 0) {
    emit_sdl_error();
    return std::nullopt;
  }

  return final_offset;
}

auto iostream_base::tell() const noexcept -> std::optional<difference_type>
{
  const auto offset = SDL_TellIO(unsafe_get());

  if (offset == -1) {
    emit_sdl_error();
    return std::nullopt;
  }

  return offset;
}

auto iostream_base::read(void* const data,
                         const size_type size) noexcept -> size_type
{
  return SDL_ReadIO(get(), data, size);
}

auto iostream_base::read_u8() noexcept -> std::optional<std::uint8_t>
{
  std::uint8_t value {};
  const auto succeeded = SDL_ReadU8(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_u16_le() noexcept -> std::optional<std::uint16_t>
{
  std::uint16_t value {};
  const auto succeeded = SDL_ReadU16LE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_u16_be() noexcept -> std::optional<std::uint16_t>
{
  std::uint16_t value {};
  const auto succeeded = SDL_ReadU16BE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_s16_le() noexcept -> std::optional<std::int16_t>
{
  std::int16_t value {};
  const auto succeeded = SDL_ReadS16LE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_s16_be() noexcept -> std::optional<std::int16_t>
{
  std::int16_t value {};
  const auto succeeded = SDL_ReadS16BE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_u32_le() noexcept -> std::optional<std::uint32_t>
{
  std::uint32_t value {};
  const auto succeeded = SDL_ReadU32LE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_u32_be() noexcept -> std::optional<std::uint32_t>
{
  std::uint32_t value {};
  const auto succeeded = SDL_ReadU32BE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_s32_le() noexcept -> std::optional<std::int32_t>
{
  std::int32_t value {};
  const auto succeeded = SDL_ReadS32LE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_s32_be() noexcept -> std::optional<std::int32_t>
{
  std::int32_t value {};
  const auto succeeded = SDL_ReadS32BE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_u64_le() noexcept -> std::optional<std::uint64_t>
{
  std::uint64_t value {};
  const auto succeeded = SDL_ReadU64LE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_u64_be() noexcept -> std::optional<std::uint64_t>
{
  std::uint64_t value {};
  const auto succeeded = SDL_ReadU64BE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_s64_le() noexcept -> std::optional<std::int64_t>
{
  std::int64_t value {};
  const auto succeeded = SDL_ReadS64LE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::read_s64_be() noexcept -> std::optional<std::int64_t>
{
  std::int64_t value {};
  const auto succeeded = SDL_ReadS64BE(get(), &value);

  if (!succeeded) {
    emit_sdl_error();
    return std::nullopt;
  }

  return value;
}

auto iostream_base::write(const void* const data,
                          const size_type size) noexcept -> size_type
{
  const auto written_bytes = SDL_WriteIO(get(), data, size);

  if (written_bytes < size) {
    emit_sdl_error();
  }

  return written_bytes;
}

auto iostream_base::write_u8(const std::uint8_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteU8(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_u16_le(const std::uint16_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteU16LE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_u16_be(const std::uint16_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteU16BE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_s16_le(const std::int16_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteS16LE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_s16_be(const std::int16_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteS16BE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_u32_le(const std::uint32_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteU32LE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_u32_be(const std::uint32_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteU32BE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_s32_le(const std::int32_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteS32LE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_s32_be(const std::int32_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteS32BE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_u64_le(const std::uint64_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteU64LE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_u64_be(const std::uint64_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteU64BE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_s64_le(const std::int64_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteS64LE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::write_s64_be(const std::int64_t value) noexcept -> result
{
  const auto succeeded = SDL_WriteS64BE(get(), value);

  if (!succeeded) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto iostream_base::size() const noexcept -> std::optional<difference_type>
{
  const auto io_size = SDL_GetIOSize(unsafe_get());

  if (io_size < 0) {
    emit_sdl_error();
    return std::nullopt;
  }

  return io_size;
}

auto iostream_base::status() const noexcept -> SDL_IOStatus
{
  return SDL_GetIOStatus(unsafe_get());
}

auto iostream_base::get_properties() const noexcept
    -> std::optional<SDL_PropertiesID>
{
  const auto id = SDL_GetIOProperties(unsafe_get());

  if (id == 0) {
    emit_sdl_error();
    return std::nullopt;
  }

  return id;
}

auto iostream_base::get() noexcept -> SDL_IOStream*
{
  return unsafe_get();
}

auto iostream_base::get() const noexcept -> const SDL_IOStream*
{
  return unsafe_get();
}

void iostream::iostream_deleter::operator()(SDL_IOStream* stream) const noexcept
{
  const auto ec = SDL_CloseIO(stream);
  if (ec != 0) {
    emit_sdl_error();
  }
}

iostream::iostream(SDL_IOStream* ptr) noexcept
  : m_stream {ptr}
{}

auto iostream::from_file(const char* file,
                         const char* mode) noexcept -> std::optional<iostream>
{
  auto* const ptr = SDL_IOFromFile(file, mode);

  if (!ptr) {
    emit_sdl_error();
    return std::nullopt;
  }

  return iostream {ptr};
}

auto iostream::from_memory(void* data, const size_type size) noexcept
    -> std::optional<iostream>
{
  auto* const ptr = SDL_IOFromMem(data, size);

  if (!ptr) {
    emit_sdl_error();
    return std::nullopt;
  }

  return iostream {ptr};
}

auto iostream::from_const_memory(const void* data,
                                 const size_type size) noexcept
    -> std::optional<iostream>
{
  auto* const ptr = SDL_IOFromConstMem(data, size);

  if (!ptr) {
    emit_sdl_error();
    return std::nullopt;
  }

  return iostream {ptr};
}

auto iostream::from_dynamic_memory() noexcept -> std::optional<iostream>
{
  auto* const ptr = SDL_IOFromDynamicMem();

  if (!ptr) {
    emit_sdl_error();
    return std::nullopt;
  }

  return iostream {ptr};
}

auto iostream::unsafe_get() const noexcept -> SDL_IOStream*
{
  return m_stream.get();
}

iostream_ref::iostream_ref(SDL_IOStream* ptr) noexcept
  : m_stream {ptr}
{}

iostream_ref::iostream_ref(iostream& other) noexcept
  : iostream_ref {other.get()}
{}

auto iostream_ref::is_null() const noexcept -> bool
{
  return m_stream == nullptr;
}

iostream_ref::operator bool() const noexcept
{
  return !is_null();
}

auto iostream_ref::unsafe_get() const noexcept -> SDL_IOStream*
{
  return m_stream;
}

auto load_file(const char* file) noexcept -> std::optional<file_data>
{
  file_data result {};
  result.data.reset(SDL_LoadFile(file, &result.size));

  if (!result.data) {
    emit_sdl_error();
    return std::nullopt;
  }

  return result;
}

auto load_file(iostream_ref stream) noexcept -> std::optional<file_data>
{
  file_data result {};
  result.data.reset(SDL_LoadFile_IO(stream.get(), &result.size, SDL_FALSE));

  if (!result.data) {
    emit_sdl_error();
    return std::nullopt;
  }

  return result;
}

}  // namespace cen::inline v8_0_0
