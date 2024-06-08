// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/io/storage.hpp"

namespace cen::inline v8_0_0 {

auto storage_base::create_directory(const char* const path) noexcept -> result
{
  const auto ec = SDL_CreateStorageDirectory(get(), path);

  if (ec != 0) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto storage_base::remove_path(const char* const path) noexcept -> result
{
  const auto ec = SDL_RemoveStoragePath(get(), path);

  if (ec != 0) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto storage_base::rename_path(const char* const old_path,
                               const char* const new_path) noexcept -> result
{
  const auto ec = SDL_RenameStoragePath(get(), old_path, new_path);

  if (ec != 0) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto storage_base::enumerate_directory(const char* const path,
                                       SDL_EnumerateDirectoryCallback callback,
                                       void* const user_data) noexcept -> result
{
  const auto ec =
      SDL_EnumerateStorageDirectory(get(), path, callback, user_data);

  if (ec != 0) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto storage_base::glob_directory(const char* const path,
                                  const char* const pattern,
                                  const SDL_GlobFlags flags) noexcept
    -> std::optional<glob_directory_result>
{
  glob_directory_result result {};
  result.paths.reset(
      SDL_GlobStorageDirectory(get(), path, pattern, flags, &result.count));

  if (!result.paths) {
    emit_sdl_error();
    return std::nullopt;
  }

  return result;
}

auto storage_base::read_file(const char* const path,
                             void* const buffer,
                             const std::uint64_t buffer_size) noexcept -> result
{
  const auto ec = SDL_ReadStorageFile(get(), path, buffer, buffer_size);

  if (ec != 0) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto storage_base::write_file(const char* const path,
                              const void* const data,
                              const std::uint64_t data_size) noexcept -> result
{
  const auto ec = SDL_WriteStorageFile(get(), path, data, data_size);

  if (ec != 0) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto storage_base::file_size(const char* const path) const noexcept
    -> std::optional<std::uint64_t>
{
  std::uint64_t size {};
  const auto ec = SDL_GetStorageFileSize(unsafe_get(), path, &size);

  if (ec != 0) {
    emit_sdl_error();
    return std::nullopt;
  }

  return size;
}

auto storage_base::path_info(const char* const path) const noexcept
    -> std::optional<SDL_PathInfo>
{
  SDL_PathInfo info {};
  const auto ec = SDL_GetStoragePathInfo(unsafe_get(), path, &info);

  if (ec != 0) {
    emit_sdl_error();
    return std::nullopt;
  }

  return info;
}

auto storage_base::space_remaining() const noexcept -> std::uint64_t
{
  return SDL_GetStorageSpaceRemaining(unsafe_get());
}

auto storage_base::is_ready() const noexcept -> bool
{
  return SDL_StorageReady(unsafe_get()) == SDL_TRUE;
}

auto storage_base::get() noexcept -> SDL_Storage*
{
  return unsafe_get();
}

auto storage_base::get() const noexcept -> const SDL_Storage*
{
  return unsafe_get();
}

void storage::storage_deleter::operator()(SDL_Storage* const ptr) const noexcept
{
  const auto ec = SDL_CloseStorage(ptr);
  if (ec != 0) {
    emit_sdl_error();
  }
}

storage::storage(SDL_Storage* ptr) noexcept
  : m_storage {ptr}
{}

auto storage::open(const SDL_StorageInterface* const interface,
                   void* user_data) noexcept -> std::optional<storage>
{
  auto* const ptr = SDL_OpenStorage(interface, user_data);

  if (!ptr) {
    emit_sdl_error();
    return std::nullopt;
  }

  return storage {ptr};
}

auto storage::for_local(const char* const base_path) noexcept
    -> std::optional<storage>
{
  auto* const ptr = SDL_OpenFileStorage(base_path);

  if (!ptr) {
    emit_sdl_error();
    return std::nullopt;
  }

  return storage {ptr};
}

auto storage::for_title(const char* const root_override,
                        const SDL_PropertiesID props) noexcept
    -> std::optional<storage>
{
  auto* const ptr = SDL_OpenTitleStorage(root_override, props);

  if (!ptr) {
    emit_sdl_error();
    return std::nullopt;
  }

  return storage {ptr};
}

auto storage::for_user(const char* const org,
                       const char* const app,
                       const SDL_PropertiesID props) noexcept
    -> std::optional<storage>
{
  auto* const ptr = SDL_OpenUserStorage(org, app, props);

  if (!ptr) {
    emit_sdl_error();
    return std::nullopt;
  }

  return storage {ptr};
}

auto storage::unsafe_get() const noexcept -> SDL_Storage*
{
  return m_storage.get();
}

storage_ref::storage_ref(SDL_Storage* const ptr) noexcept
  : m_storage {ptr}
{}

storage_ref::storage_ref(storage& other) noexcept
  : storage_ref {other.get()}
{}

storage_ref::operator bool() const noexcept
{
  return m_storage != nullptr;
}

auto storage_ref::unsafe_get() const noexcept -> SDL_Storage*
{
  return m_storage;
}

}  // namespace cen::inline v8_0_0
