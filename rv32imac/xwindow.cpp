#include <chrono>
#include <unistd.h>
#include "xwindow.h"

xwindow::xwindow(uint32_t width, uint32_t height, memory& memory, const uint64_t videoAddr)
	: iWidth(width), iHeight(height), iMemory(memory), iVideoAddr(videoAddr)
{
}

err_t xwindow::open()
{
	iDisplay = XOpenDisplay(nullptr);
	if (iDisplay == nullptr) {
		fprintf(stderr, "XOpenDisplay failed.\n");
		return err_t::error;
	}
	iScreenID = DefaultScreen(iDisplay);
	iWindow = XCreateSimpleWindow(iDisplay, RootWindow(iDisplay, iScreenID), 0, 0, iWidth, iHeight, 0, 0, 0);
    XStoreName(iDisplay, iWindow, "RISC-V Virtual Machine");
	XSizeHints hints;
    hints.flags = PMinSize | PMaxSize;
    hints.min_width = hints.max_width = iWidth;
    hints.min_height = hints.max_height = iHeight;
    XSetWMNormalHints(iDisplay, iWindow, &hints);
	XSelectInput(iDisplay, iWindow, StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
	XMapWindow(iDisplay, iWindow);
	iGContext = XCreateGC(iDisplay, iWindow, 0, nullptr);
	return err_t::ok;
}

err_t xwindow::loop()
{
	while (iRunning) {
		const auto start = std::chrono::high_resolution_clock::now();
		processEvents();
		updateScreen();
		const auto stop = std::chrono::high_resolution_clock::now();
  		const std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    	const uint32_t duration_us = static_cast<uint32_t>(duration.count());
		usleep(33333 - duration_us);
	}
	return err_t::ok;
}

void xwindow::close()
{
	XDestroyWindow(iDisplay, iWindow);
	XCloseDisplay(iDisplay);
}

// TODO - to be removed?
void xwindow::fill(uint32_t color)
{
	std::lock_guard<memory> lock(iMemory);
	for (int y = 0; y < iHeight; y++) {
		for (int x = 0; x < iWidth; x++) {
			uint32_t* pVideo = (uint32_t*)(iMemory.data() + iVideoAddr + ((y * iWidth + x) * 4));
			*pVideo = color;
		}
	}
}

void xwindow::processEvents()
{
	const uint32_t eventsNo = XPending(iDisplay);
	for (uint32_t i = 0; i < eventsNo; i++) {
		XEvent event;
		XNextEvent(iDisplay, &event);
		switch (event.type) {
			case Expose:
				updateScreen();
				break;
			case KeyPress:
				onKeyPress(event);
				break;
			case KeyRelease:
				onKeyRelease(event);
				break;
			case ButtonPress:
				onMouseButtonPress(event);
				break;
			case ButtonRelease:
				onMouseButtonRelease(event);
				break;
			case MotionNotify:
				onMouseMove(event);
				break;
		}
	}
}

void xwindow::updateScreen()
{
	std::lock_guard<memory> lock(iMemory);
	char* videoAddr = (char*)(iMemory.data() + iVideoAddr);
	XImage* image = XCreateImage(iDisplay, DefaultVisual(iDisplay, iScreenID), 24, ZPixmap, 0, videoAddr, iWidth, iHeight, 32, 0);
	XPutImage(iDisplay, iWindow, iGContext, image, 0, 0, 0, 0, iWidth, iHeight);
	XFlush(iDisplay);
}

void xwindow::onKeyPress(XEvent& event)
{
	const uint32_t index = event.xkey.keycode >> 5;
	const uint32_t bitNum = event.xkey.keycode & 0x1F;
	iKeyboard[index] |= (1 << bitNum);
}

void xwindow::onKeyRelease(XEvent& event)
{
	const uint32_t index = event.xkey.keycode >> 5;
	const uint32_t bitNum = event.xkey.keycode & 0x1F;
	iKeyboard[index] &= ~(1 << bitNum);
}

void xwindow::onMouseButtonPress(XEvent& event)
{
	iMouseButtons |= (1 << event.xbutton.button);
	iMouseX = event.xbutton.x;
	iMouseY = event.xbutton.y;
}

void xwindow::onMouseButtonRelease(XEvent& event)
{
	iMouseButtons &= ~(1 << event.xbutton.button);
	iMouseX = event.xbutton.x;
	iMouseY = event.xbutton.y;
}

void xwindow::onMouseMove(XEvent& event)
{
	int rx, ry, wx, wy;
	Window root_window, child_window;
	unsigned int mask;
	XQueryPointer(iDisplay, iWindow, &root_window, &child_window, &rx, &ry, &wx, &wy, &mask);
	iMouseX = wx;
	iMouseY = wy;
}