#include <Windows.h>
#include "../include/suika/logger.h"
#include "../include/suika/window.h"

#include "d3d/device.hpp"
#include "d3d/vs.hpp"
#include "d3d/ps.hpp"

#include "d3d/shader/shape_vs.h"
#include "d3d/shader/shape_ps.h"

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
	{
		suika::d3d::vertex_shader vs;
		suika::d3d::pixel_shader ps;
		vs.create(g_vs_main, sizeof(g_vs_main), "shape");
		ps.create(g_ps_main, sizeof(g_ps_main), "shape");
	}

	if (suika::window::create({ 1280,920 }, { 128,128 }, { 1.0,1.0 }, { 255,255,255 }, "Application") == nullptr) {
		return 0;
	}
	suika::window::background(suika::color(255, 127, 0));
	suika::window::title("APP");
	auto update = [&]() {suika::window::flip(); suika::window::clear(); return suika::window::process(); };
	while (update()) {

	}
	suika::log.info("fin");
}