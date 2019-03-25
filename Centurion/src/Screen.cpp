#include "screen.h"
#include <SDL.h>
#include <stdexcept>
#include <windows.h>

using centurion::CTN_Screen;

int CTN_Screen::getWidth()
{
	DPI_AWARENESS_CONTEXT context = GetThreadDpiAwarenessContext();
	if (context != DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) {
		SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
	}
	return GetSystemMetrics(SM_CXSCREEN);

}

int CTN_Screen::getHeight()
{
	DPI_AWARENESS_CONTEXT context = GetThreadDpiAwarenessContext();
	if (context != DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) {
		SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
	}
	return GetSystemMetrics(SM_CYSCREEN);
}