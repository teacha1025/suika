// -----------------------------------------------------------
// 
// vertex
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
#include <wrl/client.h>
#include <vector>

#include "d3d/info.hpp"
#include "../include/suika/vertex.h"
#include "d3d/vertex.h"

namespace suika {
	namespace vertex {
		vertex_2d create_2d(const float4& pos, const color_f& col, const float2& uv) {
			return vertex_2d{ .position = pos, .color = {col.r, col.g, col.b, col.a}, .uv = uv };
		}

		vertex_2d create_2d(const float2& pos, const color_f& col, const float2& uv) {
			return vertex_2d{ .position = {pos.x, pos.y, 0.0f, 1.0f}, .color = {col.r, col.g, col.b, col.a}, .uv = uv };
		}

		vertex_2d create_2d(const float3& pos, const color_f& col, const float2& uv) {
			return vertex_2d{ .position = {pos.x, pos.y, pos.z, 1.0f}, .color = {col.r, col.g, col.b, col.a}, .uv = uv };
		}

		void draw(const std::vector<vertex_2d>& vertices, const std::vector<uint16>& index, primitive_topology topology) {
			suika::d3d::vertex::set_vertex(vertices);
			suika::d3d::vertex::set_index(index, static_cast<D3D11_PRIMITIVE_TOPOLOGY>(topology));
			d3d::pContext->DrawIndexed(static_cast<UINT>(index.size()), 0, 0);
		}

	}
}
