#pragma once

// TODO avoid new/delete, use std::unique_ptr and std::shared_ptr with std::make_unique and std::make_shared
// TODO make classes as independent as possible (don't use friend classes)
// TODO fix duplicated functionality
namespace centurion
{
	class Centurion; //TODO rename
	class Window;
	class Screen;
	class Font;

	class Positionable;
	class Dimensioned;

	namespace events
	{
		class Action;
		class KeyListener;
		class KeyStroke;
	}

	namespace visuals
	{
		class Renderer;
		class Texture;
		class TextureFactory;

		class Color;
		class Drawable;
	}

	namespace geo
	{
		class Rectangle;
		class Point;
	}

	namespace tools
	{
		class BooleanConverter;
		class NullChecker;
	}
}

class centurion::Centurion final {

private:
	static bool initialized;

	Centurion() = delete;

public:
	~Centurion() = default;

	static void Init();

	static void Close();

	static bool IsInitialized();
};
