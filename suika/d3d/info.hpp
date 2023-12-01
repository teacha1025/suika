// -----------------------------------------------------------
// 
// d3d11 declaration.
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

#pragma once
#include <d3d11.h>
#include <unordered_map>
#include <wrl/client.h>

#include "../../include/suika/logger.h"
#include "../../include/suika/window.h"

namespace suika {
	namespace d3d {
		extern Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
		extern Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
		extern Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

		using canvas_id = uint;
		extern std::unordered_map<canvas_id, Microsoft::WRL::ComPtr<IDXGISwapChain>> pSwapChain;
		extern std::unordered_map<canvas_id, Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> pRTView;
		extern std::unordered_map<canvas_id, Microsoft::WRL::ComPtr<ID3D11Texture2D>> pTargetTexture;
		extern std::unordered_map<canvas_id, Microsoft::WRL::ComPtr<ID3D11SamplerState>> pSamplerState;
		extern std::unordered_map<canvas_id, D3D11_VIEWPORT> ViewPort;
		extern std::unordered_map<canvas_id, window::id> WindowID;
		extern logger log_d3d;
	}
}
