#pragma once
#include "centurion.h"

/**
\brief The Drawable class provides an interface for objects that may perform rendering with a Renderer.
*/
class centurion::visuals::Drawable {

protected:
	Drawable() = default;

public:
	virtual ~Drawable() = 0;

	/**
	\brief Performs the rendering operations specified by this Drawable.
	\param renderer - The Renderer that will be used for the rendering.
	*/
	virtual void draw(const centurion::visuals::Renderer& renderer) = 0;
};