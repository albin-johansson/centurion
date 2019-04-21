#pragma once
#include <SDL_video.h>
#include <memory>
#include <string>
#include "color.h"
#include "drawable.h"
#include "font.h"
#include "point.h"
#include "rectangle.h"
#include "renderer.h"

namespace centurion {
namespace visuals {

class Window;
typedef std::shared_ptr<Window> Window_sptr;
typedef std::unique_ptr<Window> Window_uptr;
typedef std::weak_ptr<Window> Window_wptr;

/**
\brief The Window class represents a top-level frame.
\since 1.0.0
*/
class Window : public centurion::geo::Dimensioned {
 private:
  SDL_Window* window;
  Renderer_uptr renderer;
  Drawable_sptr drawable;
  const int width;
  const int height;

  void CheckWindowDimensions(int width, int height);

 public:
  /**
  \param title - the title of the window.
  \param width - the desired width of the window.
  \param height - the desired height of the window.
  \param flags - flags providing information about the window to be created, the
  flag values are specified by SDL_WindowFlags. For example,
  SDL_WindowFlags::SDL_WINDOW_FULLSCREEN.
  */
  Window(const std::string& title, int width, int height, uint32_t flags);

  ~Window();

  /*
  \brief Makes this window visible.
  \since 1.0.0
  */
  void Show();

  /*
  \brief Makes this window invisible.
  \since 1.0.0
  */
  void Hide();

  /**
  \brief Applies any previous rendering operations to this window. If the
  Drawable instance has been set, using the SetDrawable()-method, then it will
  be called by this method.
  \since 1.0.0
  */
  void Render();

  /**
  \brief Clears the rendering area of this window.
  \since 1.0.0
  */
  void Clear();

  /**
  \brief Renders a texture to the rendering target.
  \param texture - the texture that will be rendered.
  \param x - the desired x-coordinate.
  \param y - the desired y-coordinate.
  \param w - the desired width of the image.
  \param h - the desired height of the image.
  \since 1.0.0
  */
  void Render(centurion::visuals::Texture& texture, int x, int y, int w, int h);

  /**
  \brief Renders a texture to the rendering target.
  \param texture - the texture that will be rendered.
  \param rect - the Rectangle that provides the dimensions for the rendered
  image.
  \since 1.0.0
  */
  void Render(centurion::visuals::Texture& texture,
              const centurion::geo::Rectangle rect);

  /**
  \brief Renders a texture to the rendering target.
  \param texture - the texture that will be rendered.
  \param x - the desired x-coordinate.
  \param y - the desired y-coordinate.
  \since 1.0.0
  */
  void Render(centurion::visuals::Texture& texture, int x, int y);

  /**
  \brief Renders a filled rectangle with the currently selected color.
  \param x - the desired x-coordinate.
  \param y - the desired y-coordinate.
  \param w - the desired width of the rectangle.
  \param h - the desired height of the rectangle.
  \since 1.0.0
  */
  void RenderFilledRect(int x, int y, int w, int h);

  /**
  \brief Renders a filled rectangle with the currently selected color.
  \param rect - the rectangle that will be rendered.
  \since 1.0.0
  */
  void RenderFilledRect(centurion::geo::Rectangle rect);

  /**
  \brief Renders an outlined rectangle with the currently selected color.
  \param x - the desired x-coordinate.
  \param y - the desired y-coordinate.
  \param w - the desired width of the rectangle.
  \param h - the desired height of the rectangle.
  \since 1.0.0
  */
  void RenderOutlinedRect(int x, int y, int w, int h);

  /**
  \brief Renders an outlined rectangle with the currently selected color.
  \param rect - the rectangle that will be rendered.
  \since 1.0.0
  */
  void RenderOutlinedRect(centurion::geo::Rectangle rect);

  /**
  \brief Renders a line between two points with the currently selected color.
  \param x1 - the x-coordinate of the first point.
  \param y1 - the y-coordinate of the first point.
  \param x2 - the x-coordinate of the second point.
  \param y2 - the y-coordinate of the second point.
  \since 1.0.0
  */
  void RenderLine(int x1, int y1, int x2, int y2);

  /**
  \brief Renders a line between two points with the currently selected color.
  \param p1 - the first point.
  \param p2 - the second point.
  \since 1.0.0
  */
  void RenderLine(centurion::geo::Point p1, centurion::geo::Point p2);

  /**
  \brief Renders the supplied string using the currently selected font and
  color.
  \param str - the string that will be rendered.
  \param x - the x-coordinate of the rendered string.
  \param y - the y-coordinate of the rendered string.
  \since 1.0.0
  */
  void RenderString(const std::string& str, int x, int y);

  /**
  \brief Assigns the Drawable that will be invoked whenever the Render() method
  is called.
  \param drawable - the Drawable that will be used.
  \since 1.0.0
  */
  void SetDrawable(
      const std::shared_ptr<centurion::visuals::Drawable> drawable);

  /**
  \brief Sets whether this window is resizable or not.
  \param resizable true if the window is resizable, false otherwise.
  \since 1.0.0
  */
  void SetResizable(bool resizable);

  /**
  \brief Assigns the currently active font.
  \param font - the font that will be used.
  \since 1.0.0
  */
  void SetFont(const std::shared_ptr<centurion::visuals::Font> font);

  /**
  \brief Assigns the active color.
  \param color - the color that will be used.
  \since 1.0.0
  */
  void SetColor(centurion::visuals::Color color);

  /**
  \brief Assigns a Texture instance as the rendering target.
  \param texture - the texture that will be the new rendering target, nullptr
  resets the rendering target.
  \since 1.2.0
  */
  void SetRenderTarget(centurion::visuals::Texture_sptr texture);

  /**
  \brief Returns the width of this window.
  \since 1.0.0
  */
  inline int GetWidth() const noexcept override { return width; };

  /**
  \brief Returns the height of this window.
  \since 1.0.0
  */
  inline int GetHeight() const noexcept override { return height; };

  /**
  \brief Creates and returns a Texture that visually represents the supplied
  string. This method provides a more efficient way to render strings than the
  RenderString()-method.
  \param str - the string that the texture will represent.
  \since 1.0.0
  */
  std::shared_ptr<centurion::visuals::Texture> CreateTextureFromString(
      const std::string& str) const;

  /**
  \brief Creates and returns a Texture found at the supplied path.
  \param path - the path of the image in the file system.
  \since 1.0.0
  */
  std::shared_ptr<centurion::visuals::Texture> CreateTexture(
      const std::string& path) const;

  /**
  \brief Creates and returns an empty texture.
  \param width - the width of the created texture.
  \param height - the height of the created texture.
  \param access - the access of the created texture.
  \since 1.2.0
  */
  Texture_sptr CreateRawTexture(int width, int height,
                                SDL_TextureAccess access);

  /**
  \brief Creates and returns a subtexture from the supplied texture.
  \param base - a pointer to the texture that the subtexture will be based on.
  \param cutout - the rectangle that provides the dimensions for the subtexture.
  \param width - the final width of the subtexture.
  \param height - the final height of the subtexture.
  \param pixelFormat - the pixel format used for the subtexture.
  \since 1.2.0
  */
  Texture_sptr CreateSubtexture(Texture_sptr base,
                                centurion::geo::Rectangle cutout, int width,
                                int height, Uint32 pixelFormat);

  /**
  \brief Returns a shared pointer that points to a Window instance.
  \param title - the title of the window.
  \param width - the width of the window.
  \param height - the height of the window.
  \param flags - flags providing information about the window to be created, the
  flag values are specified by SDL_WindowFlags. For example,
  SDL_WindowFlags::SDL_WINDOW_FULLSCREEN.
  \since 1.1.0
  */
  static Window_sptr CreateShared(const std::string& title, int width,
                                  int height, uint32_t flags);

  /**
  \brief Returns a unique pointer that points to a Window instance.
  \param title - the title of the window.
  \param width - the width of the window.
  \param height - the height of the window.
  \param flags - flags providing information about the window to be created, the
  flag values are specified by SDL_WindowFlags. For example,
  SDL_WindowFlags::SDL_WINDOW_FULLSCREEN.
  \since 1.1.0
  */
  static Window_uptr CreateUnique(const std::string& title, int width,
                                  int height, uint32_t flags);

  /**
  \brief Returns a weak pointer that points to a Window instance.
  \param title - the title of the window.
  \param width - the width of the window.
  \param height - the height of the window.
  \param flags - flags providing information about the window to be created, the
  flag values are specified by SDL_WindowFlags. For example,
  SDL_WindowFlags::SDL_WINDOW_FULLSCREEN.
  \since 1.1.0
  */
  static Window_wptr CreateWeak(const std::string& title, int width, int height,
                                uint32_t flags);
};

}  // namespace visuals
}  // namespace centurion