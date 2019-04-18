#pragma once
#include <memory>
#include "renderer.h"

namespace centurion {
namespace visuals {

/**
\brief The Drawable class provides an interface for objects that may perform
rendering with a Renderer.
\since 1.0.0
*/
class Drawable {
 protected:
  Drawable() = default;

 public:
  virtual ~Drawable() = default;

  /**
  \brief Performs the rendering operations specified by this Drawable.
  \param renderer - The Renderer that will be used for the rendering.
  \since 1.0.0
  */
  virtual void Draw(centurion::visuals::Renderer& renderer) = 0;
};

typedef std::shared_ptr<Drawable> Drawable_sptr;
typedef std::unique_ptr<Drawable> Drawable_uptr;
typedef std::weak_ptr<Drawable> Drawable_wptr;

}  // namespace visuals
}  // namespace centurion