#include <GL/glew.h>

#include "centurion.hpp"

namespace {

auto run() -> int
{
  cen::gl::set_attribute(cen::gl_attribute::context_major_version, 4);
  cen::gl::set_attribute(cen::gl_attribute::context_minor_version, 1);
  cen::gl::set_attribute(cen::gl_attribute::accelerated_visual, 1);
  cen::gl::set_attribute(cen::gl_attribute::double_buffer, 1);

  cen::window window{"Centurion OpenGL Demo",
                     {800, 600},
                     SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN};
  cen::gl::context context{window};

  window.show();

  glClearColor(255, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  cen::gl::swap(window);

  using namespace cen::literals;
  cen::thread::sleep(2_s);

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
