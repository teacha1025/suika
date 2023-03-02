#pragma once
#include "def.h"
#include "point.h"
#include "color.h"

namespace suika {
	struct float2 {
		float x, y;
	};
	struct float3 {
		float x, y, z;
	};
	struct float4 {
		float x, y, z, w;
	};
	struct double2 {
		double x, y;
	};
	struct double3 {
		double x, y, z;
	};
	struct double4 {
		double x, y, z, w;
	};
	namespace vertex {
		struct vertex_2d {
			float4 position;
			color color;
			float2 uv;
		};
		vertex_2d create_2d(const float4& pos, const color& col, const float2& uv);
		vertex_2d create_2d(const point<float>& pos, const color& col, const float2& uv);
		vertex_2d create_2d(const vector3<float>& pos, const color& col, const float2& uv);

		void set_vertex(const void* vertices, uint vertices_size, uint stride);

		void set_index(const void* index, uint index_size);
	}
}