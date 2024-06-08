// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/io/filesystem.hpp"

namespace cen::inline v8_0_0 {

auto create_directory(const char* const path) noexcept -> result
{
  const auto ec = SDL_CreateDirectory(path);

  if (ec != 0) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto enumerate_directory(const char* const path,
                         SDL_EnumerateDirectoryCallback callback,
                         void* const user_data) noexcept -> result
{
  const auto ec = SDL_EnumerateDirectory(path, callback, user_data);

  if (ec != 0) {
    emit_sdl_error();
    return result::failure;
  }

  return result::success;
}

auto glob_directory(const char* const path,
                    const char* const pattern,
                    const SDL_GlobFlags flags) noexcept
    -> std::optional<glob_directory_result>
{
  glob_directory_result result {};
  result.paths.reset(SDL_GlobDirectory(path, pattern, flags, &result.count));

  if (!result.paths) {
    emit_sdl_error();
    return std::nullopt;
  }

  return result;
}

auto get_folder(const SDL_Folder folder) noexcept -> unique_sdl_ptr<char>
{
  unique_sdl_ptr<char> path {};
  path.reset(SDL_GetUserFolder(folder));

  if (!path) {
    emit_sdl_error();
  }

  return path;
}

auto get_base_path() noexcept -> unique_sdl_ptr<char>
{
  unique_sdl_ptr<char> path {};
  path.reset(SDL_GetBasePath());

  if (!path) {
    emit_sdl_error();
  }

  return path;
}

auto get_pref_path(const char* const org,
                   const char* const app) noexcept -> unique_sdl_ptr<char>
{
  unique_sdl_ptr<char> path {};
  path.reset(SDL_GetPrefPath(org, app));

  if (!path) {
    emit_sdl_error();
  }

  return path;
}

}  // namespace cen::inline v8_0_0
