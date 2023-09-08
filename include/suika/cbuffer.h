#pragma once
#include "def.h"
#include "point.h"
#include "type.h"
#include "matrix.h"

namespace suika {
	struct matrix4x4 {
		float mt[4][4];
	};
	struct cbuffer_default {
		matrix4x4 mt;
	};
	cbuffer_default set_view(const point<int>& window_size);

	void set_cbuffer(uint constant_size, void* constant, uint index);
}