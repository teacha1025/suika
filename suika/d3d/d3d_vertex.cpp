#include <d3d11.h>
#include <DirectXMath.h>
#include <windows.h>
#include <wrl/client.h>
#include <vector>
#include "info.hpp"
#include "vertex.h"
#include "../../include/suika/vertex.h"
#include "../../include/suika/type.h"

namespace suika {
	namespace d3d {
		namespace vertex {
			std::vector<uint16> index;
			std::vector<DirectX::XMMATRIX> instance_matrix;

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

			//main.cpp‚Å‰Šú‰»
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
			}

			//void set_vertex(const void* vertices, uint vertices_size, uint stride) {
			//	D3D11_MAPPED_SUBRESOURCE mapped;
			//	D3D11_MAP map_type = D3D11_MAP_WRITE_DISCARD;
			//	auto er = suika::d3d::pContext->Map(g_vertexBuffer.Get(), 0, map_type, 0, &mapped);
			//	if (FAILED(er)) {
			//		d3d::log_d3d.error("Failed to Update VertexBuffer");
			//		d3d::log_d3d.result(er);
			//		return;
			//	}
			//	if (void* const p = mapped.pData) {
			//		std::memcpy(p, vertices, vertices_size);
			//	}
			//	suika::d3d::pContext->Unmap(g_vertexBuffer.Get(), 0);
			//
			//	suika::d3d::pContext->IASetVertexBuffers(0, 1, g_vertexBuffer.GetAddressOf(), &stride, &offset);
			//}
			//
			/*void set_vertex_instance(const void* vertices, uint vertices_size, uint stride) {
				D3D11_MAP map_type = D3D11_MAP_WRITE_DISCARD;
				{
					D3D11_MAPPED_SUBRESOURCE mapped;
					auto er = suika::d3d::pContext->Map(g_vertexBuffer.Get(), 0, map_type, 0, &mapped);
					if (FAILED(er)) {
						d3d::log_d3d.error("Failed to Update VertexBuffer");
						d3d::log_d3d.result(er);
						return;
					}
					if (void* const p = mapped.pData) {
						std::memcpy(p, vertices, vertices_size);
					}
					suika::d3d::pContext->Unmap(g_vertexBuffer.Get(), 0);
				}
				{
					D3D11_MAPPED_SUBRESOURCE mapped;
					auto er = suika::d3d::pContext->Map(g_instanceMatrix.Get(), 0, map_type, 0, &mapped);
					if (FAILED(er)) {
						d3d::log_d3d.error("Failed to Update VertexBuffer");
						d3d::log_d3d.result(er);
						return;
					}
					if (void* const p = mapped.pData) {
						std::memcpy(p, instance_matrix.data(), sizeof(DirectX::XMMATRIX) * instance_matrix.size());
					}
					suika::d3d::pContext->Unmap(g_instanceMatrix.Get(), 0);
				}
				uint st[] = { stride, sizeof(DirectX::XMMATRIX) };
				ID3D11Buffer* buf[] = { g_vertexBuffer.Get(), g_instanceMatrix.Get() };
				suika::d3d::pContext->IASetVertexBuffers(0, 2, buf, st, offset_ins);
			}*/

			void set_index(const std::vector<uint16>& index, D3D11_PRIMITIVE_TOPOLOGY topology) {
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

			DirectX::XMMATRIX calc_matrix(const suika::vector3<float>& origine, const suika::vector3<float>& translate, const suika::vector3<float>& rotate, const suika::vector3<float>& extend) {
				/*auto r = DirectX::XMMatrixRotationRollPitchYaw(rotate.z, rotate.x, rotate.y);
				auto t = DirectX::XMMatrixTranslation(translate.x, translate.y, translate.z);
				auto e = DirectX::XMMatrixScaling(extend.x, extend.y, extend.z);

				auto m = e * r * t;*/

				auto m = (DirectX::XMMatrixAffineTransformation({ extend.x,extend.y,extend.z },{origine.x,origine.y,origine.z},{rotate.x,rotate.y,rotate.z},{translate.x,translate.y,translate.z}));

				return DirectX::XMMatrixTranspose(m);
			}

			void add_index(const suika::vector3<float>& origine, const suika::vector3<float>& translate, const suika::vector3<float>& rotate, const suika::vector3<float>& extend) {
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
						const D3D11_MAP map_type = D3D11_MAP_WRITE_DISCARD;
						D3D11_MAPPED_SUBRESOURCE mapped;
						auto er = suika::d3d::pContext->Map(g_instanceMatrix.Get(), 0, map_type, 0, &mapped);
						if (FAILED(er)) {
							d3d::log_d3d.error("Failed to Update VertexBuffer");
							d3d::log_d3d.result(er);
							return;
						}
						if (void* const p = mapped.pData) {
							std::memcpy(p, instance_matrix.data(), sizeof(DirectX::XMMATRIX) * instance_matrix.size());
						}
						suika::d3d::pContext->Unmap(g_instanceMatrix.Get(), 0);
					}
					stride_ins[1] = sizeof(DirectX::XMMATRIX);

					ID3D11Buffer* buf[] = { g_vertexBuffer.Get(), g_instanceMatrix.Get() };
					suika::d3d::pContext->IASetVertexBuffers(0, 2, buf, stride_ins, offset_ins);
					d3d::pContext->DrawIndexedInstanced(static_cast<UINT>(index.size()), static_cast<UINT>(instance_matrix.size()), 0, 0, 0);
					instance_matrix.resize(0);
				}
			}

		}
	}
}