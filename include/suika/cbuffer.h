#pragma once
#include "def.h"
#include "point.h"
#include "type.h"
#include "matrix.h"

namespace suika {
	struct cbuffer_default {
		matrix<float> mt;
		cbuffer_default() {
			mt.resize(4, 4);
		}
	};
	cbuffer_default set_view(const point<int>& window_size);

	void set_cbuffer(uint constant_size, void* constant, uint index);
}