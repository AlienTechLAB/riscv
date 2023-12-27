#ifndef XWINDOW_H
#define XWINDOW_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdint.h>
#include "types.h"

using namespace riscv;

class xwindow
{
public:
	xwindow(uint32_t width, uint32_t height, uint8_t* video);
	err_t open();
	void close();
	err_t loop();
	void fill(uint32_t color);

private:
	void processEvents();
	void updateScreen();
	void onKeyPress(XEvent& event);
	void onKeyRelease(XEvent& event);
	void onMouseButtonPress(XEvent& event);
	void onMouseButtonRelease(XEvent& event);
	void onMouseMove(XEvent& event);

	uint32_t iWidth{ 0 };
	uint32_t iHeight{ 0 };
	uint8_t* pVideo{ nullptr };
	Display* iDisplay{ nullptr };
	int iScreenID{ 0 };
	Window iWindow;
	GC iGContext;

	uint32_t iMouseX{ 0 };
	uint32_t iMouseY{ 0 };
	uint32_t iMouseButtons{ 0 };
	uint32_t iKeyboard[4]{ 0, 0, 0, 0 };
	bool iRunning{ true };
};


#endif	// XWINDOW_H