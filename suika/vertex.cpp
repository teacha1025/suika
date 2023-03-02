#include <d3d11.h>
#include <windows.h>
#include <wrl/client.h>
#include "d3d/info.hpp"
#include "../include/suika/vertex.h"

namespace suika {
	namespace vertex {
		vertex_2d create_2d(const float4& pos, const color& col, const float2& uv) {
			return vertex_2d{ .position = pos, .color = col, .uv = uv };
		}
		vertex_2d create_2d(const point<float>& pos, const color& col, const float2& uv) {
			return vertex_2d{ .position = {pos.x, pos.y, 0.0f, 1.0f}, .color = col, .uv = uv };
		}
		vertex_2d create_2d(const vector3<float>& pos, const color& col, const float2& uv) {
			return vertex_2d{ .position = {pos.x, pos.y, pos.z, 1.0f}, .color = col, .uv = uv };
		}

		D3D11_BUFFER_DESC bufferDesc;
		D3D11_SUBRESOURCE_DATA initData;
		UINT offset = 0;
		Microsoft::WRL::ComPtr<ID3D11Buffer> g_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> g_vertexBuffer;
		void set_vertex(const void* vertices, uint vertices_size, uint stride) {
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.ByteWidth = vertices_size;
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferDesc.CPUAccessFlags = 0;

			ZeroMemory(&initData, sizeof(initData));
			initData.pSysMem = vertices;

			auto er = suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, g_vertexBuffer.GetAddressOf());
			if (FAILED(er)) {
				d3d::log_d3d.error("Failed to Create VertexBuffer");
				d3d::log_d3d.result(er);
				return;
			}
			suika::d3d::pContext->IASetVertexBuffers(0, 1, g_vertexBuffer.GetAddressOf(), &stride, &offset);
		}

		void set_index(const void* index, uint index_size) {
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.ByteWidth = index_size;
			bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bufferDesc.CPUAccessFlags = 0;
			initData.pSysMem = index;

			auto er = suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, &g_indexBuffer);
			if (FAILED(er)) {
				d3d::log_d3d.error("Failed to Create IndexBuffer");
				d3d::log_d3d.result(er);
				return;
			}

			suika::d3d::pContext->IASetIndexBuffer(g_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
			suika::d3d::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}
	}
}