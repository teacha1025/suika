// -----------------------------------------------------------
// 
// d3d11 viewport.
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
#include "../../include/suika/point.h"
#include "info.hpp"

namespace suika {
	namespace d3d {
		std::unordered_map<canvas_id, D3D11_VIEWPORT> ViewPort;
		namespace viewport {
			bool create(const point<float>& top, const point<float>& size, canvas_id id) {
				ViewPort.insert({ id, D3D11_VIEWPORT{.TopLeftX = top.x, .TopLeftY = top.y, .Width = size.x,.Height = size.y, .MinDepth = 0.0f, .MaxDepth = 1.0f } });
				log_d3d.info("Create Viewport");
				return true;
			}
		}
	}
};
