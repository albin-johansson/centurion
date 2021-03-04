/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_FILE_HEADER
#define CENTURION_FILE_HEADER

#include <SDL.h>

#include <cassert>   // assert
#include <cstddef>   // size_t
#include <memory>    // unique_ptr
#include <optional>  // optional
#include <string>    // string

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "integers.hpp"
#include "not_null.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup system
/// \{

enum class file_mode
{
  read,                        ///< "r"
  read_binary,                 ///< "rb"
  write,                       ///< "w"
  write_binary,                ///< "wb"
  append,                      ///< "a"
  append_binary,               ///< "ab"
  read_existing,               ///< "r+"
  read_existing_binary,        ///< "rb+"
  write_replace,               ///< "w+"
  write_replace_binary,        ///< "wb+"
  append_read_anywhere,        ///< "a+"
  append_read_anywhere_binary  ///< "ab+"
};

enum class seek_mode
{
  from_beginning = RW_SEEK_SET,       ///< From the beginning.
  relative_to_current = RW_SEEK_CUR,  ///< Relative to the current read point.
  relative_to_end = RW_SEEK_END       ///< Relative to the end.
};

enum class file_type : unsigned
{
  unknown = SDL_RWOPS_UNKNOWN,
  win32 = SDL_RWOPS_WINFILE,
  stdio = SDL_RWOPS_STDFILE,
  jni = SDL_RWOPS_JNIFILE,
  memory = SDL_RWOPS_MEMORY,
  memory_ro = SDL_RWOPS_MEMORY_RO
};

class file final
{
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a file handle based on an existing context.
   *
   * \param context the context that will be used.
   *
   * \throws exception if the supplied pointer is null.
   *
   * \since 5.3.0
   */
  explicit file(SDL_RWops* context) : m_context{context}
  {
    if (!m_context) {
      throw exception{"Null RWops context supplied to file constructor!"};
    }
  }

  /**
   * \brief Opens the file at the specified file path.
   *
   * \details Be sure to check the validity of the file, after construction.
   * \verbatim
   *  cen::file file{"foo", cen::file_mode::read_existing_binary};
   *  if (file) {
   *    // File was opened successfully!
   *  }
   * \endverbatim
   *
   * \param path the file path of the file.
   * \param mode the mode that will be used to open the file.
   *
   * \since 5.3.0
   */
  explicit file(const not_null<czstring> path, const file_mode mode) noexcept
      : m_context{SDL_RWFromFile(path, to_string(mode))}
  {}

  explicit file(const std::string& path, const file_mode mode) noexcept
      : file{path.c_str(), mode}
  {}

  /// \} End of construction

  /**
   * \brief Writes to the file.
   *
   * \tparam T the type of the data.
   *
   * \param data a pointer to the data that will be written to the file.
   * \param count the number of objects that will be written.
   *
   * \return the number of objects that were written to the file.
   *
   * \since 5.3.0
   */
  template <typename T>
  auto write(const T* data, const std::size_t count) noexcept -> std::size_t
  {
    return SDL_RWwrite(get(), data, sizeof(T), count);
  }

  template <typename T, std::size_t size>
  auto write(const T (&data)[size]) noexcept -> std::size_t
  {
    return write(data, size);
  }

  // clang-format off

  template <typename Container>
  auto write(const Container& container) noexcept(noexcept(container.data()) &&
                                                  noexcept(container.size()))
      -> std::size_t
  {
    return write(container.data(), container.size());
  }

  // clang-format on

  /**
   * \brief Reads data from the file.
   *
   * \tparam T the type of the data that will be read.
   *
   * \param[out] data the pointer to which the read data will be written to.
   * \param maxCount the maximum number of objects that will be read.
   *
   * \return the number of objects that were read.
   *
   * \since 5.3.0
   */
  template <typename T>
  auto read(T* data, const std::size_t maxCount) noexcept -> std::size_t
  {
    return SDL_RWread(get(), data, sizeof(T), maxCount);
  }

  // Reads a value of type T, where T must be default-constructible
  template <typename T>
  auto read() noexcept(noexcept(T{})) -> T
  {
    T value{};
    read(&value, 1);
    return value;
  }

  /**
   * \brief Seeks to the specified offset, using the specified seek mode.
   *
   * \param offset the offset to seek to.
   * \param mode the seek mode that will be used.
   *
   * \return the resulting offset in the data stream; `std::nullopt` if
   * something went wrong.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto seek(const i64 offset,  // NOLINT not const
                          const seek_mode mode) noexcept -> std::optional<i64>
  {
    const auto result = SDL_RWseek(get(), offset, static_cast<int>(mode));
    if (result != -1) {
      return result;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the current offset in the data stream.
   *
   * \return the current offset in the data stream.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto offset() const noexcept -> i64
  {
    return SDL_RWtell(get());
  }

  [[nodiscard]] auto type() const noexcept -> file_type
  {
    return static_cast<file_type>(m_context->type);
  }

  /**
   * \brief Returns the size of the file.
   *
   * \return the size of the file; `std::nullopt` if unknown.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto size() const noexcept -> std::optional<std::size_t>
  {
    const auto result = SDL_RWsize(get());
    if (result != -1) {
      return result;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Indicates whether or not the file holds a non-null pointer.
   *
   * \return `true` if the file holds a non-null pointer; `false` otherwise.
   *
   * \since 5.3.0
   */
  explicit operator bool() const noexcept
  {
    return m_context != nullptr;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_RWops*
  {
    return m_context.get();
  }

 private:
  struct deleter final
  {
    void operator()(SDL_RWops* data) noexcept
    {
      SDL_RWclose(data);
    }
  };
  std::unique_ptr<SDL_RWops, deleter> m_context;

  [[nodiscard]] static auto to_string(const file_mode mode) noexcept -> czstring
  {
    switch (mode) {
      default:
        assert(false);

      case file_mode::read:
        return "r";

      case file_mode::read_binary:
        return "rb";

      case file_mode::write:
        return "w";

      case file_mode::write_binary:
        return "wb";

      case file_mode::append:
        return "a";

      case file_mode::append_binary:
        return "ab";

      case file_mode::read_existing:
        return "r+";

      case file_mode::read_existing_binary:
        return "rb+";

      case file_mode::write_replace:
        return "w+";

      case file_mode::write_replace_binary:
        return "wb+";

      case file_mode::append_read_anywhere:
        return "a+";

      case file_mode::append_read_anywhere_binary:
        return "ab+";
    }
  }
};

/// \} End of system group

}  // namespace cen

#endif  // CENTURION_FILE_HEADER
