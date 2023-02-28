#pragma once
#include "../../include/suika/point.h"
#include "info.hpp"

namespace suika {
	namespace d3d {
		namespace viewport {
			bool create(const point<float>& top, const point<float>& size, canvas_id id);
		}
	}
}