// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

#include <cstdint>
#include <memory>
#include <optional>

#include <SDL3/SDL.h>

#include "centurion/core/error.hpp"
#include "centurion/io/filesystem.hpp"

namespace cen::inline v8_0_0 {

class storage_base
{
 public:
  virtual ~storage_base() noexcept = default;

  // SDL_CreateStorageDirectory
  auto create_directory(const char* path) noexcept -> result;

  // SDL_RemoveStoragePath
  auto remove_path(const char* path) noexcept -> result;

  // SDL_RenameStoragePath
  auto rename_path(const char* old_path,
                   const char* new_path) noexcept -> result;

  // SDL_EnumerateStorageDirectory
  auto enumerate_directory(const char* path,
                           SDL_EnumerateDirectoryCallback callback,
                           void* user_data = nullptr) noexcept -> result;

  // SDL_GlobStorageDirectory
  auto glob_directory(const char* path,
                      const char* pattern,
                      SDL_GlobFlags flags) noexcept
      -> std::optional<glob_directory_result>;

  // SDL_ReadStorageFile
  auto read_file(const char* path,
                 void* buffer,
                 std::uint64_t buffer_size) noexcept -> result;

  // SDL_WriteStorageFile
  auto write_file(const char* path,
                  const void* data,
                  std::uint64_t data_size) noexcept -> result;

  // SDL_GetStorageFileSize
  [[nodiscard]]
  auto file_size(const char* path) const noexcept
      -> std::optional<std::uint64_t>;

  // SDL_GetStoragePathInfo
  [[nodiscard]]
  auto path_info(const char* path) const noexcept
      -> std::optional<SDL_PathInfo>;

  // SDL_GetStorageSpaceRemaining
  [[nodiscard]]
  auto space_remaining() const noexcept -> std::uint64_t;

  // SDL_StorageReady
  [[nodiscard]]
  auto is_ready() const noexcept -> bool;

  [[nodiscard]]
  auto get() noexcept -> SDL_Storage*;

  [[nodiscard]]
  auto get() const noexcept -> const SDL_Storage*;

  [[nodiscard]]
  virtual auto unsafe_get() const noexcept -> SDL_Storage* = 0;
};

class storage final : public storage_base
{
 public:
  // SDL_OpenStorage
  [[nodiscard]]
  static auto open(const SDL_StorageInterface* interface,
                   void* user_data = nullptr) noexcept
      -> std::optional<storage>;

  // SDL_OpenFileStorage
  [[nodiscard]]
  static auto for_local(const char* base_path = nullptr) noexcept
      -> std::optional<storage>;

  // SDL_OpenTitleStorage
  [[nodiscard]]
  static auto for_title(const char* root_override,
                        SDL_PropertiesID props) noexcept
      -> std::optional<storage>;

  // SDL_OpenUserStorage
  [[nodiscard]]
  static auto for_user(const char* org,
                       const char* app,
                       SDL_PropertiesID props) noexcept
      -> std::optional<storage>;

  [[nodiscard]]
  auto unsafe_get() const noexcept -> SDL_Storage* override;

 private:
  struct storage_deleter
  {
    void operator()(SDL_Storage* ptr) const noexcept;
  };

  std::unique_ptr<SDL_Storage, storage_deleter> m_storage;

  explicit storage(SDL_Storage* ptr) noexcept;
};

class storage_ref final : public storage_base
{
 public:
  explicit storage_ref(SDL_Storage* ptr = nullptr) noexcept;

  /* implicit */ storage_ref(storage& other) noexcept;

  [[nodiscard]]
  explicit operator bool() const noexcept;

  [[nodiscard]]
  auto unsafe_get() const noexcept -> SDL_Storage* override;

 private:
  SDL_Storage* m_storage;
};

}  // namespace cen::inline v8_0_0
