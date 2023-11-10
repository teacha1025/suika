#pragma once
#include "d3d/vertex.h"
#include "d3d/blend.hpp"
#include "../include/suika/shader.h"
#include "../include/suika/circle.h"

static std::vector<suika::uint16> index;

namespace suika {
	std::vector<suika::vertex::vertex_2d> circle::create_vertex() {
		index.clear();
		index.reserve(this->_resolution * 3);
		const double dt = PI_2 / this->_resolution;
		static std::vector<suika::vertex::vertex_2d> ret;
		ret.clear();
		ret.reserve(this->_resolution * 3);
		ret.emplace_back(vertex::create_2d({ 0,0 }, this->_color, { 0.5f, 0.5f }));
		for (uint16 i = 0; i < this->_resolution; i++) {
			const double theta1 = dt * i;
			const double x1 = cos(theta1);
			const double y1 = sin(theta1);
			const float u1 = (float)(x1 * 0.5 + 0.5);
			const float v1 = (float)(y1 * 0.5 + 0.5);
			ret.emplace_back(vertex::create_2d({ x1 * this->_radius,y1 * this->_radius }, this->_color, { u1,v1 }));
			index.emplace_back(0);
			index.emplace_back(i+1);
			index.emplace_back(i+2);
		}
		*(index.end()-1) = 1;
		return ret;
	}
	void circle::draw() {
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::circle);
		set_vs(this->_shaders.vs);
		set_ps(this->_shaders.ps);
		d3d::blend::blends[_blend].set();
		d3d::vertex::set_vertex_instance(create_vertex());
		d3d::vertex::set_index(index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, this->_extend, { _color.r, _color.g, _color.b, _color.a }, { 0,0 });

	}
}