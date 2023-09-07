#pragma once
#include "d3d/vertex.h"
#include "../include/suika/rect.h"

namespace suika {
	void rect::draw() {
		auto vec2xmvec = [](const vector3<float>& v) {
			return DirectX::XMVECTOR(v.x, v.y, v.z);
		};
		auto affin = [&](const point<int>& uv) {
			point<float> _p = this->_size * uv;
			DirectX::XMVECTOR p(_p.x, _p.y, 0);

			auto mat = DirectX::XMMatrixAffineTransformation(vec2xmvec(this->_extend), vec2xmvec(this->_center), vec2xmvec(this->_rotation), vec2xmvec(this->_transition));
			return DirectX::mul	
		};
		auto create_vertex = [&]() {
			return std::vector<suika::vertex::vertex_2d> {
				suika::vertex::create_2d(affin({0,0})),
				suika::vertex::create_2d(suika::vector2<float>{pos.x + size.x, pos.y}, this->_color, { 1,0 }),
				suika::vertex::create_2d(suika::vector2<float>{pos.x, pos.y + size.y}, this->_color, { 0,1 }),
				suika::vertex::create_2d(suika::vector2<float>{pos.x + size.x, pos.y + size.y}, this->_color, { 1,1 }),
			};
		};
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::rect);
		d3d::vertex::set_vertex_instance();
		d3d::vertex::add_index(this->_center, this->_transition, this->_rotation, this->_extend);
	}
}