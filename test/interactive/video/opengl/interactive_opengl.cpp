#include <GL/glew.h>

#include "centurion.hpp"

namespace {

auto run() -> int
{
  cen::gl::set(cen::gl::attribute::context_major_version, 4);
  cen::gl::set(cen::gl::attribute::context_minor_version, 1);
  cen::gl::set(cen::gl::attribute::accelerated_visual, 1);
  cen::gl::set(cen::gl::attribute::double_buffer, 1);

  cen::window window{"Centurion OpenGL Demo",
                     cen::window::default_size(),
                     SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN};
  cen::gl::context context{window};

  window.show();

  cen::event event;
  bool running{true};

  while (running)
  {
    while (event.poll())
    {
      if (event.is<cen::quit_event>())
      {
        running = false;
        break;
      }
    }

    glClearColor(1, 0.58f, 0.95f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    cen::gl::swap(window);
  }

  window.hide();

  return 0;
}

}  // namespace

auto main(int argc, char** argv) -> int
{
  cen::library centurion;
  cen::gl::library opengl;
  return run();
}
