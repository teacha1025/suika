#include <Windows.h>
#include "../include/suika/logger.h"
#include "../include/suika/window.h"

#include "d3d/device.hpp"
#include "d3d/swapchain.hpp"
#include "d3d/RTV.hpp"

extern void init();
extern int main();

namespace suika {
	//logger log;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	suika::log.init();
	if (!suika::d3d::init()) {
		suika::log.error("d3d error");
		return 0;
	}
	if (suika::window::create({ 1280,920 }, { 128,128 }, { 1.0,1.0 }, { 255,255,255 }, "title") == nullptr) {
		return 0;
	}
	auto hwnd = suika::window::create({ 640,480 }, { 128,128 }, { 1.0,1.0 }, { 255,255,255 }, "sub");
	if (hwnd == nullptr) {
		return 0;
	}
	suika::window::background(suika::color(255, 127, 0));
	suika::window::background(suika::color(255, 255, 0), hwnd);
	auto update = [&]() {suika::window::flip(); suika::window::clear(); return suika::window::process(); };
	while (update()) {

	}
	suika::log.info("fin");
}