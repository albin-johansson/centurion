#pragma once
#include <SDL_video.h>
#include <memory>
#include "ctn_renderer_interface.h"
#include "ctn_texture_interface.h"

namespace centurion {
namespace visuals {

class IWindow;
using IWindow_sptr = std::shared_ptr<IWindow>;
using IWindow_uptr = std::unique_ptr<IWindow>;
using IWindow_wptr = std::weak_ptr<IWindow>;

/**
\brief The IWindow class is an interface for objects that represent a top-level
window.
\since 2.0.0
*/
class IWindow {
 protected:
  IWindow() = default;

 public:
  virtual ~IWindow() = default;

  /**
  \brief Applies previous rendering operations.
  \since 2.0.0
  */
  virtual void ApplyRendering() = 0;

  /**
  \brief Clears the rendering target with the selected color.
  \since 2.0.0
  */
  virtual void RenderClear() = 0;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param x - the x-coordinate of the texture.
  \param y - the y-coordinate of the texture.
  \param w - the width of the rendered texture.
  \param h - the height of the rendered texture.
  \since 2.0.0
  */
  virtual void Render(ITexture& texture, int x, int y, int w, int h) = 0;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param src - the source rectangle.
  \param dst - the destination rectangle.
  \since 2.0.0
  */
  virtual void Render(ITexture& texture, centurion::geo::Rectangle src,
                      centurion::geo::Rectangle dst) = 0;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param x - the x-coordinate of the texture.
  \param y - the y-coordinate of the texture.
  \since 2.0.0
  */
  virtual void Render(ITexture& texture, int x, int y) = 0;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param x - the x-coordinate of the texture.
  \param y - the y-coordinate of the texture.
  \param angle - the angle of the rendered texture.
  \param flip - the value describing the flipping of the texture.
  \since 2.0.0
  */
  virtual void Render(ITexture& texture, int x, int y, int angle,
                      SDL_RendererFlip flip) = 0;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param x - the x-coordinate of the texture.
  \param y - the y-coordinate of the texture.
  \param flip - the value describing the flipping of the texture.
  \since 2.0.0
  */
  virtual void Render(ITexture& texture, int x, int y,
                      SDL_RendererFlip flip) = 0;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param x - the x-coordinate of the texture.
  \param y - the y-coordinate of the texture.
  \param angle - the angle of the rendered texture.
  \since 2.0.0
  */
  virtual void Render(ITexture& texture, int x, int y, int angle) = 0;

  /**
  \brief Renders an outlined rectangle.
  \param rect - the rectangle that will be rendered.
  \since 2.0.0
  */
  virtual void RenderOutlinedRect(centurion::geo::Rectangle rect) = 0;

  /**
  \brief Renders a filled rectangle.
  \param rect - the rectangle that will be rendered.
  \since 2.0.0
  */
  virtual void RenderFilledRect(centurion::geo::Rectangle rect) = 0;

  /**
  \brief Renders a line.
  \param p1 - the starting point of the line.
  \param p2 - the end point of the line.
  \since 2.0.0
  */
  virtual void RenderLine(centurion::geo::Point p1,
                          centurion::geo::Point p2) = 0;

  /**
  \brief Renders the supplied string, using the previously selected font.
  \param str - the string that will be rendered.
  \param x - the x-coordinate of the rendered string.
  \param y - the y-coordinate of the rendered string.
  \note If no font is available, this method has no effect.
  \since 2.0.0
  */
  virtual void RenderString(const std::string& str, int x, int y) = 0;

  /**
  \brief Assigns the rendering target for subsequent rendering operations.
  \param texture - the texture that will serve as the rendering target.
  \note If the supplied texture doesn't support being used as a rendering
  target, this method has no effect.
  \note If the supplied argument is nullptr, the rendering target is reset.
  \since 2.0.0
  */
  virtual void SetRenderTarget(ITexture_sptr texture) = 0;

  /**
  \brief Sets the font to be used when rendering text.
  \param font - a pointer to the font instance that will be used.
  \since 2.0.0
  */
  virtual void SetFont(Font_sptr font) = 0;

  /**
  \brief Sets the rendering color.
  \param color - the color that will be used.
  \since 2.0.0
  */
  virtual void SetColor(Color color) = 0;

  /**
  \brief Creates a texture of the supplied string, using the currently selected
  font.
  \param str - the string that the created texture will represent.
  \throws exception if there isn't a font to use.
  \since 1.0.0
  */
  virtual ITexture_sptr CreateTextureFromString(const std::string& str) = 0;

  /**
  \brief Creates and returns a subtexture from the supplied texture.
  \param base - a pointer to the texture that the subtexture will be based on.
  \param cutout - the rectangle that provides the cutout dimensions.
  \param w - the final width of the created texture.
  \param h - the final height of the created texture.
  \param format - the pixel format used for the subtexture.
  \throws exception if the creation of subtextures isn't supported.
  \since 1.2.0
  */
  virtual ITexture_sptr CreateSubtexture(ITexture_sptr base,
                                         centurion::geo::Rectangle cutout,
                                         int w, int h, Uint32 format) = 0;

  /**
  \brief Creates and returns an empty texture.
  \param width - the width of the created texture.
  \param height - the height of the created texture.
  \param access - the access of the created texture.
  \throws invalid_argument if the width and/or height is less than 1.
  \throws exception if the operation is unsuccessful.
  \since 1.2.0
  */
  virtual ITexture_sptr CreateEmptyTexture(int width, int height, Uint32 format,
                                           SDL_TextureAccess access) = 0;

  /**
  \brief Creates and returns a texture that may be used as a render target.
  \param width - the width of the created texture.
  \param height - the height of the created texture.
  \throws invalid_argument if the width and/or height is less than 1.
  \throws exception if the operation is unsuccessful.
  \since 2.0.0
  */
  virtual ITexture_sptr CreateRenderTarget(int width, int height) = 0;

  /**
  \brief Makes this window visible.
  \since 2.0.0
  */
  virtual void Show() = 0;

  /**
  \brief Makes this window invisible.
  \since 2.0.0
  */
  virtual void Hide() = 0;

  /**
  \brief Returns the width of this window.
  \since 2.0.0
  */
  virtual int GetWidth() const = 0;

  /**
  \brief Returns the height of this window.
  \since 2.0.0
  */
  virtual int GetHeight() const = 0;

  /**
  \brief Returns a pointer to the renderer used by this window.
  \since 2.0.0
  */
  virtual IRenderer_sptr GetRenderer() = 0;

  /**
  \brief Returns a pointer to the internal representation of this window.
  \since 2.0.0
  */
  virtual SDL_Window* GetSDLVersion() = 0;
};

}  // namespace visuals
}  // namespace centurion