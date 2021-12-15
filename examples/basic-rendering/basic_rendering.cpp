#include <centurion.hpp>

int main(int, char**)
{
  const cen::SDLLibrary sdl;
  const cen::IMGLibrary img;
  const cen::TTFLibrary ttf;

  // Create our window and renderer
  auto [window, renderer] = cen::make_window_and_renderer();

  // Here we assume the existence of an image and font
  const cen::Texture image{renderer, RESOURCE_DIR "panda.png"};
  const cen::Font font{RESOURCE_DIR "daniel.ttf", 36};
  window.show();

  // Render a string to a texture, which in turn can be rendered to our render target
  cen::Texture text{renderer, font.RenderBlendedUTF8("Hello world!", cen::colors::white)};

  // Clear our render target with an arbitrary color
  renderer.ClearWith(cen::colors::light_coral);

  // Draw a filled circle
  renderer.SetColor(cen::colors::red);
  renderer.FillCircle(cen::FPoint{150, 150}, 75);

  // Draw an outlined circle
  renderer.SetColor(cen::colors::cyan);
  renderer.DrawCircle(cen::FPoint{350, 275}, 50);

  // Draw a filled rectangle
  renderer.SetColor(cen::colors::lime_green);
  renderer.FillRect(cen::FRect{25.0, 500.0, 125.0, 75.0});

  // Draw an outlined rectangle
  renderer.SetColor(cen::colors::khaki);
  renderer.DrawRect(cen::FRect{550.0, 50.0, 140.0, 60.0});

  // Draw a line between two points
  renderer.SetColor(cen::colors::forest_green);
  renderer.DrawLine(cen::FPoint{240.0, 340.0}, cen::FPoint{360.0, 460.0});

  // Render the image along with the text (also in the form of a texture)
  renderer.Render(image, cen::FPoint{600.0, 450.0});
  renderer.Render(text, cen::FPoint{450.0, 230.0});

  // Apply our draw calls to the render target (the window)
  renderer.Present();

  using namespace cen::literals;  // For _ms literal
  cen::Thread::Sleep(2000_ms);    // Wait for 2 seconds so that we can see the result
  window.hide();

  return 0;
}