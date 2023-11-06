#pragma once
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
			extern Microsoft::WRL::ComPtr<ID3D11Buffer> g_vertexBuffer;
			extern Microsoft::WRL::ComPtr<ID3D11Buffer> g_instanceMatrix;
			//extern std::vector<DirectX::XMMATRIX> instance_matrix;
			extern std::vector<matrix4x4<float>> instance_matrix;
			extern UINT offset;
			extern UINT offset_ins[2];
			extern uint stride_ins[2];
			extern std::any now_vertex;
			enum class ins_type {
				rect,
				circle,
				triangle,
				texture,
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
			
			

			/// <param name="origine">ピクセル</param>
			/// <param name="translate">ピクセル</param>
			/// <param name="rotate">ラジアン</param>
			/// <param name="extend">倍率</param>
			matrix4x4<float> calc_matrix(const suika::vector3<float>& origine, const suika::vector3<float>& translate, const suika::vector3<float>& rotate, const suika::vector3<float>& extend);

			void add_index(const suika::vector3<float>& origine, const suika::vector3<float>& translate, const suika::vector3<float>& rotate, const suika::vector3<float>& extend);
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
			/*
			MEMO
			set_vertex,set_index,set
			set_cbuffer,update_cbuffer
			*/
		}
	}
}