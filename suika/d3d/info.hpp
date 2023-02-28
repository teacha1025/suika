#pragma once
#ifndef _SK_D3D_INFO
#define _SK_D3D_INFO

#include <d3d11.h>
#include <unordered_map>
#include <wrl/client.h>
#include "../../include/suika/logger.h"


namespace suika {
	namespace d3d {
		extern Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
		extern Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
		extern Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

		using canvas_id = uint;
		extern std::unordered_map<canvas_id, Microsoft::WRL::ComPtr<IDXGISwapChain>> pSwapChain;
		extern std::unordered_map<canvas_id, Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> pRTView;
		//extern std::unordered_map<canvas_id, Microsoft::WRL::ComPtr<ID3D11DepthStencilView>> pDSView;
		extern std::unordered_map<canvas_id, D3D11_VIEWPORT> ViewPort;
		extern logger log_d3d;
	}
}
#endif