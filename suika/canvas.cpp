// -----------------------------------------------------------
// 
// canvas.
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

#include <d3d11.h>
#include <windows.h>
#include <unordered_map>
#include <wrl/client.h>

#include "d3d/info.hpp"
#include "../include/suika/point.h"
#include "../include/suika/canvas.h"

#include "d3d/swapchain.hpp"
#include "d3d/RTV.hpp"
#include "d3d/viewport.hpp"

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		std::unordered_map<canvas_id, window::id> WindowID;
	}

	ulong canvas_num = 0;

	canvas::canvas(const point<float>& size, const point<float>& top, HWND hWnd, const color& bg) {
		id = canvas_num++;
		bg_color = bg;
		d3d::swapchain::create(size, hWnd, id);
		d3d::RTV::create(id);
		d3d::viewport::create(top, size, id);
		d3d::WindowID.insert({ id, hWnd });
	}

	void canvas::clear() const {
		auto& rtv = d3d::pRTView[id];

		FLOAT color[4] = { bg_color.r / 255.0f,bg_color.g / 255.0f, bg_color.b / 255.0f, bg_color.a / 255.0f };
		d3d::pContext->ClearRenderTargetView(rtv.Get(), color);
	}

	void canvas::set() const {
		auto& rtv = d3d::pRTView[id];
		auto& vp = d3d::ViewPort[id];

		d3d::pContext->OMSetRenderTargets(1u, rtv.GetAddressOf(), nullptr);
		d3d::pContext->RSSetViewports(1u, &vp);
	}

	void canvas::present(bool vsync) const {
		auto& sw = d3d::pSwapChain[id];

		sw->Present(vsync ? 1 : 0, 0);
	}

	std::shared_ptr<canvas> make_canvas(const point<float>& size, const point<float>& top, HWND hWnd, const color& fillcolor) {
		return std::make_shared<canvas>(size, top, hWnd, fillcolor);
	}
}