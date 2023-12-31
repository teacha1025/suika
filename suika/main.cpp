// -----------------------------------------------------------
// 
// suika entry point
// 
// Copyright 2023 teacha1025
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// -----------------------------------------------------------

#include <Windows.h>

#include "../include/suika/codecvt.h"
#include "../include/suika/except.h"
#include "../include/suika/string.h"
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
	namespace window {
		void init();
	}
	namespace keyboard {
		void init();
	}
	namespace mouse {
		void init();
	}
	namespace gamepad {
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

		namespace texture {
			void fin();
		}
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	
	HRESULT hr_init = S_OK;
#ifndef _DEBUG
	_set_se_translator([](unsigned int code, _EXCEPTION_POINTERS* ep) -> void {
		std::string exp = "";
		switch (code) {
			case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			case EXCEPTION_INT_DIVIDE_BY_ZERO:
				exp = "devide by zero.";
				break;
			case EXCEPTION_ACCESS_VIOLATION:
				exp = "access violation.";
				break;
			case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
				exp = "access to out of range.";
				break;
			case EXCEPTION_INT_OVERFLOW:
			case EXCEPTION_FLT_OVERFLOW:
				exp = "overflowed.";
				break;
			case EXCEPTION_FLT_UNDERFLOW:
				exp = "underflowed";
				break;
			case EXCEPTION_INVALID_HANDLE:
				exp = "invalid handle";
				break;
			case EXCEPTION_STACK_OVERFLOW:
				exp = "stack over flowed";
				break;
			case EXCEPTION_INVALID_DISPOSITION:
				exp = "invalid disposition.";
				break;
			case EXCEPTION_DATATYPE_MISALIGNMENT:
				exp = "datatype misalignmented.";
				break;
			case EXCEPTION_BREAKPOINT:
				exp = "breakpoint was found.";
				break;
			case EXCEPTION_SINGLE_STEP:
				exp = "single step.";
				break;
			case EXCEPTION_NONCONTINUABLE_EXCEPTION:
				exp = "noncontinuable exception has occurred.";
				break;
			case EXCEPTION_PRIV_INSTRUCTION:
				exp = "unapproved instruction.";
				break;
			case EXCEPTION_IN_PAGE_ERROR:
				exp = "cannot load page.";
				break;
			case EXCEPTION_ILLEGAL_INSTRUCTION:
				exp = "invalid instruction.";
				break;
			case EXCEPTION_GUARD_PAGE:
				exp = "guard page.";
				break;
			case 0xE06D7363:
				exp = "C++ Exception";
				break;
			default:
				exp = "unknown";
				break;
		}
		throw std::exception(std::format("SEH Exception code:0x{:X}  {}", code, exp).c_str());
		});
#endif
#ifndef _DEBUG
	try
#endif
	{
		hr_init = CoInitialize(NULL);
		suika::window::init();
		init();
		if (!suika::log.init()) {
			return 0;
		}
		if (!suika::d3d::init()) {
			suika::log.error("d3d error");
			return 0;
		}
#if 0
		suika::add_vs("../suika/d3d/shader/shape.hlsl",   suika::SHAPE_VERTEX);
		suika::add_vs("../suika/d3d/shader/texture.hlsl", suika::TEXTURE_VERTEX);
		suika::add_ps("../suika/d3d/shader/shape.hlsl",   suika::SHAPE_PIXEL);
		suika::add_ps("../suika/d3d/shader/texture.hlsl", suika::TEXTURE_PIXEL);
#else
		{
#include "d3d/shader/shape_vs.h"
#include "d3d/shader/shape_ps.h"
			suika::add_vs(g_vs_main, sizeof(g_vs_main), suika::SHAPE_VERTEX);
			suika::add_ps(g_ps_main, sizeof(g_ps_main), suika::SHAPE_PIXEL);
		}
		{
#include "d3d/shader/texture_vs.h"
#include "d3d/shader/texture_ps.h"
			suika::add_vs(g_vs_main, sizeof(g_vs_main), suika::TEXTURE_VERTEX);
			suika::add_ps(g_ps_main, sizeof(g_ps_main), suika::TEXTURE_PIXEL);
		}
#endif
		suika::set_vs(suika::SHAPE_VERTEX);
		suika::set_ps(suika::SHAPE_PIXEL);

		suika::d3d::blend::init();
		suika::d3d::vertex::init();
		auto wid = suika::window::create(suika::window::size(nullptr), suika::window::extends(nullptr), suika::window::background(nullptr), suika::window::title(nullptr), suika::window::vsync(nullptr));
		if (wid == nullptr) {
			return 0;
		}

		suika::window::canvas().get()->set();
		suika::d3d::dwrite::init(suika::window::canvas().get()->id);
		suika::d3d::dinput::init(wid);
		suika::keyboard::init();
		suika::mouse::init();
		suika::gamepad::init();

		auto cb = suika::set_view(suika::window::size(wid));
		suika::set_cbuffer(sizeof(cb), &cb, 0);
		suika::d3d::blend::blends[suika::blend::alpha].set();

		suika::log.info("initialized");

		// ===========================================================

		auto res = main();

		// ===========================================================

		suika::log.info("fin");
		suika::d3d::dwrite::free();
		suika::d3d::dinput::fin();
		suika::d3d::texture::fin();

		if (SUCCEEDED(hr_init)) {
			CoUninitialize();
		}
		return res;
	}
#ifndef _DEBUG
	catch (suika::exception e) {
		suika::log.exception(e.what());
		if (SUCCEEDED(hr_init)) {
			CoUninitialize();
		}
		return 0;
	}
	catch (std::exception e) {
		suika::log.exception(e.what());
		if (SUCCEEDED(hr_init)) {
			CoUninitialize();
		}
		return 0;
	}
	catch(...) {
		suika::log.exception("unknown exception occured.");
		if (SUCCEEDED(hr_init)) {
			CoUninitialize();
		}
		return 0;
	}
#endif
}
