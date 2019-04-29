#pragma once
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <memory>
#include <string>
#include "ctn_color.h"
#include "ctn_font.h"
#include "ctn_point.h"
#include "ctn_rectangle.h"
#include "ctn_renderer_interface.h"
#include "ctn_texture_interface.h"

namespace centurion {
namespace visuals {

/**
\brief The Renderer class provides rendering functionality for a Window.
\since 1.0.0
*/
class Renderer final : public IRenderer {
 private:
  SDL_Renderer* sdlRenderer = nullptr;
  Font_sptr font = nullptr;
  Color color = Color::WHITE;

  SDL_Texture* CreateSDLTextureFromString(const std::string& str);

  inline bool IsValid(int width, int height) const noexcept {
    return (width > 0) && (height > 0);
  }

 public:
  /**
  \param renderer - a pointer to an SDL_Renderer that will be the internal
  representation of the renderer.
  \throws invalid_argument if the supplied pointer is null.
  */
  explicit Renderer(SDL_Renderer* renderer);

  ~Renderer();

  /**
  \brief Applies previous rendering operations.
  \since 2.0.0
  */
  void ApplyRendering() noexcept override;

  /**
  \brief Clears the rendering target with the selected color.
  \since 2.0.0
  */
  void RenderClear() noexcept override;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param x - the x-coordinate of the texture.
  \param y - the y-coordinate of the texture.
  \param w - the width of the rendered texture.
  \param h - the height of the rendered texture.
  \note if the supplied width and height is less than 1, this method has no
  effect.
  \since 2.0.0
  */
  void Render(ITexture& texture, int x, int y, int w, int h) noexcept override;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param src - the source rectangle.
  \param dst - the destination rectangle.
  \since 2.0.0
  */
  void Render(ITexture& texture, centurion::geo::Rectangle src,
              centurion::geo::Rectangle dst) noexcept override;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param x - the x-coordinate of the texture.
  \param y - the y-coordinate of the texture.
  \since 2.0.0
  */
  void Render(ITexture& texture, int x, int y) noexcept override;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param x - the x-coordinate of the texture.
  \param y - the y-coordinate of the texture.
  \param angle - the angle of the rendered texture.
  \param flip - the value describing the flipping of the texture.
  \since 2.0.0
  */
  void Render(ITexture& texture, int x, int y, int angle,
              SDL_RendererFlip flip) noexcept override;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param x - the x-coordinate of the texture.
  \param y - the y-coordinate of the texture.
  \param flip - the value describing the flipping of the texture.
  \since 2.0.0
  */
  void Render(ITexture& texture, int x, int y,
              SDL_RendererFlip flip) noexcept override;

  /**
  \brief Renders a texture.
  \param texture - the texture that will be rendered.
  \param x - the x-coordinate of the texture.
  \param y - the y-coordinate of the texture.
  \param angle - the angle of the rendered texture.
  \since 2.0.0
  */
  void Render(ITexture& texture, int x, int y, int angle) noexcept override;

  /**
  \brief Renders an outlined rectangle.
  \param rect - the rectangle that will be rendered.
  \since 2.0.0
  */
  void RenderOutlinedRect(centurion::geo::Rectangle rect) noexcept override;

  /**
  \brief Renders a filled rectangle.
  \param rect - the rectangle that will be rendered.
  \since 2.0.0
  */
  void RenderFilledRect(centurion::geo::Rectangle rect) noexcept override;

  /**
  \brief Renders a line.
  \param p1 - the starting point of the line.
  \param p2 - the end point of the line.
  \since 2.0.0
  */
  void RenderLine(centurion::geo::Point p1,
                  centurion::geo::Point p2) noexcept override;

  /**
  \brief Renders the supplied string, using the previously selected font.
  \param str - the string that will be rendered.
  \param x - the x-coordinate of the rendered string.
  \param y - the y-coordinate of the rendered string.
  \note If no font is available, this method has no effect.
  \note Avoid using this method if possible, as it's quite slow.
  \since 2.0.0
  */
  void RenderString(const std::string& str, int x, int y) override;

  /**
  \brief Assigns the rendering target for subsequent rendering operations.
  \param texture - the texture that will serve as the rendering target.
  \note If the supplied texture doesn't support being used as a rendering
  target, this method has no effect.
  \note If the supplied argument is nullptr, the rendering target is reset.
  \since 2.0.0
  */
  void SetRenderTarget(ITexture_sptr texture) noexcept override;

  /**
  \brief Sets the font to be used when rendering text.
  \param font - a pointer to the font instance that will be used.
  \since 2.0.0
  */
  void SetFont(Font_sptr font) noexcept override;

  /**
  \brief Sets the rendering color.
  \param color - the color that will be used.
  \since 2.0.0
  */
  void SetColor(Color color) noexcept override;

  /**
  \brief Creates a texture of the supplied string, using the currently selected
  font.
  \param str - the string that the created texture will represent.
  \throws exception if there isn't a font to use.
  \since 1.0.0
  */
  ITexture_sptr CreateTextureFromString(const std::string& str) override;

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
  ITexture_sptr CreateSubtexture(ITexture_sptr base,
                                 centurion::geo::Rectangle cutout, int w, int h,
                                 Uint32 format) override;

  /**
  \brief Creates and returns an empty texture.
  \param width - the width of the created texture.
  \param height - the height of the created texture.
  \param access - the access of the created texture.
  \throws invalid_argument if the width and/or height is less than 1.
  \throws exception if the operation is unsuccessful.
  \since 1.2.0
  */
  ITexture_sptr CreateEmptyTexture(int width, int height, Uint32 format,
                                   SDL_TextureAccess access) override;

  /**
  \brief Creates and returns a texture that may be used as a render target.
  \param width - the width of the created texture.
  \param height - the height of the created texture.
  \throws invalid_argument if the width and/or height is less than 1.
  \throws exception if the operation is unsuccessful.
  \since 2.0.0
  */
  ITexture_sptr CreateRenderTarget(int width, int height) override;

  /**
  \brief Returns the internal representation of this Renderer. DO NOT use the
  returned pointer to call SDL_DestroyRenderer().
  \since 1.0.0
  */
  inline SDL_Renderer* GetSDLVersion() noexcept override { return sdlRenderer; }

  /**
  \brief Returns a shared pointer to a renderer instance.
  \param renderer - a pointer to the SDL_Renderer that the renderer will be
  based on.
  \since 1.1.0
  */
  static IRenderer_sptr CreateShared(SDL_Renderer* renderer);

  /**
  \brief Returns a unique pointer to a renderer instance.
  \param renderer - a pointer to the SDL_Renderer that the renderer will be
  based on.
  \since 1.1.0
  */
  static IRenderer_uptr CreateUnique(SDL_Renderer* renderer);

  /**
  \brief Returns a weak pointer to a renderer instance.
  \param renderer - a pointer to the SDL_Renderer that the renderer will be
  based on.
  \since 1.1.0
  */
  static IRenderer_wptr CreateWeak(SDL_Renderer* renderer);
};

}  // namespace visuals
}  // namespace centurion