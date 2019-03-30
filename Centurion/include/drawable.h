#pragma once
#include "renderer.h"

namespace centurion {
namespace visuals {

/**
\brief The Drawable class provides an interface for objects that may perform
rendering with a Renderer.
*/
class Drawable {
 protected:
  Drawable() = default;

 public:
  virtual ~Drawable() = default;

  /**
  \brief Performs the rendering operations specified by this Drawable.
  \param renderer - The Renderer that will be used for the rendering.
  */
  virtual void Draw(centurion::visuals::Renderer& renderer) = 0;
};

}  // namespace visuals
}  // namespace centurion