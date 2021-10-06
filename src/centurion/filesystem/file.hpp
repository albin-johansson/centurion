#ifndef CENTURION_FILE_HEADER
#define CENTURION_FILE_HEADER

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#include <cassert>   // assert
#include <cstddef>   // size_t
#include <memory>    // unique_ptr
#include <optional>  // optional
#include <string>    // string

#include "../core/integers.hpp"
#include "../core/not_null.hpp"
#include "../core/result.hpp"
#include "../core/str.hpp"
#include "../core/to_underlying.hpp"
#include "file_mode.hpp"
#include "file_type.hpp"
#include "seek_mode.hpp"

namespace cen {

/// \addtogroup filesystem
/// \{

/**
 * \class file
 *
 * \brief Represents a file "context" or handle.
 *
 * \note This class differs slightly from other library classes in that it is owning, but
 * it does *not* throw if the internal pointer can't be created, etc. This is because file
 * operations are error-prone, so we want to avoid throwing a bunch of exceptions, for
 * performance reasons.
 *
 * \since 5.3.0
 */
class file final
{
 public:
  using size_type = std::size_t;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a file handle based on an existing context.
   *
   * \param context the context that will be used.
   *
   * \since 5.3.0
   */
  explicit file(SDL_RWops* context) noexcept : m_context{context}
  {}

  /**
   * \brief Opens the file at the specified file path.
   *
   * \details Be sure to check the validity of the file, after construction.
   * \code{cpp}
   *   cen::file file{"foo", cen::file_mode::read_existing_binary};
   *   if (file) {
   *     // File was opened successfully!
   *   }
   * \endcode
   *
   * \param path the path of the file.
   * \param mode the mode that will be used to open the file.
   *
   * \since 5.3.0
   */
  file(const not_null<str> path, const file_mode mode) noexcept
      : m_context{SDL_RWFromFile(path, to_string(mode))}
  {}

  /// \copydoc file(not_null<str>, file_mode)
  file(const std::string& path, const file_mode mode) noexcept : file{path.c_str(), mode}
  {}

  /// \} End of construction

  /// \name Write API
  /// \{

  /**
   * \brief Writes the supplied data to the file.
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
  auto write(not_null<const T*> data, const size_type count) noexcept -> size_type
  {
    assert(m_context);
    return SDL_RWwrite(get(), data, sizeof(T), count);
  }

  /**
   * \brief Writes the contents of an array to the file, whose size is known at
   * compile-time.
   *
   * \tparam T the type of the array elements.
   * \tparam size the size of the array.
   *
   * \param data the data that will be written.
   *
   * \return the number of objects that were written.
   *
   * \since 5.3.0
   */
  template <typename T, size_type size>
  auto write(const T (&data)[size]) noexcept -> size_type
  {
    return write(data, size);
  }

  // clang-format off

  /**
   * \brief Writes the contents of a container to the file.
   *
   * \pre `Container` *must* be a collection that stores its data contiguously! The
   * behaviour of this function is undefined otherwise.
   *
   * \tparam Container a contiguous container, e.g. `std::vector` or `std::array`.
   *
   * \param container the container that will be written to the file.
   *
   * \return the number of objects that were written.
   *
   * \since 5.3.0
   */
  template <typename Container>
  auto write(const Container& container) noexcept(noexcept(container.data()) &&
                                                  noexcept(container.size()))
      -> size_type
  {
    return write(container.data(), container.size());
  }

  // clang-format on

  /**
   * \brief Writes an unsigned 8-bit integer to the file.
   *
   * \pre the internal file context must not be null.
   *
   * \param value the value that will be written.
   *
   * \return `success` if the value was written to the file; `failure` otherwise.
   *
   * \since 5.3.0
   */
  auto write_byte(const u8 value) noexcept -> result
  {
    assert(m_context);
    return SDL_WriteU8(m_context.get(), value) == 1;
  }

  /**
   * \brief Writes an unsigned 16-bit integer to the file, as a little endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \param value the value that will be written, in the native endianness.
   *
   * \return `success` if the value was written to the file; `failure` otherwise.
   *
   * \since 5.3.0
   */
  auto write_as_little_endian(const u16 value) noexcept -> result
  {
    assert(m_context);
    return SDL_WriteLE16(m_context.get(), value) == 1;
  }

  /**
   * \brief Writes an unsigned 32-bit integer to the file, as a little endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \param value the value that will be written, in the native endianness.
   *
   * \return `success` if the value was written to the file; `failure` otherwise.
   *
   * \since 5.3.0
   */
  auto write_as_little_endian(const u32 value) noexcept -> result
  {
    assert(m_context);
    return SDL_WriteLE32(m_context.get(), value) == 1;
  }

  /**
   * \brief Writes an unsigned 64-bit integer to the file, as a little endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \param value the value that will be written, in the native endianness.
   *
   * \return `success` if the value was written to the file; `failure` otherwise.
   *
   * \since 5.3.0
   */
  auto write_as_little_endian(const u64 value) noexcept -> result
  {
    assert(m_context);
    return SDL_WriteLE64(m_context.get(), value) == 1;
  }

  /**
   * \brief Writes an unsigned 16-bit integer to the file, as a big endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \param value the value that will be written, in the native endianness.
   *
   * \return `success` if the value was written to the file; `failure` otherwise.
   *
   * \since 5.3.0
   */
  auto write_as_big_endian(const u16 value) noexcept -> result
  {
    assert(m_context);
    return SDL_WriteBE16(m_context.get(), value) == 1;
  }

  /**
   * \brief Writes an unsigned 32-bit integer to the file, as a big endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \param value the value that will be written, in the native endianness.
   *
   * \return `success` if the value was written to the file; `failure` otherwise.
   *
   * \since 5.3.0
   */
  auto write_as_big_endian(const u32 value) noexcept -> result
  {
    assert(m_context);
    return SDL_WriteBE32(m_context.get(), value) == 1;
  }

  /**
   * \brief Writes an unsigned 64-bit integer to the file, as a big endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \param value the value that will be written, in the native endianness.
   *
   * \return `success` if the value was written to the file; `failure` otherwise.
   *
   * \since 5.3.0
   */
  auto write_as_big_endian(const u64 value) noexcept -> result
  {
    assert(m_context);
    return SDL_WriteBE64(m_context.get(), value) == 1;
  }

  /// \} End of write API

  /// \name Read API
  /// \{

  /**
   * \brief Reads data from the file.
   *
   * \pre the internal file context must not be null.
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
  auto read_to(T* data, const size_type maxCount) noexcept -> size_type
  {
    assert(m_context);
    return SDL_RWread(m_context.get(), data, sizeof(T), maxCount);
  }

  /**
   * \brief Reads data from the file to an array whose size is known at compile-time. This
   * function uses the size of the supplied array to determine the amount of elements to
   * read.
   *
   * \pre the internal file context must not be null.
   *
   * \tparam T the type of the data that will be read.
   * \tparam size the size of the array.
   *
   * \param[out] data the pointer to which the read data will be written to.
   *
   * \return the number of objects that were read.
   *
   * \since 5.3.0
   */
  template <typename T, size_type size>
  auto read_to(T (&data)[size]) noexcept -> size_type
  {
    return read_to(data, size);
  }

  // clang-format off

  /**
   * \brief Reads data from the file to a container. This function uses the size of the
   * supplied container to determine the amount of elements to read.
   *
   * \pre the internal file context must not be null.
   * \pre `Container` *must* be a collection that stores its data contiguously! The
   * behaviour of this function is undefined otherwise.
   *
   * \tparam Container the type of the data that will be read, e.g. `std::vector` or
   * `std::array`.
   *
   * \param[out] container the container to which the read data will be written to.
   *
   * \return the number of objects that were read.
   *
   * \since 5.3.0
   */
  template <typename Container>
  auto read_to(Container& container) noexcept(noexcept(container.data()) &&
                                              noexcept(container.size()))
      -> size_type
  {
    return read_to(container.data(), container.size());
  }

  // clang-format on

  // Reads a value of type T, where T must be default-constructible

  /**
   * \brief Reads a single value from the file.
   *
   * \pre the internal file context must not be null.
   *
   * \note `T` must be default-constructible in order to use this function.
   *
   * \tparam T the type of the value, which must be default-constructible.
   *
   * \return the read value.
   *
   * \since 5.3.0
   */
  template <typename T>
  auto read() noexcept(noexcept(T{})) -> T
  {
    T value{};
    read_to(&value, 1);
    return value;
  }

  /**
   * \brief Reads an unsigned 8-bit integer from the file.
   *
   * \pre the internal file context must not be null.
   *
   * \return the read value.
   *
   * \since 5.3.0
   */
  auto read_byte() noexcept -> u8
  {
    assert(m_context);
    return SDL_ReadU8(m_context.get());
  }

  /**
   * \brief Reads an unsigned 16-bit integer from the file, as a little endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \return the read value.
   *
   * \since 5.3.0
   */
  auto read_little_endian_u16() noexcept -> u16
  {
    assert(m_context);
    return SDL_ReadLE16(m_context.get());
  }

  /**
   * \brief Reads an unsigned 32-bit integer from the file, as a little endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \return the read value.
   *
   * \since 5.3.0
   */
  auto read_little_endian_u32() noexcept -> u32
  {
    assert(m_context);
    return SDL_ReadLE32(m_context.get());
  }

  /**
   * \brief Reads an unsigned 64-bit integer from the file, as a little endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \return the read value.
   *
   * \since 5.3.0
   */
  auto read_little_endian_u64() noexcept -> u64
  {
    assert(m_context);
    return SDL_ReadLE64(m_context.get());
  }

  /**
   * \brief Reads an unsigned 16-bit integer from the file, as a big endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \return the read value.
   *
   * \since 5.3.0
   */
  auto read_big_endian_u16() noexcept -> u16
  {
    assert(m_context);
    return SDL_ReadBE16(m_context.get());
  }

  /**
   * \brief Reads an unsigned 32-bit integer from the file, as a big endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \return the read value.
   *
   * \since 5.3.0
   */
  auto read_big_endian_u32() noexcept -> u32
  {
    assert(m_context);
    return SDL_ReadBE32(m_context.get());
  }

  /**
   * \brief Reads an unsigned 64-bit integer from the file, as a big endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \return the read value.
   *
   * \since 5.3.0
   */
  auto read_big_endian_u64() noexcept -> u64
  {
    assert(m_context);
    return SDL_ReadBE64(m_context.get());
  }

  /// \} End of read API

  /// \name File type queries
  /// \{

#ifndef CENTURION_NO_SDL_IMAGE

  /**
   * \brief Indicates whether or not the file represents a PNG image.
   *
   * \return `true` if the file is a PNG image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_png() const noexcept -> bool
  {
    return IMG_isPNG(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents an ICO image.
   *
   * \return `true` if the file is an ICO image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_ico() const noexcept -> bool
  {
    return IMG_isICO(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents a JPG image.
   *
   * \return `true` if the file is a JPG image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_jpg() const noexcept -> bool
  {
    return IMG_isJPG(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents a BMP image.
   *
   * \return `true` if the file is a BMP image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_bmp() const noexcept -> bool
  {
    return IMG_isBMP(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents a GIF.
   *
   * \return `true` if the file is a GIF; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_gif() const noexcept -> bool
  {
    return IMG_isGIF(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents an SVG image.
   *
   * \return `true` if the file is an SVG image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_svg() const noexcept -> bool
  {
    return IMG_isSVG(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents a WEBP image.
   *
   * \return `true` if the file is a WEBP image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_webp() const noexcept -> bool
  {
    return IMG_isWEBP(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents a TIF image.
   *
   * \return `true` if the file is a TIF image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_tif() const noexcept -> bool
  {
    return IMG_isTIF(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents a PNM image.
   *
   * \return `true` if the file is a PNM image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_pnm() const noexcept -> bool
  {
    return IMG_isPNM(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents a PCX image.
   *
   * \return `true` if the file is a PCX image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_pcx() const noexcept -> bool
  {
    return IMG_isPCX(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents an LBM image.
   *
   * \return `true` if the file is an LBM image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_lbm() const noexcept -> bool
  {
    return IMG_isLBM(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents a CUR image.
   *
   * \return `true` if the file is a CUR image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_cur() const noexcept -> bool
  {
    return IMG_isCUR(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents an XCF image.
   *
   * \return `true` if the file is an XCF image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_xcf() const noexcept -> bool
  {
    return IMG_isXCF(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents an XPM image.
   *
   * \return `true` if the file is an XPM image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_xpm() const noexcept -> bool
  {
    return IMG_isXPM(m_context.get()) == 1;
  }

  /**
   * \brief Indicates whether or not the file represents an XV image.
   *
   * \return `true` if the file is an XV image; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_xv() const noexcept -> bool
  {
    return IMG_isXV(m_context.get()) == 1;
  }

#endif  // CENTURION_NO_SDL_IMAGE

  /// \} End of file type queries

  /**
   * \brief Seeks to the specified offset, using the specified seek mode.
   *
   * \param offset the offset to seek to.
   * \param mode the seek mode that will be used.
   *
   * \return the resulting offset in the data stream; `std::nullopt` if something went
   * wrong.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto seek(const i64 offset, const seek_mode mode) noexcept
      -> std::optional<i64>
  {
    assert(m_context);
    const auto result = SDL_RWseek(m_context.get(), offset, to_underlying(mode));
    if (result != -1) {
      return result;
    }
    else {
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
    assert(m_context);
    return SDL_RWtell(m_context.get());
  }

  /**
   * \brief Returns the file type associated with the instance.
   *
   * \return the associated file type.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto type() const noexcept -> file_type
  {
    assert(m_context);
    return static_cast<file_type>(m_context->type);
  }

  /**
   * \brief Returns the size of the file.
   *
   * \return the size of the file; `std::nullopt` if unknown.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto size() const noexcept -> std::optional<size_type>
  {
    assert(m_context);
    const auto result = SDL_RWsize(m_context.get());
    if (result != -1) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns a pointer to the internal file context.
   *
   * \return a pointer to the internal file context, can be null.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_RWops*
  {
    return m_context.get();
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

 private:
  struct deleter final
  {
    void operator()(SDL_RWops* context) noexcept
    {
      SDL_RWclose(context);
    }
  };
  std::unique_ptr<SDL_RWops, deleter> m_context;

  [[nodiscard]] static auto to_string(const file_mode mode) noexcept -> str
  {
    switch (mode) {
      default:
        assert(false);

      case file_mode::read_existing:
        return "r";

      case file_mode::read_existing_binary:
        return "rb";

      case file_mode::write:
        return "w";

      case file_mode::write_binary:
        return "wb";

      case file_mode::append_or_create:
        return "a";

      case file_mode::append_or_create_binary:
        return "ab";

      case file_mode::read_write_existing:
        return "r+";

      case file_mode::read_write_existing_binary:
        return "rb+";

      case file_mode::read_write_replace:
        return "w+";

      case file_mode::read_write_replace_binary:
        return "wb+";

      case file_mode::read_append:
        return "a+";

      case file_mode::read_append_binary:
        return "ab+";
    }
  }
};

/// \} End of group filesystem

}  // namespace cen

#endif  // CENTURION_FILE_HEADER
