#include <Windows.h>
#include "../include/suika/logger.h"
#include "../include/suika/window.h"
#include "../include/suika/shader.h"
#include "../include/suika/color.h"
#include "../include/suika/pallet.h"
#include "../include/suika/vertex.h"
#include "../include/suika/cbuffer.h"

#include "d3d/info.hpp"
#include "d3d/device.hpp"
#include "d3d/vs.hpp"
#include "d3d/ps.hpp"
#include "d3d/cbuffer.hpp"
#include "d3d/blend.hpp"
#include "d3d/dwrite.h"

#include "d3d/shader/shape_vs.h"
#include "d3d/shader/shape_ps.h"

extern void init();
extern int main();

namespace suika {
	//logger log;
	namespace window {
		void init();
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	try {
		suika::window::init();
		init();
		suika::log.init();
		if (!suika::d3d::init()) {
			suika::log.error("d3d error");
			return 0;
		}
		suika::add_vs("../suika/d3d/shader/shape.hlsl", "shape");
		suika::add_vs("../suika/d3d/shader/texture.hlsl", "texture");
		suika::add_ps("../suika/d3d/shader/shape.hlsl", "shape");
		suika::add_ps("../suika/d3d/shader/texture.hlsl", "texture");
		suika::set_vs("shape");
		suika::set_ps("shape");

		suika::d3d::blend::init();

		if (suika::window::create(suika::window::size(nullptr), suika::window::extends(nullptr), suika::window::background(nullptr), suika::window::title(nullptr)) == nullptr) {
			return 0;
		}

		//suika::window::background(suika::color(0, 0, 0));
		//suika::window::title("APP");

		suika::window::canvas().get()->set();

		auto res = main();

		suika::log.info("fin");
		suika::d3d::dwrite::free();
		return res;
	}
	catch(...) {
		suika::log.exception("unknown exception occured.");
		return 0;
	}
}