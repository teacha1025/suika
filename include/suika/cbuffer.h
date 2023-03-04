#pragma once
#include "def.h"
#include "point.h"

namespace suika {
	struct matrix {
		float m[4][4];
	};

	struct cbuffer_default {
		matrix mt;
	};
	cbuffer_default set_view(const point<int>& window_size);

	void set_cbuffer(uint constant_size, void* constant, uint index);
}