#pragma once
#include "../../include/suika/point.h"
#include "info.hpp"

namespace suika {
	namespace d3d {
		namespace swapchain {
			bool create(const point<float>& size, HWND hWnd, canvas_id id);
		}
	}
}