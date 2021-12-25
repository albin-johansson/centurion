#ifndef CENTURION_FILESYSTEM_HPP_
#define CENTURION_FILESYSTEM_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#include <cassert>      // assert
#include <cstddef>      // size_t
#include <optional>     // optional
#include <string>       // string
#include <string_view>  // string_view

#include "common.hpp"
#include "core/sdl_string.hpp"
#include "memory.hpp"

namespace cen {

enum class FileType : unsigned {
  Unknown = SDL_RWOPS_UNKNOWN,
  Win = SDL_RWOPS_WINFILE,
  Std = SDL_RWOPS_STDFILE,
  Jni = SDL_RWOPS_JNIFILE,
  Memory = SDL_RWOPS_MEMORY,
  MemoryReadOnly = SDL_RWOPS_MEMORY_RO
};

enum class FileMode {
  ReadExisting,             // "r"
  ReadExistingBinary,       // "rb"
  Write,                    // "w"
  WriteBinary,              // "wb"
  AppendOrCreate,           // "a"
  AppendOrCreateBinary,     // "ab"
  ReadWriteExisting,        // "r+"
  ReadWriteExistingBinary,  // "rb+"
  ReadWriteReplace,         // "w+"
  ReadWriteReplaceBinary,   // "wb+"
  ReadAppend,               // "a+"
  ReadAppendBinary          // "ab+"
};

enum class SeekMode {
  FromBeginning = RW_SEEK_SET,      ///< From the beginning.
  RelativeToCurrent = RW_SEEK_CUR,  ///< Relative to the current read point.
  RelativeToEnd = RW_SEEK_END       ///< Relative to the end.
};

class File final {
 public:
  explicit File(SDL_RWops* context) noexcept : mContext{context} {}

  File(const char* path, const FileMode mode) noexcept
      : mContext{SDL_RWFromFile(path, Stringify(mode))}
  {}

  File(const std::string& path, const FileMode mode) noexcept : File{path.c_str(), mode} {}

  template <typename T>
  auto Write(NotNull<const T*> data, const std::size_t count) noexcept -> std::size_t
  {
    assert(mContext);
    return SDL_RWwrite(get(), data, sizeof(T), count);
  }

  template <typename T, std::size_t size>
  auto Write(const T (&data)[size]) noexcept -> std::size_t
  {
    return Write(data, size);
  }

  // clang-format off

  template <typename Container>
  auto Write(const Container& container) noexcept(noexcept(container.data()) &&
                                                  noexcept(container.size()))
      -> std::size_t
  {
    return Write(container.data(), container.size());
  }

  // clang-format on

  auto WriteByte(const Uint8 value) noexcept -> Result
  {
    assert(mContext);
    return SDL_WriteU8(mContext.get(), value) == 1;
  }

  auto WriteNativeAsLittleEndian(const Uint16 value) noexcept -> Result
  {
    assert(mContext);
    return SDL_WriteLE16(mContext.get(), value) == 1;
  }

  auto WriteNativeAsLittleEndian(const Uint32 value) noexcept -> Result
  {
    assert(mContext);
    return SDL_WriteLE32(mContext.get(), value) == 1;
  }

  auto WriteNativeAsLittleEndian(const Uint64 value) noexcept -> Result
  {
    assert(mContext);
    return SDL_WriteLE64(mContext.get(), value) == 1;
  }

  auto WriteNativeAsBigEndian(const Uint16 value) noexcept -> Result
  {
    assert(mContext);
    return SDL_WriteBE16(mContext.get(), value) == 1;
  }

  auto WriteNativeAsBigEndian(const Uint32 value) noexcept -> Result
  {
    assert(mContext);
    return SDL_WriteBE32(mContext.get(), value) == 1;
  }

  auto WriteNativeAsBigEndian(const Uint64 value) noexcept -> Result
  {
    assert(mContext);
    return SDL_WriteBE64(mContext.get(), value) == 1;
  }

  [[nodiscard]] auto Seek(const Sint64 offset, const SeekMode mode) noexcept
      -> std::optional<Sint64>
  {
    assert(mContext);
    const auto result = SDL_RWseek(mContext.get(), offset, ToUnderlying(mode));
    if (result != -1) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

  template <typename T>
  auto ReadTo(T* data, const std::size_t maxCount) noexcept -> std::size_t
  {
    assert(mContext);
    return SDL_RWread(mContext.get(), data, sizeof(T), maxCount);
  }

  template <typename T, std::size_t size>
  auto ReadTo(T (&data)[size]) noexcept -> std::size_t
  {
    return ReadTo(data, size);
  }

  // clang-format off

  template <typename Container>
  auto ReadTo(Container& container) noexcept(noexcept(container.data()) &&
                                             noexcept(container.size()))
      -> std::size_t
  {
    return ReadTo(container.data(), container.size());
  }

  // clang-format on

  template <typename T>
  auto Read() noexcept(noexcept(T{})) -> T
  {
    T value{};
    ReadTo(&value, 1);
    return value;
  }

  auto ReadByte() noexcept -> Uint8
  {
    assert(mContext);
    return SDL_ReadU8(mContext.get());
  }

  auto ReadLittleEndianU16() noexcept -> Uint16
  {
    assert(mContext);
    return SDL_ReadLE16(mContext.get());
  }

  auto ReadLittleEndianU32() noexcept -> Uint32
  {
    assert(mContext);
    return SDL_ReadLE32(mContext.get());
  }

  auto ReadLittleEndianU64() noexcept -> Uint64
  {
    assert(mContext);
    return SDL_ReadLE64(mContext.get());
  }

  auto ReadBigEndianU16() noexcept -> Uint16
  {
    assert(mContext);
    return SDL_ReadBE16(mContext.get());
  }

  auto ReadBigEndianU32() noexcept -> Uint32
  {
    assert(mContext);
    return SDL_ReadBE32(mContext.get());
  }

  auto ReadBigEndianU64() noexcept -> Uint64
  {
    assert(mContext);
    return SDL_ReadBE64(mContext.get());
  }

#ifndef CENTURION_NO_SDL_IMAGE

  [[nodiscard]] auto IsPNG() const noexcept -> bool { return IMG_isPNG(mContext.get()) == 1; }

  [[nodiscard]] auto IsICO() const noexcept -> bool { return IMG_isICO(mContext.get()) == 1; }

  [[nodiscard]] auto IsJPG() const noexcept -> bool { return IMG_isJPG(mContext.get()) == 1; }

  [[nodiscard]] auto IsBMP() const noexcept -> bool { return IMG_isBMP(mContext.get()) == 1; }

  [[nodiscard]] auto IsGIF() const noexcept -> bool { return IMG_isGIF(mContext.get()) == 1; }

  [[nodiscard]] auto IsSVG() const noexcept -> bool { return IMG_isSVG(mContext.get()) == 1; }

  [[nodiscard]] auto IsWEBP() const noexcept -> bool
  {
    return IMG_isWEBP(mContext.get()) == 1;
  }

  [[nodiscard]] auto IsTIF() const noexcept -> bool { return IMG_isTIF(mContext.get()) == 1; }

  [[nodiscard]] auto IsPNM() const noexcept -> bool { return IMG_isPNM(mContext.get()) == 1; }

  [[nodiscard]] auto IsPCX() const noexcept -> bool { return IMG_isPCX(mContext.get()) == 1; }

  [[nodiscard]] auto IsLBM() const noexcept -> bool { return IMG_isLBM(mContext.get()) == 1; }

  [[nodiscard]] auto IsCUR() const noexcept -> bool { return IMG_isCUR(mContext.get()) == 1; }

  [[nodiscard]] auto IsXCF() const noexcept -> bool { return IMG_isXCF(mContext.get()) == 1; }

  [[nodiscard]] auto IsXPM() const noexcept -> bool { return IMG_isXPM(mContext.get()) == 1; }

  [[nodiscard]] auto IsXV() const noexcept -> bool { return IMG_isXV(mContext.get()) == 1; }

#endif  // CENTURION_NO_SDL_IMAGE

  [[nodiscard]] auto GetOffset() const noexcept -> Sint64
  {
    assert(mContext);
    return SDL_RWtell(mContext.get());
  }

  [[nodiscard]] auto GetType() const noexcept -> FileType
  {
    assert(mContext);
    return static_cast<FileType>(mContext->type);
  }

  [[nodiscard]] auto GetSize() const noexcept -> std::optional<std::size_t>
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

  [[nodiscard]] auto get() const noexcept -> SDL_RWops* { return mContext.get(); }

  explicit operator bool() const noexcept { return mContext != nullptr; }

 private:
  Managed<SDL_RWops> mContext;

  [[nodiscard]] static auto Stringify(const FileMode mode) noexcept -> const char*
  {
    switch (mode) {
      default:
        assert(false);

      case FileMode::ReadExisting:
        return "r";

      case FileMode::ReadExistingBinary:
        return "rb";

      case FileMode::Write:
        return "w";

      case FileMode::WriteBinary:
        return "wb";

      case FileMode::AppendOrCreate:
        return "a";

      case FileMode::AppendOrCreateBinary:
        return "ab";

      case FileMode::ReadWriteExisting:
        return "r+";

      case FileMode::ReadWriteExistingBinary:
        return "rb+";

      case FileMode::ReadWriteReplace:
        return "w+";

      case FileMode::ReadWriteReplaceBinary:
        return "wb+";

      case FileMode::ReadAppend:
        return "a+";

      case FileMode::ReadAppendBinary:
        return "ab+";
    }
  }
};

/* Returns the directory from which the application launched from. */
[[nodiscard]] inline auto GetBasePath() -> sdl_string
{
  return sdl_string{SDL_GetBasePath()};
}

/* Returns the preferred path for storing application related files. */
[[nodiscard]] inline auto GetPreferredPath(const char* org, const char* app) -> sdl_string
{
  /* Looking at the SDL source code, it actually seems fine to supply a null
     string for the organization name. However, I haven't been able to find any
     documentation providing this guarantee, so we simply disallow null
     organization names. */
  assert(org);
  assert(app);
  return sdl_string{SDL_GetPrefPath(org, app)};
}

[[nodiscard]] inline auto GetPreferredPath(const std::string& org, const std::string& app)
    -> sdl_string
{
  return GetPreferredPath(org.c_str(), app.c_str());
}

}  // namespace cen

#endif  // CENTURION_FILESYSTEM_HPP_
