// -----------------------------------------------------------
// 
// d3d11 vertex.
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
#include <array>
#include <vector>
#include <any>
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>

#include "info.hpp"
#include "../../include/suika/def.h"
#include "../../include/suika/point.h"
#include "../../include/suika/color.h"
#include "../../include/suika/type.h"
#include "../../include/suika/vertex.h"
#include "../../include/suika/matrix.h"

namespace suika {
	namespace d3d {
		namespace vertex {
			define INSTANCE_PARAM = 3;
			extern Microsoft::WRL::ComPtr<ID3D11Buffer> g_vertexBuffer;
			extern Microsoft::WRL::ComPtr<ID3D11Buffer> g_instanceMatrix;
			extern std::vector<matrix4x4<float>> instance_matrix;
			extern std::vector<matrix2x2<float>> instance_uv;
			extern UINT offset;
			extern UINT offset_ins[INSTANCE_PARAM];
			extern uint stride_ins[INSTANCE_PARAM];
			extern std::any now_vertex;

			enum class ins_type {
				line,
				rect,
				circle,
				triangle,
				texture,
				font,
				none,
			};

			void flush();

			template<class T>
			void set_vertex(std::vector<T> vertices) {
				flush();
				now_vertex = vertices;

				const uint stride = sizeof(T);
				D3D11_MAPPED_SUBRESOURCE mapped;
				const D3D11_MAP map_type = D3D11_MAP_WRITE_DISCARD;
				auto er = suika::d3d::pContext->Map(g_vertexBuffer.Get(), 0, map_type, 0, &mapped);
				if (FAILED(er)) {
					d3d::log_d3d.error("Failed to Update VertexBuffer");
					d3d::log_d3d.result(er);
					return;
				}
				if (void* const p = mapped.pData) {
					std::memcpy(p, vertices.data(), sizeof(T) * vertices.size());
				}
				suika::d3d::pContext->Unmap(g_vertexBuffer.Get(), 0);

				suika::d3d::pContext->IASetVertexBuffers(0, 1, g_vertexBuffer.GetAddressOf(), &stride, &offset);

			}


			void set_index(const std::vector<uint16>& index, D3D11_PRIMITIVE_TOPOLOGY topology);

			matrix4x4<float> calc_matrix(const suika::vector3<float>& origine, const suika::vector3<float>& translate, const suika::vector3<float>& rotate, const suika::vector3<float>& extend);

			void add_index(const suika::float3& origine, const suika::float3& translate, const suika::float3& rotate, const suika::float3& extend, const suika::float4& color, std::array<suika::float2, 2> uv);
			template<class T>
			void set_vertex_instance(const std::vector<T>& vertices) {
				if (now_vertex.has_value() && now_vertex.type() == typeid(std::vector<T>)) {
					if (std::any_cast<const std::vector<T>&>(now_vertex) == vertices) {
						return;
					}
				}
				flush();
				now_vertex = vertices;

				const D3D11_MAP map_type = D3D11_MAP_WRITE_DISCARD;
				{
					D3D11_MAPPED_SUBRESOURCE mapped;
					auto er = suika::d3d::pContext->Map(g_vertexBuffer.Get(), 0, map_type, 0, &mapped);
					if (FAILED(er)) {
						d3d::log_d3d.error("Failed to Update VertexBuffer");
						d3d::log_d3d.result(er);
						return;
					}
					if (void* const p = mapped.pData) {
						std::memcpy(p, vertices.data(), sizeof(T) * vertices.size());
					}
					suika::d3d::pContext->Unmap(g_vertexBuffer.Get(), 0);
				}
				stride_ins[0] = sizeof(T);
			}
			void set_ins_mode(ins_type type);

			void flush();

			template<class T>
			void draw(const std::vector<T>& vertices, const std::vector<uint16>& index, D3D11_PRIMITIVE_TOPOLOGY topology) {
				flush();
				set_vertex(vertices.data(), static_cast<uint>(vertices.size() * sizeof(T)), static_cast<uint>(sizeof(T)));
				set_index(index, topology);
				pContext->DrawIndexed(static_cast<UINT>(index.size()), 0, 0);
			}
		}
	}
}
