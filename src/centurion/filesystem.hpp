/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_FILESYSTEM_HPP_
#define CENTURION_FILESYSTEM_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#include <cassert>      // assert
#include <cstddef>      // size_t
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "common.hpp"
#include "memory.hpp"

namespace cen {

enum class file_type : unsigned
{
  unknown = SDL_RWOPS_UNKNOWN,
  win = SDL_RWOPS_WINFILE,
  std = SDL_RWOPS_STDFILE,
  jni = SDL_RWOPS_JNIFILE,
  memory = SDL_RWOPS_MEMORY,
  memory_ro = SDL_RWOPS_MEMORY_RO
};

[[nodiscard]] constexpr auto to_string(const file_type type) -> std::string_view
{
  switch (type) {
    case file_type::unknown:
      return "unknown";

    case file_type::win:
      return "win";

    case file_type::std:
      return "std";

    case file_type::jni:
      return "jni";

    case file_type::memory:
      return "memory";

    case file_type::memory_ro:
      return "memory_ro";

    default:
      throw exception{"Did not recognize file type!"};
  }
}

inline auto operator<<(std::ostream& stream, const file_type type) -> std::ostream&
{
  return stream << to_string(type);
}

enum class file_mode
{
  r,   ///< Read existing ("r").
  rb,  ///< Read existing binary ("rb").

  w,   ///< Write ("w").
  wb,  ///< Write binary ("wb").

  a,   ///< Append/create ("a").
  ab,  ///< Append/create binary ("ab").

  rx,   ///< Read/write existing ("r+").
  rbx,  ///< Read/write existing binary ("rb+").

  wx,   ///< Read/write replace ("w+").
  wbx,  ///< Read/write replace binary ("wb+").

  ax,   ///< Read/append ("a+").
  abx,  ///< Read/append binary ("ab+").
};

[[nodiscard]] constexpr auto to_string(const file_mode mode) -> std::string_view
{
  switch (mode) {
    case file_mode::r:
      return "r";

    case file_mode::rb:
      return "rb";

    case file_mode::w:
      return "w";

    case file_mode::wb:
      return "wb";

    case file_mode::a:
      return "a";

    case file_mode::ab:
      return "ab";

    case file_mode::rx:
      return "rx";

    case file_mode::rbx:
      return "rbx";

    case file_mode::wx:
      return "wx";

    case file_mode::wbx:
      return "wbx";

    case file_mode::ax:
      return "ax";

    case file_mode::abx:
      return "abx";

    default:
      throw exception{"Did not recognize file mode!"};
  }
}

inline auto operator<<(std::ostream& stream, const file_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

enum class seek_mode
{
  from_beginning = RW_SEEK_SET,       ///< From the beginning.
  relative_to_current = RW_SEEK_CUR,  ///< Relative to the current read point.
  relative_to_end = RW_SEEK_END       ///< Relative to the end.
};

[[nodiscard]] constexpr auto to_string(const seek_mode mode) -> std::string_view
{
  switch (mode) {
    case seek_mode::from_beginning:
      return "from_beginning";

    case seek_mode::relative_to_current:
      return "relative_to_current";

    case seek_mode::relative_to_end:
      return "relative_to_end";

    default:
      throw exception{"Did not recognize seek mode!"};
  }
}

inline auto operator<<(std::ostream& stream, const seek_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

/**
 * Represents a file context or handle.
 *
 * This class differs slightly from other library classes in that it is owning, but it
 * does not throw if the internal pointer can't be created, etc. This is because file
 * operations are error-prone, and we don't want to use exceptions for control flow.
 */
class file final
{
 public:
  using size_type = usize;

  explicit file(SDL_RWops* context) noexcept : mContext{context} {}

  file(const char* path, const file_mode mode) noexcept
      : mContext{SDL_RWFromFile(path, stringify(mode))}
  {}

  file(const std::string& path, const file_mode mode) noexcept : file{path.c_str(), mode} {}

  template <typename T>
  auto write(const T* data, const size_type count) noexcept -> size_type
  {
    assert(mContext);
    return SDL_RWwrite(this->data(), data, sizeof(T), count);
  }

  template <typename T, size_type Size>
  auto write(const T (&data)[Size]) noexcept -> size_type
  {
    return write(data, Size);
  }

  // clang-format off

  /**
   * Writes the contents of a container to the file.
   *
   * \pre `Container` must be a collection that stores its data contiguously.
   *
   * \tparam Container a contiguous container, e.g. `std::vector` or `std::array`.
   *
   * \param container the container that will be written to the file.
   *
   * \return the number of objects that were written.
   */
  template <typename Container>
  auto write(const Container& container) noexcept(noexcept(container.data()) &&
                                                  noexcept(container.size()))
      -> size_type
  {
    return write(container.data(), container.size());
  }

  // clang-format on

  auto write_byte(const uint8 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteU8(data(), value) == 1;
  }

  auto write_native_as_little_endian(const uint16 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteLE16(data(), value) == 1;
  }

  auto write_native_as_little_endian(const uint32 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteLE32(data(), value) == 1;
  }

  auto write_native_as_little_endian(const uint64 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteLE64(data(), value) == 1;
  }

  auto write_native_as_big_endian(const uint16 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteBE16(data(), value) == 1;
  }

  auto write_native_as_big_endian(const uint32 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteBE32(data(), value) == 1;
  }

  auto write_native_as_big_endian(const uint64 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteBE64(data(), value) == 1;
  }

  template <typename T>
  auto read_to(T* data, const size_type maxCount) noexcept -> size_type
  {
    assert(data);
    assert(mContext);
    return SDL_RWread(this->data(), data, sizeof(T), maxCount);
  }

  template <typename T, size_type Size>
  auto read_to(bounded_array_ref<T, Size> data) noexcept -> size_type
  {
    return read_to(data, Size);
  }

  // clang-format off

  template <typename Container>
  auto read_to(Container& container) noexcept(noexcept(container.data()) &&
                                              noexcept(container.size()))
      -> size_type
  {
    return read_to(container.data(), container.size());
  }

  // clang-format on

  template <typename T>
  auto read() noexcept(noexcept(T{})) -> T
  {
    T value{};
    read_to(&value, 1);
    return value;
  }

  auto read_byte() noexcept -> uint8
  {
    assert(mContext);
    return SDL_ReadU8(data());
  }

  auto read_little_endian_u16() noexcept -> uint16
  {
    assert(mContext);
    return SDL_ReadLE16(data());
  }

  auto read_little_endian_u32() noexcept -> uint32
  {
    assert(mContext);
    return SDL_ReadLE32(data());
  }

  auto read_little_endian_u64() noexcept -> uint64
  {
    assert(mContext);
    return SDL_ReadLE64(data());
  }

  auto read_big_endian_u16() noexcept -> uint16
  {
    assert(mContext);
    return SDL_ReadBE16(data());
  }

  auto read_big_endian_u32() noexcept -> uint32
  {
    assert(mContext);
    return SDL_ReadBE32(data());
  }

  auto read_big_endian_u64() noexcept -> uint64
  {
    assert(mContext);
    return SDL_ReadBE64(data());
  }

  [[nodiscard]] auto seek(const int64 offset, const seek_mode mode) noexcept -> maybe<int64>
  {
    assert(mContext);
    const auto result = SDL_RWseek(data(), offset, to_underlying(mode));
    if (result != -1) {
      return result;
    }
    else {
      return nothing;
    }
  }

#ifndef CENTURION_NO_SDL_IMAGE

  [[nodiscard]] auto is_png() const noexcept -> bool { return IMG_isPNG(data()) == 1; }

  [[nodiscard]] auto is_ico() const noexcept -> bool { return IMG_isICO(data()) == 1; }

  [[nodiscard]] auto is_jpg() const noexcept -> bool { return IMG_isJPG(data()) == 1; }

  [[nodiscard]] auto is_bmp() const noexcept -> bool { return IMG_isBMP(data()) == 1; }

  [[nodiscard]] auto is_gif() const noexcept -> bool { return IMG_isGIF(data()) == 1; }

  [[nodiscard]] auto is_svg() const noexcept -> bool { return IMG_isSVG(data()) == 1; }

  [[nodiscard]] auto is_webp() const noexcept -> bool { return IMG_isWEBP(data()) == 1; }

  [[nodiscard]] auto is_tif() const noexcept -> bool { return IMG_isTIF(data()) == 1; }

  [[nodiscard]] auto is_pnm() const noexcept -> bool { return IMG_isPNM(data()) == 1; }

  [[nodiscard]] auto is_pcx() const noexcept -> bool { return IMG_isPCX(data()) == 1; }

  [[nodiscard]] auto is_lbm() const noexcept -> bool { return IMG_isLBM(data()) == 1; }

  [[nodiscard]] auto is_cur() const noexcept -> bool { return IMG_isCUR(data()) == 1; }

  [[nodiscard]] auto is_xcf() const noexcept -> bool { return IMG_isXCF(data()) == 1; }

  [[nodiscard]] auto is_xpm() const noexcept -> bool { return IMG_isXPM(data()) == 1; }

  [[nodiscard]] auto is_xv() const noexcept -> bool { return IMG_isXV(data()) == 1; }

#if SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)

  [[nodiscard]] auto is_avif() const noexcept -> bool { return IMG_isAVIF(data()) == 1; }
  [[nodiscard]] auto is_jxl() const noexcept -> bool { return IMG_isJXL(data()) == 1; }
  [[nodiscard]] auto is_qoi() const noexcept -> bool { return IMG_isQOI(data()) == 1; }

#endif  // SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)

#endif  // CENTURION_NO_SDL_IMAGE

  [[nodiscard]] auto offset() const noexcept -> int64
  {
    assert(mContext);
    return SDL_RWtell(data());
  }

  [[nodiscard]] auto type() const noexcept -> file_type
  {
    assert(mContext);
    return static_cast<file_type>(mContext->type);
  }

  [[nodiscard]] auto size() const noexcept -> maybe<usize>
  {
    assert(mContext);
    const auto result = SDL_RWsize(data());
    if (result != -1) {
      return result;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto data() const noexcept -> SDL_RWops* { return mContext.get(); }

  [[nodiscard]] auto is_ok() const noexcept -> bool { return mContext != nullptr; }

  /// Indicates whether the file handle is valid.
  explicit operator bool() const noexcept { return is_ok(); }

 private:
  managed_ptr<SDL_RWops> mContext;

  [[nodiscard]] static auto stringify(const file_mode mode) noexcept -> const char*
  {
    switch (mode) {
      default:
        assert(false);

      case file_mode::r:
        return "r";

      case file_mode::rb:
        return "rb";

      case file_mode::w:
        return "w";

      case file_mode::wb:
        return "wb";

      case file_mode::a:
        return "a";

      case file_mode::ab:
        return "ab";

      case file_mode::rx:
        return "r+";

      case file_mode::rbx:
        return "rb+";

      case file_mode::wx:
        return "w+";

      case file_mode::wbx:
        return "wb+";

      case file_mode::ax:
        return "a+";

      case file_mode::abx:
        return "ab+";
    }
  }
};

/// Returns the directory from which the application launched from.
[[nodiscard]] inline auto base_path() -> sdl_string { return sdl_string{SDL_GetBasePath()}; }

/// Returns the preferred path for storing application related files.
[[nodiscard]] inline auto preferred_path(const char* org, const char* app) -> sdl_string
{
  /* Looking at the SDL source code, it actually seems fine to supply a null
     string for the organization name. However, I haven't been able to find any
     documentation providing this guarantee, so we simply disallow null
     organization names. */
  assert(org);
  assert(app);
  return sdl_string{SDL_GetPrefPath(org, app)};
}

[[nodiscard]] inline auto preferred_path(const std::string& org, const std::string& app)
    -> sdl_string
{
  return preferred_path(org.c_str(), app.c_str());
}

}  // namespace cen

#endif  // CENTURION_FILESYSTEM_HPP_
