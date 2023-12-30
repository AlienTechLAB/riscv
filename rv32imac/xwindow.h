#ifndef XWINDOW_H
#define XWINDOW_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdint.h>
#include "types.h"
#include "memory.h"

using namespace riscv;

class xwindow
{
public:
	xwindow(uint32_t width, uint32_t height, memory& memory, const uint64_t videoAddr);
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

	memory& iMemory;
	uint64_t iVideoAddr{ 0 };
	uint32_t iWidth{ 0 };
	uint32_t iHeight{ 0 };
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