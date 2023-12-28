// -----------------------------------------------------------
// 
// d3d11 render target view.
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

#include "../../include/suika/point.h"
#include "info.hpp"

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		std::unordered_map<canvas_id, ComPtr<ID3D11RenderTargetView>> pRTView;
		namespace RTV {
			bool create(canvas_id id) {
				ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
				auto er = pSwapChain[id]->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pBackBuffer.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to get back buffer");
					log_d3d.result(er);
					return false;
				}

				pRTView.insert({ id, {} });
				auto& rtv = (pRTView[id]);
				er = pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, rtv.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to create render target view");
					log_d3d.result(er);
					return false;
				}
				log_d3d.info("Create RenderTargetView");
				return true;
			}
		}
	}
}
