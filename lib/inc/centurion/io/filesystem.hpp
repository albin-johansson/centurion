// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

#include <optional>

#include <SDL3/SDL.h>

#include "centurion/core/error.hpp"
#include "centurion/core/memory.hpp"

namespace cen::inline v8_0_0 {

struct glob_directory_result final
{
  unique_sdl_ptr<char*> paths;
  int count;
};

// SDL_CreateDirectory
auto create_directory(const char* path) noexcept -> result;

// SDL_RemovePath
auto remove_path(const char* path) noexcept -> result;

// SDL_RenamePath
auto rename_path(const char* old_path, const char* new_path) noexcept -> result;

// SDL_GetPathInfo
[[nodiscard]]
auto path_info(const char* path) noexcept -> std::optional<SDL_PathInfo>;

// SDL_EnumerateDirectory
auto enumerate_directory(const char* path,
                         SDL_EnumerateDirectoryCallback callback,
                         void* user_data = nullptr) noexcept -> result;

// SDL_GlobDirectory
[[nodiscard]]
auto glob_directory(const char* path,
                    const char* pattern,
                    SDL_GlobFlags flags) noexcept
    -> std::optional<glob_directory_result>;

// SDL_GetUserFolder
[[nodiscard]]
auto get_folder(SDL_Folder folder) noexcept -> unique_sdl_ptr<char>;

// SDL_GetBasePath
[[nodiscard]]
auto get_base_path() noexcept -> unique_sdl_ptr<char>;

// SDL_GetPrefPath
[[nodiscard]]
auto get_pref_path(const char* org,
                   const char* app) noexcept -> unique_sdl_ptr<char>;

}  // namespace cen::inline v8_0_0
