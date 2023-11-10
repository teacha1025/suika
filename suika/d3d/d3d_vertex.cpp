#include <d3d11.h>
#include <DirectXMath.h>
#include <windows.h>
#include <wrl/client.h>
#include <vector>
#include "info.hpp"
#include "vertex.h"
#include "../../include/suika/matrix.h"
#include "../../include/suika/vertex.h"
#include "../../include/suika/type.h"

namespace suika {
	namespace d3d {
		namespace vertex {
			std::vector<uint16> index;
			std::vector<matrix4x4<float>> instance_matrix;

			std::any now_vertex;
			ins_type now_type= ins_type::none;

			D3D11_BUFFER_DESC bufferDesc;
			D3D11_SUBRESOURCE_DATA initData;
			UINT offset = 0;
			UINT offset_ins[2] = { 0,0 };
			uint stride_ins[2] = { 0,0 };
			Microsoft::WRL::ComPtr<ID3D11Buffer> g_indexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer> g_vertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer> g_instanceMatrix;

			template<concepts::numbers T>
			matrix<T> to_matrix(DirectX::XMMATRIX m) {
				matrix<T> ret(4, 4, 0);
				for (int i = 0; i < 4; i++) {
					ret.at(i, 0) = m.r[i].m128_f32[0];
					ret.at(i, 1) = m.r[i].m128_f32[1];
					ret.at(i, 2) = m.r[i].m128_f32[2];
					ret.at(i, 3) = m.r[i].m128_f32[3];
				}
				return ret;
			}
			template<concepts::numbers T>
			matrix4x4<T> to_matrix4x4(DirectX::XMMATRIX m) {
				matrix4x4<T> ret;
				ret.at(0, 0) = m.r[0].m128_f32[0];
				ret.at(0, 1) = m.r[0].m128_f32[1];
				ret.at(0, 2) = m.r[0].m128_f32[2];
				ret.at(0, 3) = m.r[0].m128_f32[3];

				ret.at(1, 0) = m.r[1].m128_f32[0];
				ret.at(1, 1) = m.r[1].m128_f32[1];
				ret.at(1, 2) = m.r[1].m128_f32[2];
				ret.at(1, 3) = m.r[1].m128_f32[3];

				ret.at(2, 0) = m.r[2].m128_f32[0];
				ret.at(2, 1) = m.r[2].m128_f32[1];
				ret.at(2, 2) = m.r[2].m128_f32[2];
				ret.at(2, 3) = m.r[2].m128_f32[3];

				ret.at(3, 0) = m.r[3].m128_f32[0];
				ret.at(3, 1) = m.r[3].m128_f32[1];
				ret.at(3, 2) = m.r[3].m128_f32[2];
				ret.at(3, 3) = m.r[3].m128_f32[3];
				return ret;
			}
			template<concepts::numbers T>
			DirectX::XMMATRIX to_matrix(matrix<T> m) {
				DirectX::XMMATRIX ret = {};
				for (int i = 0; i < 4; i++) {
					ret.r[i].m128_f32[0] = m.at(i, 0);
					ret.r[i].m128_f32[1] = m.at(i, 1);
					ret.r[i].m128_f32[2] = m.at(i, 2);
					ret.r[i].m128_f32[3] = m.at(i, 3);
				}
				return ret;
			}

			void init() {
				constexpr uint32 BUFFER_SIZE = 65536U;
				{
					const D3D11_BUFFER_DESC desc =
					{
						.ByteWidth = BUFFER_SIZE,
						.Usage = D3D11_USAGE_DYNAMIC,
						.BindFlags = D3D11_BIND_VERTEX_BUFFER,
						.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
						.MiscFlags = 0,
						.StructureByteStride = 0,
					};

					auto er = suika::d3d::pDevice->CreateBuffer(&desc, nullptr, &g_vertexBuffer);
					if (FAILED(er)) {
						d3d::log_d3d.error("Failed to Create VertexBuffer");
						d3d::log_d3d.result(er);
						return;
					}
				}
				{
					const D3D11_BUFFER_DESC desc =
					{
						.ByteWidth = BUFFER_SIZE,
						.Usage = D3D11_USAGE_DYNAMIC,
						.BindFlags = D3D11_BIND_INDEX_BUFFER,
						.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
						.MiscFlags = 0,
						.StructureByteStride = 0,
					};

					auto er = suika::d3d::pDevice->CreateBuffer(&desc, nullptr, &g_indexBuffer);
					if (FAILED(er)) {
						d3d::log_d3d.error("Failed to Create IndexBuffer");
						d3d::log_d3d.result(er);
						return;
					}
				}
				{
					const D3D11_BUFFER_DESC desc =
					{
						.ByteWidth = BUFFER_SIZE,
						.Usage = D3D11_USAGE_DYNAMIC,
						.BindFlags = D3D11_BIND_VERTEX_BUFFER,
						.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
						.MiscFlags = 0,
						.StructureByteStride = 0,
					};

					auto er = suika::d3d::pDevice->CreateBuffer(&desc, nullptr, &g_instanceMatrix);
					if (FAILED(er)) {
						d3d::log_d3d.error("Failed to Create instanceMatrixBuffer");
						d3d::log_d3d.result(er);
						return;
					}
				}

				log_d3d.info("Initialize Vertex");
			}


			void set_index(const std::vector<uint16>& index, D3D11_PRIMITIVE_TOPOLOGY topology) {
				static std::vector<uint16> old_index(0);
				if (old_index == index) {
					return;
				}
				flush();
				old_index = index;
				D3D11_MAPPED_SUBRESOURCE mapped;
				D3D11_MAP map_type = D3D11_MAP_WRITE_DISCARD;
				auto er = suika::d3d::pContext->Map(g_indexBuffer.Get(), 0, map_type, 0, &mapped);
				if (FAILED(er)) {
					d3d::log_d3d.error("Failed to Update VertexBuffer");
					d3d::log_d3d.result(er);
					return;
				}
				if (uint16* const p = static_cast<uint16*>(mapped.pData)) {
					std::memcpy(p, index.data(), sizeof(uint16) * index.size());
				}
				suika::d3d::pContext->Unmap(g_indexBuffer.Get(), 0);

				suika::d3d::pContext->IASetIndexBuffer(g_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
				suika::d3d::pContext->IASetPrimitiveTopology(topology);
				::suika::d3d::vertex::index = index;
			}

			matrix4x4<float> calc_matrix(const suika::vector3<float>& origine, const suika::vector3<float>& translate, const suika::vector3<float>& rotate, const suika::vector3<float>& extend) {
				auto m = (DirectX::XMMatrixAffineTransformation({ extend.x,extend.y,extend.z },{origine.x,origine.y,origine.z},DirectX::XMQuaternionRotationRollPitchYawFromVector({rotate.x,rotate.y,rotate.z}),{translate.x,translate.y,translate.z}));

				return (to_matrix4x4<float>(DirectX::XMMatrixTranspose(m)));
			}

			void add_index(const suika::float3& origine, const suika::float3& translate, const suika::float3& rotate, const suika::float3& extend, const suika::float4& color, const suika::float2 uv) {
				if (instance_matrix.size() > 2048) {
					flush();
				}
				instance_matrix.emplace_back(calc_matrix(origine, translate, rotate, extend));
			}

			void set_ins_mode(ins_type type) {
				if (now_type != type) {
					now_type = type;
					flush();
					return;
				}
				
			}

			void flush() {
				if (instance_matrix.size() > 0) {
					{
						static const D3D11_MAP map_type = D3D11_MAP_WRITE_DISCARD;
						D3D11_MAPPED_SUBRESOURCE mapped = {};
						auto er = suika::d3d::pContext->Map(g_instanceMatrix.Get(), 0, map_type, 0, &mapped);
						if (FAILED(er)) {
							d3d::log_d3d.error("Failed to Update instanceMatrix");
							d3d::log_d3d.result(er);
							return;
						}
						if (void* const p = mapped.pData) {
							std::memcpy(p, instance_matrix.data(), sizeof(matrix4x4<float>) * instance_matrix.size());
						}
						suika::d3d::pContext->Unmap(g_instanceMatrix.Get(), 0);
					}
					stride_ins[1] = sizeof(matrix4x4<float>);
					ID3D11Buffer* buf[] = { g_vertexBuffer.Get(), g_instanceMatrix.Get()};
					suika::d3d::pContext->IASetVertexBuffers(0, 2, buf, stride_ins, offset_ins);
					d3d::pContext->DrawIndexedInstanced(static_cast<UINT>(index.size()), static_cast<UINT>(instance_matrix.size()), 0, 0, 0);
					instance_matrix.resize(0);
				}
			}
		}
	}
}