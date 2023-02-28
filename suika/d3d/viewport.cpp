#include <DirectXMath.h>
#include <d3d11.h>
#include <windows.h>
#include <unordered_map>
#include <wrl/client.h>
#include "../../include/suika/point.h"
#include "info.hpp"

namespace suika {
	namespace d3d {
		std::unordered_map<canvas_id, D3D11_VIEWPORT> ViewPort;
		namespace viewport {
			bool create(const point<float>& top, const point<float>& size, canvas_id id) {
				ViewPort.insert({ id, D3D11_VIEWPORT{.TopLeftX = top.x, .TopLeftY = top.y, .Width = size.x,.Height = size.y, .MinDepth = 0.0f, .MaxDepth = 1.0f } });
				return true;
			}
		}
	}
};