#include <d3d11.h>
#include <windows.h>
#include <wrl/client.h>
#include <vector>
#include "d3d/info.hpp"
#include "../include/suika/vertex.h"

namespace suika {
	namespace vertex {
		std::vector<uint16> index;
		std::vector<vertex_2d> vertices;
		vertex_2d create_2d(const float4& pos, const color& col, const float2& uv) {
			return vertex_2d{ .position = pos, .color = {col.r, col.g, col.b, col.a}, .uv = uv };
		}
		vertex_2d create_2d(const point<float>& pos, const color& col, const float2& uv) {
			return vertex_2d{ .position = {pos.x, pos.y, 0.0f, 1.0f}, .color = {col.r, col.g, col.b, col.a}, .uv = uv };
		}
		vertex_2d create_2d(const vector3<float>& pos, const color& col, const float2& uv) {
			return vertex_2d{ .position = {pos.x, pos.y, pos.z, 1.0f}, .color = {col.r, col.g, col.b, col.a}, .uv = uv };
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

			auto er = suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, &g_vertexBuffer);
			if (FAILED(er)) {
				d3d::log_d3d.error("Failed to Create VertexBuffer");
				d3d::log_d3d.result(er);
				return;
			}
			suika::d3d::pContext->IASetVertexBuffers(0, 1, g_vertexBuffer.GetAddressOf(), &stride, &offset);
		}

		void set_index(const std::vector<uint16>& index, primitive_topology topology) {
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.ByteWidth = static_cast<UINT>(index.size() * sizeof(uint16));
			bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bufferDesc.CPUAccessFlags = 0;
			initData.pSysMem = index.data();

			auto er = suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, &g_indexBuffer);
			if (FAILED(er)) {
				d3d::log_d3d.error("Failed to Create IndexBuffer");
				d3d::log_d3d.result(er);
				return;
			}

			suika::d3d::pContext->IASetIndexBuffer(g_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
			suika::d3d::pContext->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(topology));
		}

		void add_index(const std::vector<uint16>& idx) {
			index.insert(idx.end(), idx.begin(), idx.end());
		}

		void add_vertex(const std::vector<vertex_2d>& vtx) {
			vertices.insert(vtx.end(), vtx.begin(), vtx.end());
		}
		void internal_set(const std::vector<vertex_2d>& vertices, const std::vector<uint16>& index) {

		}
		void draw() {
			if (index.empty()) return;
			set_index(index, primitive_topology::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			d3d::pContext->DrawIndexed(static_cast<UINT>(index.size()), 0, 0);

			index.clear();
			index.shrink_to_fit();
		}
	}
}