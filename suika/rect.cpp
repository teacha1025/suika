#pragma once
#include "d3d/vertex.h"
#include "../include/suika/rect.h"
#include "../include/suika/matrix.h"

namespace suika {
#if 1
	void rect::draw() {
		auto vec2xmvec = [](const vector3<float>& v) {
			return DirectX::XMVECTOR{ v.x, v.y, v.z };
		};
		auto affine = [&](const point<int>& uv) {
			point<float> _p = this->_size * uv;
			float4 p(_p.x, _p.y, 0, 0);

			return vertex::vertex_2d{ .position = p, .color = {.r = this->_color.r, .g = this->_color.g, .b = this->_color.b, .a = this->_color.a}, .uv = uv };
		};
		auto create_vertex = [&]() {
			return std::vector<suika::vertex::vertex_2d> {
				affine({ 0,0 }),
				affine({ 1,0 }),
				affine({ 0,1 }),
				affine({ 1,1 }),
			};
		};
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::rect);
		d3d::vertex::set_vertex_instance(create_vertex());
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, this->_extend);
	}
#endif
}