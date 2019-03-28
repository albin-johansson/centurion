#pragma once
#include "centurion.h"
#include "renderer.h"
#include "drawable.h"
#include "dimensioned.h"
#include <SDL_video.h>
#include <string>
#include <memory>

/**
\brief The Window class represents a top-level frame.
*/
class centurion::Window : public centurion::Dimensioned {

private:
	SDL_Window* window;
	std::unique_ptr<centurion::visuals::Renderer> renderer;
	std::shared_ptr<centurion::visuals::Drawable> drawable;
	const int width;
	const int height;

	void CheckWindowDimensions(int width, int height);

public:
	/**
	\param title - the title of the window.
	\param width - the desired width of the window.
	\param height - the desired height of the window.
	\param flags - flags providing information about the window to be created, the flag values
				   are specified by SDL_WindowFlags. For example, SDL_WindowFlags::SDL_WINDOW_FULLSCREEN.
	*/
	Window(const std::string& title, int width, int height, Uint32 flags);

	~Window();

	/*
	\brief Makes this window visible.
	*/
	void Show();

	/*
	\brief	Makes this window invisible.
	*/
	void Hide();

	/**
	\brief Renders this window.
	*/
	void Render();

	/**
	\brief Assigns the Drawable that will be invoked whenever the Render() method is called.
	\param drawable - the Drawable that will be used.
	*/
	void SetDrawable(const std::shared_ptr<centurion::visuals::Drawable> drawable);

	/**
	\brief Sets whether this window is resizable or not.
	\param resizable true if the window is resizable, false otherwise.
	*/
	void SetResizable(bool resizable);

	/**
	\brief Returns the width of this window.
	*/
	int GetWidth() const override;

	/**
	\brief Returns the height of this window.
	*/
	int GetHeight() const override;

	// TODO add listener methods
};