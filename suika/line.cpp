#pragma once
#include "d3d/vertex.h"
#include "d3d/blend.hpp"
#include "../include/suika/shader.h"
#include "../include/suika/line.h"

static const std::vector<suika::uint16> index = { 0,1 };

namespace suika {
	std::vector<suika::vertex::vertex_2d> line::create_vertex() {
		return {
			vertex::create_2d(this->_A, this->_color, { 0,0 }),
			vertex::create_2d(this->_B, this->_color, { 0,0 })
		};
	}
	void line::draw() {
		set_vs(this->_shaders.vs);
		set_ps(this->_shaders.ps);
		d3d::blend::blends[_blend].set();
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::line);
		d3d::vertex::set_vertex_instance(create_vertex());
		d3d::vertex::set_index(index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_LINELIST);
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, this->_extend);

	}

	void line::draw(float b, bool rounded) {

	}
}