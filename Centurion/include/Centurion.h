#pragma once

// TODO avoid new/delete, use std::unique_ptr and std::shared_ptr with std::make_unique and std::make_shared
// TODO make classes as independent as possible (don't use friend classes)
namespace centurion
{
	class Centurion; //TODO rename
	class Window;
	class Screen;

	namespace events
	{
		class Action;
		class KeyListener;
		class KeyStroke;
	}

	namespace visuals
	{
		class Graphics;
		class Image;
		class Color;
	}

	namespace geo
	{
		class Rectangle;
		class Point;
	}

	namespace tools
	{
		class BooleanConverter;
	}
}

class centurion::Centurion final {

private:
	Centurion() = delete;

public:
	~Centurion() = default;

	static void Init();

	static void Close();
};
