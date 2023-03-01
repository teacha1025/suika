#include <d3d11.h>
#include <windows.h>
#include <unordered_map>
#include <wrl/client.h>

#include "../../include/suika/point.h"
#include "info.hpp"

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		std::unordered_map<canvas_id, ComPtr<IDXGISwapChain>> pSwapChain;
		namespace swapchain {
			bool create(const point<float>& size, HWND hWnd, canvas_id id) {
				DXGI_SWAP_CHAIN_DESC descSwapChain = {
					.BufferDesc = {
						.Width = static_cast<UINT>(size.x), 
						.Height = static_cast<UINT>(size.x),
						.RefreshRate = {60U, 1U}, 
						.Format = DXGI_FORMAT_R8G8B8A8_UNORM, 
						.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,	
						.Scaling = DXGI_MODE_SCALING_UNSPECIFIED
					},
					.SampleDesc = {1, 0},
					.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
					.BufferCount = 1U, .OutputWindow = hWnd,
					.Windowed = true,
					.SwapEffect = DXGI_SWAP_EFFECT_DISCARD,
					.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH 
				};
				pSwapChain.insert({ id, {} });
				auto& sw = (pSwapChain[id]);
				auto er = pFactory->CreateSwapChain(pDevice.Get(), &descSwapChain, sw.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to create swapchain");
					log_d3d.result(er);
					return false;
				}
				log_d3d.info("Create SwapChain");
				return true;
			}
		}
	}
}