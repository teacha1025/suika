#pragma once
#include "def.h"
#include "point.h"
#include "color.h"

namespace suika {
	using float2 = vector2<float>;
	using float3 = vector3<float>;
	using float4 = vector4<float>;
	using double2 = vector2<double>;
	using double3 = vector3<double>;
	using double4 = vector4<double>;
	struct color_v {
		float r, g, b, a;
	};
	enum primitive_topology {
		PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
		PRIMITIVE_TOPOLOGY_POINTLIST = 1,
		PRIMITIVE_TOPOLOGY_LINELIST = 2,
		PRIMITIVE_TOPOLOGY_LINESTRIP = 3,
		PRIMITIVE_TOPOLOGY_TRIANGLELIST = 4,
		PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
		PRIMITIVE_TOPOLOGY_LINELIST_ADJ = 10,
		PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = 11,
		PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = 12,
		PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 13,
	};
	namespace vertex {
		
		struct vertex_2d {
			float4 position;
			color_v color;
			float2 uv;
			//float2 dummy;

			bool operator == (const vertex_2d& v) const {
				return this->position.x == v.position.x && this->position.y == v.position.y && this->position.z == v.position.z && this->position.w == v.position.w
					&& this->color.r == v.color.r && this->color.g == v.color.g && this->color.b == v.color.b && this->color.a == v.color.a
					&& this->uv.x == v.uv.x && this->uv.y == v.uv.y;
			}
		};
		vertex_2d create_2d(const float4& pos, const color_f& col, const float2& uv);
		vertex_2d create_2d(const point<float>& pos, const color_f& col, const float2& uv);
		vertex_2d create_2d(const vector3<float>& pos, const color_f& col, const float2& uv);

		void draw(const std::vector<vertex_2d>& vertices, const std::vector<uint16>& index, primitive_topology topology);
		/*
		MEMO
		set_vertex,set_index,set
		set_cbuffer,update_cbuffer
		*/
	}
}