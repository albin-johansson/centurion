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

/**
 * \defgroup filesystem Filesystem
 *
 * \brief Provides low-level abstractions for files and directories.
 */

/// \addtogroup filesystem
/// \{

/**
 * \brief Represents various file types.
 */
enum class file_type : unsigned
{
  unknown = SDL_RWOPS_UNKNOWN,
  win = SDL_RWOPS_WINFILE,
  std = SDL_RWOPS_STDFILE,
  jni = SDL_RWOPS_JNIFILE,
  memory = SDL_RWOPS_MEMORY,
  memory_ro = SDL_RWOPS_MEMORY_RO
};

/// \name File type functions
/// \{

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

/// \} End of file type functions

/**
 * \brief Represents different file modes.
 *
 * \details The enumerators directly correspond to each of the possible SDL file mode strings.
 */
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

/// \name File mode functions
/// \{

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

/// \} End of file mode functions

enum class seek_mode
{
  from_beginning = RW_SEEK_SET,       ///< From the beginning.
  relative_to_current = RW_SEEK_CUR,  ///< Relative to the current read point.
  relative_to_end = RW_SEEK_END       ///< Relative to the end.
};

/// \name Seek mode functions
/// \{

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

/// \} End of seek mode functions

/**
 * \brief Represents a file context or handle.
 *
 * \note This class differs slightly from other library classes in that it is owning, but it
 * does not throw if the internal pointer can't be created, etc. This is because file
 * operations are error-prone, and we don't want to use exceptions for control flow.
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
   */
  explicit file(SDL_RWops* context) noexcept : mContext{context} {}

  /**
   * \brief Opens the file at the specified file path.
   *
   * \details Be sure to check the validity of the file after construction.
   * \code{cpp}
   *   cen::file file{"foo", cen::file_mode::rb};
   *   if (file) {
   *     // File was opened successfully!
   *   }
   * \endcode
   *
   * \param path the path of the file.
   * \param mode the mode that will be used to open the file.
   */
  file(const char* path, const file_mode mode) noexcept
      : mContext{SDL_RWFromFile(path, stringify(mode))}
  {}

  /// \copydoc file(const char*, file_mode)
  file(const std::string& path, const file_mode mode) noexcept : file{path.c_str(), mode} {}

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
   */
  template <typename T>
  auto write(not_null<const T*> data, const size_type count) noexcept -> size_type
  {
    assert(mContext);
    return SDL_RWwrite(mContext.get(), data, sizeof(T), count);
  }

  /**
   * \brief Writes the contents of an array to the file, whose size is known at compile-time.
   *
   * \tparam T the type of the array elements.
   * \tparam Size the size of the array.
   *
   * \param data the data that will be written.
   *
   * \return the number of objects that were written.
   */
  template <typename T, size_type Size>
  auto write(const T (&data)[Size]) noexcept -> size_type
  {
    return write(data, Size);
  }

  // clang-format off

  /**
   * \brief Writes the contents of a container to the file.
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

  /**
   * \brief Writes an unsigned 8-bit integer to the file.
   *
   * \param value the value that will be written.
   *
   * \return `success` if the value was written to the file; `failure` otherwise.
   */
  auto write_byte(const uint8 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteU8(mContext.get(), value) == 1;
  }

  /**
   * \brief Writes an unsigned integer to the file, as a little endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \param value the value that will be written, in the native endianness.
   *
   * \return `success` if the value was written to the file; `failure` otherwise.
   */
  auto write_native_as_little_endian(const uint16 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteLE16(mContext.get(), value) == 1;
  }

  /// \copydoc write_native_as_little_endian()
  auto write_native_as_little_endian(const uint32 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteLE32(mContext.get(), value) == 1;
  }

  /// \copydoc write_native_as_little_endian()
  auto write_native_as_little_endian(const uint64 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteLE64(mContext.get(), value) == 1;
  }

  /**
   * \brief Writes an unsigned integer to the file, as a big endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \param value the value that will be written, in the native endianness.
   *
   * \return `success` if the value was written to the file; `failure` otherwise.
   */
  auto write_native_as_big_endian(const uint16 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteBE16(mContext.get(), value) == 1;
  }

  /// \copydoc write_native_as_big_endian()
  auto write_native_as_big_endian(const uint32 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteBE32(mContext.get(), value) == 1;
  }

  /// \copydoc write_native_as_big_endian()
  auto write_native_as_big_endian(const uint64 value) noexcept -> result
  {
    assert(mContext);
    return SDL_WriteBE64(mContext.get(), value) == 1;
  }

  /// \} End of write API

  /// \name Read API
  /// \{

  /**
   * \brief Reads data from the file.
   *
   * \tparam T the type of the data that will be read.
   *
   * \param[out] data the pointer to which the read data will be written to.
   * \param maxCount the maximum number of objects that will be read.
   *
   * \return the number of objects that were read.
   */
  template <typename T>
  auto read_to(T* data, const size_type maxCount) noexcept -> size_type
  {
    assert(data);
    assert(mContext);
    return SDL_RWread(mContext.get(), data, sizeof(T), maxCount);
  }

  /**
   * \brief Reads data from the file to an array whose size is known at compile-time.
   *
   * \tparam T the type of the data that will be read.
   * \tparam Size the size of the array.
   *
   * \param[out] data the pointer to which the read data will be written to.
   *
   * \return the number of objects that were read.
   */
  template <typename T, size_type Size>
  auto read_to(bounded_array_ref<T, Size> data) noexcept -> size_type
  {
    return read_to(data, Size);
  }

  // clang-format off

  /**
   * \brief Reads data from the file to a container.
   *
   * \pre `Container` *must* be a collection that stores its data contiguously!
   *
   * \tparam Container a contiguous container type, e.g. `std::vector` or `std::array`.
   *
   * \param[out] container the container to which the read data will be written to.
   *
   * \return the number of objects that were read.
   */
  template <typename Container>
  auto read_to(Container& container) noexcept(noexcept(container.data()) &&
                                              noexcept(container.size()))
      -> size_type
  {
    return read_to(container.data(), container.size());
  }

  // clang-format on

  /**
   * \brief Reads a single value from the file.
   *
   * \tparam T the type of the value, which must be default-constructible.
   *
   * \return the read value.
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
   * \return the read value.
   */
  auto read_byte() noexcept -> uint8
  {
    assert(mContext);
    return SDL_ReadU8(mContext.get());
  }

  /**
   * \brief Reads an unsigned integer from the file, as a little endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \return the read value.
   */
  auto read_little_endian_u16() noexcept -> uint16
  {
    assert(mContext);
    return SDL_ReadLE16(mContext.get());
  }

  /// \copydoc read_little_endian_u16()
  auto read_little_endian_u32() noexcept -> uint32
  {
    assert(mContext);
    return SDL_ReadLE32(mContext.get());
  }

  /// \copydoc read_little_endian_u16()
  auto read_little_endian_u64() noexcept -> uint64
  {
    assert(mContext);
    return SDL_ReadLE64(mContext.get());
  }

  /**
   * \brief Reads an unsigned integer from the file, as a big endian value.
   *
   * \pre the internal file context must not be null.
   *
   * \return the read value.
   */
  auto read_big_endian_u16() noexcept -> uint16
  {
    assert(mContext);
    return SDL_ReadBE16(mContext.get());
  }

  /// \copydoc read_big_endian_u16()
  auto read_big_endian_u32() noexcept -> uint32
  {
    assert(mContext);
    return SDL_ReadBE32(mContext.get());
  }

  /// \copydoc read_big_endian_u16()
  auto read_big_endian_u64() noexcept -> uint64
  {
    assert(mContext);
    return SDL_ReadBE64(mContext.get());
  }

  /// \} End of read API

  /**
   * \brief Seeks to the specified offset, using the specified seek mode.
   *
   * \param offset the offset to seek to.
   * \param mode the seek mode that will be used.
   *
   * \return the resulting offset in the data stream;
   *         an empty optional is returned if something went wrong.
   */
  [[nodiscard]] auto seek(const int64 offset, const seek_mode mode) noexcept
      -> std::optional<int64>
  {
    assert(mContext);
    const auto result = SDL_RWseek(mContext.get(), offset, to_underlying(mode));
    if (result != -1) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

#ifndef CENTURION_NO_SDL_IMAGE

  /// \name File type queries
  /// \{

  /**
   * \brief Indicates whether the file represents a PNG image.
   *
   * \return `true` if the file is a PNG image; `false` otherwise.
   */
  [[nodiscard]] auto is_png() const noexcept -> bool { return IMG_isPNG(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents an ICO image.
   *
   * \return `true` if the file is an ICO image; `false` otherwise.
   */
  [[nodiscard]] auto is_ico() const noexcept -> bool { return IMG_isICO(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents a JPEG image.
   *
   * \return `true` if the file is a JPEG image; `false` otherwise.
   */
  [[nodiscard]] auto is_jpg() const noexcept -> bool { return IMG_isJPG(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents a BMP image.
   *
   * \return `true` if the file is a BMP image; `false` otherwise.
   */
  [[nodiscard]] auto is_bmp() const noexcept -> bool { return IMG_isBMP(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents a GIF.
   *
   * \return `true` if the file is a GIF; `false` otherwise.
   */
  [[nodiscard]] auto is_gif() const noexcept -> bool { return IMG_isGIF(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents an SVG image.
   *
   * \return `true` if the file is an SVG image; `false` otherwise.
   */
  [[nodiscard]] auto is_svg() const noexcept -> bool { return IMG_isSVG(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents a WebP image.
   *
   * \return `true` if the file is a WebP image; `false` otherwise.
   */
  [[nodiscard]] auto is_webp() const noexcept -> bool
  {
    return IMG_isWEBP(mContext.get()) == 1;
  }

  /**
   * \brief Indicates whether the file represents a TIF image.
   *
   * \return `true` if the file is a TIF image; `false` otherwise.
   */
  [[nodiscard]] auto is_tif() const noexcept -> bool { return IMG_isTIF(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents a PNM image.
   *
   * \return `true` if the file is a PNM image; `false` otherwise.
   */
  [[nodiscard]] auto is_pnm() const noexcept -> bool { return IMG_isPNM(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents a PCX image.
   *
   * \return `true` if the file is a PCX image; `false` otherwise.
   */
  [[nodiscard]] auto is_pcx() const noexcept -> bool { return IMG_isPCX(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents an LBM image.
   *
   * \return `true` if the file is an LBM image; `false` otherwise.
   */
  [[nodiscard]] auto is_lbm() const noexcept -> bool { return IMG_isLBM(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents a CUR image.
   *
   * \return `true` if the file is a CUR image; `false` otherwise.
   */
  [[nodiscard]] auto is_cur() const noexcept -> bool { return IMG_isCUR(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents an XCF image.
   *
   * \return `true` if the file is an XCF image; `false` otherwise.
   */
  [[nodiscard]] auto is_xcf() const noexcept -> bool { return IMG_isXCF(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents an XPM image.
   *
   * \return `true` if the file is an XPM image; `false` otherwise.
   */
  [[nodiscard]] auto is_xpm() const noexcept -> bool { return IMG_isXPM(mContext.get()) == 1; }

  /**
   * \brief Indicates whether the file represents an XV image.
   *
   * \return `true` if the file is an XV image; `false` otherwise.
   */
  [[nodiscard]] auto is_xv() const noexcept -> bool { return IMG_isXV(mContext.get()) == 1; }

  /// \} End of file type queries

#endif  // CENTURION_NO_SDL_IMAGE

  /**
   * \brief Returns the current offset in the data stream.
   *
   * \return the offset in the data stream.
   */
  [[nodiscard]] auto offset() const noexcept -> int64
  {
    assert(mContext);
    return SDL_RWtell(mContext.get());
  }

  /**
   * \brief Returns the file type associated with the instance.
   *
   * \return the file type.
   */
  [[nodiscard]] auto type() const noexcept -> file_type
  {
    assert(mContext);
    return static_cast<file_type>(mContext->type);
  }

  /**
   * \brief Returns the size of the file.
   *
   * \return the file size; an empty optional is returned it it is unknown.
   */
  [[nodiscard]] auto size() const noexcept -> std::optional<std::size_t>
  {
    assert(mContext);
    const auto result = SDL_RWsize(mContext.get());
    if (result != -1) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto data() const noexcept -> SDL_RWops* { return mContext.get(); }

  /**
   * \brief Indicates whether the file handle is valid.
   *
   * \return `true` if the file holds a non-null handle; `false` otherwise.
   */
  explicit operator bool() const noexcept { return mContext != nullptr; }

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

/// \name Path functions
/// \{

/**
 * \brief Returns the directory from which the application launched from.
 *
 * \details The returned string represents the path to the directory from which application was
 * run from, and will end with a path separator (e.g. "\\" or "/").
 *
 * \note This might be an expensive operation, so it's recommended to only call this function
 * once and cache the returned path.
 *
 * \return the base path of the application;
 *         a null string is returned if the path cannot be obtained.
 */
[[nodiscard]] inline auto base_path() -> sdl_string
{
  return sdl_string{SDL_GetBasePath()};
}

/**
 * \brief Returns the preferred path for storing application related files.
 *
 * \details This function returns the path to the directory to which applications are
 * meant to write files such as preferences and save data, etc. This directory will be
 * unique per user and application. The returned path will end with a path separator (e.g.
 * "\\" or "/").
 *
 * \note Only use letters, numbers, and spaces in the supplied names!
 *
 * \param org the name of the organization.
 * \param app the name of the application.
 *
 * \return an absolute path to the preferred path for storing application files;
 *         a null string is returned if something goes wrong.
 */
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

/// \copydoc preferred_path()
[[nodiscard]] inline auto preferred_path(const std::string& org, const std::string& app)
    -> sdl_string
{
  return preferred_path(org.c_str(), app.c_str());
}

/// \} End of path functions

/// \} End of group filesystem

}  // namespace cen

#endif  // CENTURION_FILESYSTEM_HPP_
