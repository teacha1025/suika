#include <DirectXMath.h>
#include <d3d11.h>
#include <windows.h>
#include <unordered_map>
#include <wrl/client.h>

#include "../../include/suika/point.h"
#include "info.hpp"

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		std::unordered_map<canvas_id, ComPtr<ID3D11RenderTargetView>> pRTView;
		namespace RTV {
			bool create(canvas_id id) {
				ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
				auto er = pSwapChain[id]->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pBackBuffer.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to get back buffer");
					log_d3d.result(er);
					return false;
				}

				pRTView.insert({ id, {} });
				auto& rtv = (pRTView[id]);
				er = pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, rtv.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to create render target view");
					log_d3d.result(er);
					return false;
				}
				log_d3d.info("Create RexderTargetView");
				return true;
			}
		}
	}
}