// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include <cinttypes>
#include <cstdio>

#include <SDL3/SDL.h>

#include "centurion/core/init.hpp"
#include "centurion/io/iostream.hpp"

namespace demo {

[[nodiscard]]
auto get_status_name(const SDL_IOStatus status) noexcept -> const char*
{
  switch (status) {
    case SDL_IO_STATUS_READY:     return "READY";
    case SDL_IO_STATUS_ERROR:     return "ERROR";
    case SDL_IO_STATUS_EOF:       return "EOF";
    case SDL_IO_STATUS_NOT_READY: return "NOT_READY";
    case SDL_IO_STATUS_READONLY:  return "READONLY";
    case SDL_IO_STATUS_WRITEONLY: return "WRITEONLY";
    default:                      return "?";
  }
}

void show_stream_info(cen::iostream_ref stream) noexcept
{
  const auto size = stream.size().value();
  const auto offset = stream.tell().value();

  SDL_Log("  stream.status() == %s", get_status_name(stream.status()));
  SDL_Log("  stream.size() == %" PRId64, size);
  SDL_Log("  stream.tell() == %" PRId64, offset);

  char buffer[128] {};
  stream.read(buffer, sizeof buffer);
  stream.seek(cen::seek_mode::start, offset);

  SDL_Log("  stream data after cursor == \"%s\"", buffer);
}

}  // namespace demo

auto main(int, char*[]) -> int
{
  const auto sdl [[maybe_unused]] = cen::sdl_library::init(0).value();

  SDL_SetLogOutputFunction(
      [](void*, int, SDL_LogPriority, const char* msg) {
        std::printf("%s\n", msg);
      },
      nullptr);

  auto stream = cen::iostream::from_dynamic_memory().value();

  SDL_Log("==> Created stream from dynamic memory");
  SDL_Log("  stream.get_properties() == %i", stream.get_properties().value());
  demo::show_stream_info(stream);

  {
    const char data[] = "Hello, iostream!";
    const auto written_bytes = stream.write(data, sizeof data);
    SDL_Log("==> Wrote %zu bytes", written_bytes);
  }

  demo::show_stream_info(stream);

  {
    const auto cursor_pos = stream.seek(cen::seek_mode::start).value();
    SDL_Log("==> Reset stream cursor to %" PRId64, cursor_pos);
  }

  demo::show_stream_info(stream);

  {
    char read_buffer[64] {};
    const auto read_bytes = stream.read(read_buffer, sizeof read_buffer);
    SDL_Log("==> Read %zu bytes", read_bytes);
  }

  demo::show_stream_info(stream);

  return 0;
}
