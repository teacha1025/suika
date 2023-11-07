#pragma once
#include "d3d/vertex.h"
#include "d3d/blend.hpp"
#include "../include/suika/shader.h"
#include "../include/suika/rect.h"

static const std::vector<suika::uint16> index =
{
	0, 1, 2,
	2, 1, 3,
};

namespace suika {
#if 1
	auto vec2xmvec(const vector3<float>& v) {
		return DirectX::XMVECTOR{ v.x, v.y, v.z };
	}
	void rect::draw() {
		set_vs(this->_shaders.vs);
		set_ps(this->_shaders.ps);
		suika::d3d::blend::blends[_blend].set();
		suika::d3d::vertex::set_index(index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::rect);
		d3d::vertex::set_vertex_instance(create_vertex());
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, this->_extend);

	}
#endif
}