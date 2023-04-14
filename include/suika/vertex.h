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
	struct color_v {
		uint r, g, b, a;
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
			float2 dummy;
		};
		vertex_2d create_2d(const float4& pos, const color& col, const float2& uv);
		vertex_2d create_2d(const point<float>& pos, const color& col, const float2& uv);
		vertex_2d create_2d(const vector3<float>& pos, const color& col, const float2& uv);

		void set_vertex(const void* vertices, uint vertices_size, uint stride);

		void set_index(const std::vector<uint16>& index, primitive_topology topology);
		template<class vertex_type>
		void set(const std::vector<vertex_type>& vertices, const std::vector<uint16>& index, primitive_topology topology) {
			set_vertex(vertices.data(), static_cast<uint>(vertices.size() * sizeof(vertex_type)), static_cast<uint>(sizeof(vertex_type)));
			set_index(index, suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}
		void internal_set(const std::vector<vertex_2d>& vertices, const std::vector<uint16>& index);
#if 0
		extern std::vector<uint16> index;
		void add_index(const std::vector<uint16>& index);
		void draw();
#endif
		/*
		MEMO
		set_vertex,set_index,set
		set_cbuffer,update_cbuffer
		*/
	}
}