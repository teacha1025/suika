#pragma once
#include <directxmath.h>
#include <d3d11.h>
#include "cbuffer.hpp"
#include "info.hpp"
#include "../../include/suika/point.h"
using namespace DirectX;
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

        void update_cbuffer(ID3D11Buffer* cb, void* buffer, UINT index) {
            pContext->UpdateSubresource(cb, index, nullptr, buffer, 0, 0);
        }

        cbuffer_0 set_view(const point<int>& window_size) {
            cbuffer_0 cbuffer;
            cbuffer.world = XMMatrixTranspose(XMMatrixIdentity());
            cbuffer.view = XMMatrixTranspose(XMMatrixIdentity());
            cbuffer.projection = XMMatrixTranspose(XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(window_size.x), static_cast<float>(window_size.y), 0.0f, 0.0f, 1.0f));
            return cbuffer;
        }
	}
}