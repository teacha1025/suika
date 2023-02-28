#include <DirectXMath.h>
#include <d3d11.h>
#include <windows.h>
#include <vector>
#include <wrl/client.h>

#include "../../include/suika/logger.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		ComPtr<ID3D11Device> pDevice;
		ComPtr<ID3D11DeviceContext> pContext;
		ComPtr<IDXGIFactory> pFactory;
		logger log_d3d;
		bool init() {
			log_d3d.set(true, "d3d.log");
			log_d3d.init();

			
			auto er = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
			if (FAILED(er)) {
				log_d3d.error("Failed to create factory");
				log_d3d.result(er);
				return false;
			}

			{
				D3D_FEATURE_LEVEL featureLevels[] = {
					D3D_FEATURE_LEVEL_11_1,
					D3D_FEATURE_LEVEL_11_0,
				};
				er = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
					featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, pDevice.GetAddressOf(), nullptr,
					pContext.GetAddressOf());
				if (FAILED(er)){
					log_d3d.error("Failed to create Direct3D11 device");
					log_d3d.result(er);
					return false;
				}
			}
			log_d3d.info("Create D3DDevice");
			return true;
		}
	}
}