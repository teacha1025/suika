#include <Windows.h>
#include "../include/suika/logger.h"
#include "../include/suika/window.h"
#include "../include/suika/shader.h"
#include "../include/suika/color.h"
#include "../include/suika/palette.h"
#include "../include/suika/vertex.h"
#include "../include/suika/cbuffer.h"
#include "../include/suika/blend.h"

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
	namespace keyboard {
		void init();
	}
	namespace mouse {
		void init();
	}
	namespace d3d {
		namespace vertex {
			void init();
		}

		namespace dinput {
			bool init(HWND hWnd);
			void fin();
		}
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	auto hr_init = CoInitialize(NULL);
	try {
		suika::window::init();
		init();
		if (!suika::log.init()) {
			return 0;
		}
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
		suika::d3d::vertex::init();
		auto wid = suika::window::create(suika::window::size(nullptr), suika::window::extends(nullptr), suika::window::background(nullptr), suika::window::title(nullptr), suika::window::vsync(nullptr));
		if (wid == nullptr) {
			return 0;
		}

		

		//suika::window::background(suika::color(0, 0, 0));
		//suika::window::title("APP");

		suika::window::canvas().get()->set();

		suika::d3d::dinput::init(wid);
		suika::keyboard::init();
		suika::mouse::init();

		auto cb = suika::set_view(suika::window::size(wid));
		suika::set_cbuffer(sizeof(cb), &cb, 0);
		suika::d3d::blend::blends[suika::blend::alpha].set();

		auto res = main();

		suika::log.info("fin");
		suika::d3d::dwrite::free();
		suika::d3d::dinput::fin();

		if (SUCCEEDED(hr_init)) {
			CoUninitialize();
		}
		return res;
	}
	catch(...) {
		suika::log.exception("unknown exception occured.");
		if (SUCCEEDED(hr_init)) {
			CoUninitialize();
		}
		return 0;
	}
}