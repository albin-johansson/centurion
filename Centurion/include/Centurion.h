#pragma once

// TODO possibly use SDL-style naming of types, such as CTN_Window.
// TODO avoid new/delete, use std::unique_ptr and std::shared_ptr with std::make_unique and std::make_shared
// TODO file names should be all lowercase. Example: this_is_a_header_file.h
// TODO make classes as independent as possible (don't use friend classes)
namespace centurion
{
	class Centurion;
	
	class CTN_Window;
	class CTN_Graphics;
	class CTN_Image;
	class CTN_Color;
	class CTN_Screen;

	//geo
	class CTN_Rectangle;
	class CTN_Point;

	//input
	class CTN_KeyListener;
	class CTN_KeyStroke;
	class CTN_Action;

	//tools
	class CTN_BooleanConverter;
}

class centurion::Centurion final {

private:
	Centurion() = delete;
	
public:
	~Centurion() = default;

	static void Init();

	static void Close();
};
