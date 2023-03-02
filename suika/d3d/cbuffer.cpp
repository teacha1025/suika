#pragma once
#include <directxmath.h>
#include <d3d11.h>
#include "cbuffer.hpp"
#include "info.hpp"
#include "../../include/suika/point.h"
namespace suika {
	namespace d3d {
		bool create_cbuffer(ID3D11Buffer** cb, UINT size) {
			D3D11_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.ByteWidth = size;
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.CPUAccessFlags = 0;

			// 定数バッファを作成
			auto er = pDevice->CreateBuffer(&bufferDesc, nullptr, cb);
			if (FAILED(er)) {
				log_d3d.error("Failed to Create Constant Buffer");
				log_d3d.result(er);
				return false;
			}
			log_d3d.info("Create ConstantBuffer");
			return true;
		}

		void set_cbuffer(ID3D11Buffer* const* cb) {
			pContext->VSSetConstantBuffers(0, 1, cb);
		}

		void update_cbuffer(ID3D11Buffer* cb, void* buffer, size_t size, UINT index) {
			

			// GPU(シェーダ側)へ転送する
			if constexpr (false) {
				D3D11_MAPPED_SUBRESOURCE cData;
				auto er = pContext->Map(cb, index, D3D11_MAP_WRITE_DISCARD, 0, &cData);
				if (FAILED(er)) {
					log_d3d.error("Failed to Map");
					log_d3d.result(er);
					return;
				}
				memcpy_s(cData.pData, cData.RowPitch, buffer, size);
				pContext->Unmap(cb, index);
			}
			else {
				pContext->UpdateSubresource(cb, index, nullptr, buffer, 0, 0);
			}
		}

		cbuffer_0 set_view(const point<int>& window_size) {
			auto w = DirectX::XMMatrixIdentity();
			//auto v = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
			auto p = DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(window_size.x), static_cast<float>(window_size.y), 0.0f, 0.0f, 1.0f));
			/*auto w = 2.0f / static_cast<float>(window_size.x);
			auto h = 2.0f / static_cast<float>(window_size.y);
			DirectX::XMMATRIX p = DirectX::XMMatrixIdentity();
			p.r[0].m128_f32[0] = w;
			p.r[1].m128_f32[1] = -h;
			p.r[2].m128_f32[2] = 1;
			p.r[3].m128_f32[0] = 1;
			p.r[3].m128_f32[1] = -1;
			p.r[3].m128_f32[3] = 1;*/
			return { DirectX::XMMatrixTranspose(p) };
		}
	}
}