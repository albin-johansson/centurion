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
#include "ctn_surface.h"
#include "ctn_texture_interface.h"

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
  int windowedWidth;
  int windowedHeight;
  bool isFullscreen;

  void CheckWindowDimensions(int width, int height);

 public:
  Window();

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
  IDrawable instance has been set, using the SetDrawable()-method, then it will
  be called by this method.
  \since 1.0.0
  */
  void ApplyRendering();

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
  void Render(ITexture& texture, int x, int y, int w, int h);

  /**
  \brief Renders a texture to the rendering target.
  \param texture - the texture that will be rendered.
  \param rect - the Rectangle that provides the dimensions for the rendered
  image.
  \since 1.0.0
  */
  void Render(ITexture& texture, const centurion::geo::Rectangle rect);

  /**
  \brief Renders a texture to the rendering target.
  \param texture - the texture that will be rendered.
  \param x - the desired x-coordinate.
  \param y - the desired y-coordinate.
  \since 1.0.0
  */
  void Render(ITexture& texture, int x, int y);

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
  ApplyRendering() method is called.
  \param drawable - a pointer to the IDrawable instance that will be used.
  \since 1.0.0
  */
  void SetDrawable(const IDrawable_sptr drawable);

  /**
  \brief Sets whether or not this window is resizable.
  \param resizable - true if the window is resizable, false otherwise.
  \since 1.0.0
  */
  void SetResizable(bool resizable);

  /**
  \brief Assigns whether or not this window is in fullscreen mode.
  \param fullscreen - true if the window will be a fullscreen window,
  false otherwise.
  \since 2.0.0
  */
  void SetFullscreen(bool fullscreen);

  /**
  \brief Assigns whether or not this window is bordered.
  \param bordered - true if the window should be bordered, false otherwise.
  \since 2.0.0
  */
  void SetBordered(bool bordered);

  /**
  \brief Sets the window icon.
  \param icon - the surface that will be used as the window icon.
  \since 2.0.0
  */
  void SetWindowIcon(Surface_sptr icon);

  /**
  \brief Sets the location of this window.
  \param x - the x-coordinate of the window.
  \param y - the y-coordinate of the window.
  \since 2.0.0
  */
  void SetLocation(int x, int y);

  /**
  \brief Sets the maximum size of this window.
  \param width - the maximum width of this window.
  \param height - the maximum height of this window.
  \since 2.0.0
  */
  void SetMaximumSize(int width, int height);

  /**
  \brief Sets the minimum size of this window.
  \param width - the minimum width of this window.
  \param height - the minimum height of this window.
  \since 2.0.0
  */
  void SetMinimumSize(int width, int height);

  /**
  \brief Sets the title text of this window.
  \param title - the new title of the window.
  \since 2.0.0
  */
  void SetTitle(std::string title);

  /**
  \brief Sets the size of this window, when in windowed mode.
  \param width - the new width of this window.
  \param height - the new height of this window.
  \since 2.0.0
  */
  void SetWindowedSize(int width, int height);

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
  \brief Assigns a Texture instance as the rendering target.
  \param texture - the texture that will be the new rendering target, nullptr
  resets the rendering target.
  \since 1.2.0
  */
  void SetRenderTarget(ITexture_sptr texture) noexcept;

  /**
  \brief Returns a pointer to the internal representation of this window.
  \since 2.0.0
  */
  inline SDL_Window* GetSDLVersion() noexcept { return sdlWindow; }

  /**
  \brief Returns the width of this window.
  \since 1.0.0
  */
  int GetWidth() const noexcept override;

  /**
  \brief Returns the height of this window.
  \since 1.0.0
  */
  int GetHeight() const noexcept override;

  /**
  \brief Creates and returns a Texture that visually represents the supplied
  string. This method provides a more efficient way to render strings than the
  RenderString()-method.
  \param str - the string that the texture will represent.
  \since 1.0.0
  */
  ITexture_sptr CreateTextureFromString(const std::string& str) const;

  /**
  \brief Creates and returns a Texture found at the supplied path.
  \param path - the path of the image in the file system.
  \since 1.0.0
  */
  ITexture_sptr CreateTexture(const std::string& path) const;

  /**
  \brief Creates and returns an empty texture.
  \param width - the width of the created texture.
  \param height - the height of the created texture.
  \param access - the access of the created texture.
  \since 1.2.0
  */
  ITexture_sptr CreateRawTexture(int width, int height,
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
  ITexture_sptr CreateSubtexture(ITexture_sptr base,
                                 centurion::geo::Rectangle src, int width,
                                 int height);

  /**
  \brief Returns a shared pointer that points to a Window instance.
  \since 1.1.0
  */
  static Window_sptr CreateShared();

  /**
  \brief Returns a unique pointer that points to a Window instance.
  \since 1.1.0
  */
  static Window_uptr CreateUnique();

  /**
  \brief Returns a weak pointer that points to a Window instance.
  \since 1.1.0
  */
  static Window_wptr CreateWeak();
};

}  // namespace visuals
}  // namespace centurion