#pragma once
#include <Windows.h>
//https://qiita.com/ousttrue/items/8eabcd171fe00c674213
namespace suika {
	namespace d3d {
		struct vertex_shader {
			void create(const BYTE* input, size_t size);
			void set();
		};
	}
}