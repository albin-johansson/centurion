#pragma once
#include <SDL.h>
#include <memory>
#include <string>
#include "centurion.h"
#include "color.h"
#include "font.h"
#include "texture_factory.h"

/**
\brief The Graphics class provides rendering functionality.
*/
class centurion::visuals::Renderer {
 private:
  SDL_Renderer* sdl_renderer;
  std::shared_ptr<centurion::Font> font;
  centurion::visuals::Color color = Color::WHITE;

  void CheckRenderDimensions(int width, int height);

  void UpdateColor();

 public:
  friend class centurion::visuals::
      TextureFactory;  // FIXME only allow the
                       // TextureFactory::CreateTexture
                       // function to be a friend

  /**
  \param renderer - a pointer to the SDL_Renderer that the Renderer will be
  based upon.
  */
  Renderer(SDL_Renderer* renderer);

  ~Renderer();

  /**
  \brief Updates the state of this Renderer. This method has to be called in
  order to apply any previous rendering operations.
  */
  void Update();

  /**
  \brief Clears the rendering target with the currently selected color.
  */
  void Clear();

  /**
  \brief Renders a texture to the rendering target.
  \param img - the texture that will be rendered.
  \param x - the desired x-coordinate.
  \param y - the desired y-coordinate.
  \param w - the desired width of the image.
  \param h - the desired height of the image.
  */
  void Render(centurion::visuals::Texture& img, int x, int y, int w, int h);

  /**
  \brief Renders a texture to the rendering target.
  \param img - the texture that will be rendered.
  \param rect - the Rectangle that provides the dimensions for the rendered
  image.
  */
  void Render(centurion::visuals::Texture& img, centurion::geo::Rectangle rect);

  /**
  \brief Renders a texture to the rendering target.
  \param img - the texture that will be rendered.
  \param x - the desired x-coordinate.
  \param y - the desired y-coordinate.
  */
  void Render(centurion::visuals::Texture& img, int x, int y);

  /**
  \brief Renders a filled rectangle with the currently selected color.
  \param x - the desired x-coordinate.
  \param y - the desired y-coordinate.
  \param w - the desired width of the rectangle.
  \param h - the desired height of the rectangle.
  */
  void RenderFilledRect(int x, int y, int w, int h);

  /**
  \brief Renders an outlined rectangle with the currently selected color.
  \param x - the desired x-coordinate.
  \param y - the desired y-coordinate.
  \param w - the desired width of the rectangle.
  \param h - the desired height of the rectangle.
  */
  void RenderOutlinedRect(int x, int y, int w, int h);

  /**
  \brief Renders a line between two points with the currently selected color.
  \param x1 - the x-coordinate of the first point.
  \param y1 - the y-coordinate of the first point.
  \param x2 - the x-coordinate of the second point.
  \param y2 - the y-coordinate of the second point.
  */
  void RenderLine(int x1, int y1, int x2, int y2);

  /**
  \brief Renders a line between two points with the currently selected color.
  \param p1 - the first point.
  \param p2 - the second point.
  */
  void RenderLine(centurion::geo::Point p1, centurion::geo::Point p2);

  // void RenderText(const std::string& text, int x, int y, int w, int h);
  // //FIXME

  /**
  \brief Assigns the currently active font.
  \param font - the font that will be used.
  */
  void SetFont(const std::shared_ptr<centurion::Font>& font);

  /**
  \brief Assigns the active color.
  \param color - the color that will be used.
  */
  void SetColor(centurion::visuals::Color color);
};