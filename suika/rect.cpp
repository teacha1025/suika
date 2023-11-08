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
	std::vector<suika::vertex::vertex_2d> rect::create_vertex() {
		return {
			vertex::create_2d({0.f,0.f},this->_color,{0,0}),
			vertex::create_2d({this->_size.x,0.f},this->_color,{1,0}),
			vertex::create_2d({0.f,this->_size.y},this->_color,{0,1}),
			vertex::create_2d({this->_size.x,this->_size.y},this->_color,{1,1}),
		};
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