#pragma once

namespace centurion
{
	class Centurion;
	class Window;
	class Graphics;
	class Screen;
	class Image;
}

class centurion::Centurion final {

private:
	Centurion() = delete;

public:
	~Centurion() = default;

	static void init();

	static void close();
};