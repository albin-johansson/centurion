#pragma once

namespace centurion
{
	class Centurion;
	class Window;
	class Graphics;
	class Screen;
	class Image;
	class Rectangle;
	class Point;
	class Color;
	class KeyStroke;
	class IAction;
	class BooleanConverter;
}

class centurion::Centurion final {

private:
	Centurion() = delete;

public:
	~Centurion() = default;

	static void init();

	static void close();
};