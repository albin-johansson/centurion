#pragma once
#include <SDL_stdinc.h>
#include <SDL_video.h>
#include <memory>
#include <string>
#include "ctn_color.h"
#include "ctn_dimensioned.h"
#include "ctn_drawable.h"
#include "ctn_font.h"
#include "ctn_point.h"
#include "ctn_rectangle.h"
#include "ctn_renderer.h"

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
class Window : public centurion::geo::IDimensioned {
 private:
  SDL_Window* sdlWindow;
  Renderer_uptr renderer;
  IDrawable_sptr drawable = nullptr;
  const int width;
  const int height;

  void CheckWindowDimensions(int width, int height);

 public:
  /**
  \param title - the title of the sdlWindow.
  \param width - the desired width of the sdlWindow.
  \param height - the desired height of the sdlWindow.
  */
  Window(const std::string& title, int width, int height);

  ~Window();

  /*
  \brief Makes this sdlWindow visible.
  \since 1.0.0
  */
  void Show();

  /*
  \brief Makes this sdlWindow invisible.
  \since 1.0.0
  */
  void Hide();

  /**
  \brief Applies any previous rendering operations to this sdlWindow. If the
  IDrawable instance has been set, using the SetDrawable()-method, then it will
  be called by this method.
  \since 1.0.0
  */
  void ApplyRendering();

  /**
  \brief Clears the rendering area of this sdlWindow.
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
  void Render(Image& texture, int x, int y, int w, int h);

  /**
  \brief Renders a texture to the rendering target.
  \param texture - the texture that will be rendered.
  \param rect - the Rectangle that provides the dimensions for the rendered
  image.
  \since 1.0.0
  */
  void Render(Image& texture, const centurion::geo::Rectangle rect);

  /**
  \brief Renders a texture to the rendering target.
  \param texture - the texture that will be rendered.
  \param x - the desired x-coordinate.
  \param y - the desired y-coordinate.
  \since 1.0.0
  */
  void Render(Image& texture, int x, int y);

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
  \brief Assigns the IDrawable that will be invoked whenever the
  ApplyRendering() method is called. \param drawable - a pointer to the
  IDrawable instance that will be used. \since 1.0.0
  */
  void SetDrawable(const IDrawable_sptr drawable);

  /**
  \brief Sets whether or not this sdlWindow is resizable.
  \param resizable - true if the sdlWindow is resizable, false otherwise.
  \since 1.0.0
  */
  void SetResizable(bool resizable);

  /**
  \brief Assigns whether or not this sdlWindow is in fullscreen mode.
  \param fullscreen - true if the sdlWindow will be a fullscreen sdlWindow,
  false otherwise. \since 2.0.0
  */
  void SetFullscreen(bool fullscreen);

  /**
  \brief Assigns whether or not this sdlWindow is bordered.
  \param bordered - true if the sdlWindow should be bordered, false otherwise.
  \since 2.0.0
  */
  void SetBordered(bool bordered);

  /**
  \brief Sets the sdlWindow icon.
  \param icon - the texture that will be used as the sdlWindow icon.
  \since 2.0.0
  */
  void SetWindowIcon(Texture_sptr icon);

  /**
  \brief Sets the location of this sdlWindow.
  \param x - the x-coordinate of the sdlWindow.
  \param y - the y-coordinate of the sdlWindow.
  \since 2.0.0
  */
  void SetLocation(int x, int y);

  /**
  \brief Sets the maximum size of this sdlWindow.
  \param width - the maximum width of this sdlWindow.
  \param height - the maximum height of this sdlWindow.
  \since 2.0.0
  */
  void SetMaximumSize(int width, int height);

  /**
  \brief Sets the minimum size of this sdlWindow.
  \param width - the minimum width of this sdlWindow.
  \param height - the minimum height of this sdlWindow.
  \since 2.0.0
  */
  void SetMinimumSize(int width, int height);

  /**
  \brief Sets the title text of this sdlWindow.
  \param title - the new title of the sdlWindow.
  \since 2.0.0
  */
  void SetTitle(std::string title);

  /**
  \brief Sets the size of this sdlWindow.
  \param width - the new width of this sdlWindow.
  \param height - the new height of this sdlWindow.
  \since 2.0.0
  */
  void SetSize(int width, int height);

  /**
  \brief Assigns the currently active font.
  \param font - a pointer to the font that will be used.
  \since 1.0.0
  */
  void SetFont(const Font_sptr font);

  /**
  \brief Assigns the active color.
  \param color - the color that will be used.
  \since 1.0.0
  */
  void SetColor(Color color);

  /**
  \brief Assigns a Image instance as the rendering target.
  \param texture - the texture that will be the new rendering target, nullptr
  resets the rendering target.
  \since 1.2.0
  */
  void SetRenderTarget(Texture_sptr texture);

  /**
  \brief Returns a pointer to the internal representation of this window.
  \since 2.0.0
  */
  inline SDL_Window* GetSDLVersion() noexcept { return sdlWindow; }

  /**
  \brief Returns the width of this sdlWindow.
  \since 1.0.0
  */
  inline int GetWidth() const noexcept override { return width; };

  /**
  \brief Returns the height of this sdlWindow.
  \since 1.0.0
  */
  inline int GetHeight() const noexcept override { return height; };

  /**
  \brief Creates and returns a Image that visually represents the supplied
  string. This method provides a more efficient way to render strings than the
  RenderString()-method.
  \param str - the string that the texture will represent.
  \since 1.0.0
  */
  Texture_sptr CreateTextureFromString(const std::string& str) const;

  /**
  \brief Creates and returns a Image found at the supplied path.
  \param path - the path of the image in the file system.
  \since 1.0.0
  */
  Texture_sptr CreateTexture(const std::string& path) const;

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
  \param src - the source rectangle, specifies the bounds of the subtexture in
  relation to the base texture.
  \param width - the width of the created texture.
  \param height - the height of the created texture.
  \since 1.2.0
  */
  Texture_sptr CreateSubtexture(Texture_sptr base,
                                centurion::geo::Rectangle src, int width,
                                int height);

  /**
  \brief Returns a shared pointer that points to a Window instance.
  \param title - the title of the sdlWindow.
  \param width - the width of the sdlWindow.
  \param height - the height of the sdlWindow.
  \param flags - flags providing information about the sdlWindow to be created,
  the flag values are specified by SDL_WindowFlags. For example,
  SDL_WindowFlags::SDL_WINDOW_FULLSCREEN.
  \since 1.1.0
  */
  static Window_sptr CreateShared(const std::string& title, int width,
                                  int height);

  /**
  \brief Returns a unique pointer that points to a Window instance.
  \param title - the title of the sdlWindow.
  \param width - the width of the sdlWindow.
  \param height - the height of the sdlWindow.
  \param flags - flags providing information about the sdlWindow to be created,
  the flag values are specified by SDL_WindowFlags. For example,
  SDL_WindowFlags::SDL_WINDOW_FULLSCREEN.
  \since 1.1.0
  */
  static Window_uptr CreateUnique(const std::string& title, int width,
                                  int height);

  /**
  \brief Returns a weak pointer that points to a Window instance.
  \param title - the title of the sdlWindow.
  \param width - the width of the sdlWindow.
  \param height - the height of the sdlWindow.
  \param flags - flags providing information about the sdlWindow to be created,
  the flag values are specified by SDL_WindowFlags. For example,
  SDL_WindowFlags::SDL_WINDOW_FULLSCREEN.
  \since 1.1.0
  */
  static Window_wptr CreateWeak(const std::string& title, int width,
                                int height);
};

}  // namespace visuals
}  // namespace centurion