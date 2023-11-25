// -----------------------------------------------------------
// 
// line
// 
// Copyright 2023 teacha1025
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// -----------------------------------------------------------

#pragma once

#include "d3d/vertex.h"
#include "d3d/blend.hpp"
#include "../include/suika/shader.h"
#include "../include/suika/line.h"
#include "../include/suika/vector.h"

static std::vector<suika::uint16> index = { 0,1 };

namespace suika {
	std::vector<suika::vertex::vertex_2d> line::create_vertex() {
		index = { 0,1 };
		return {
			vertex::create_2d(this->_A, this->_color, { 0,0 }),
			vertex::create_2d(this->_B, this->_color, { 0,0 })
		};
	}

	std::vector<suika::vertex::vertex_2d> line::create_vertex_bold(float b) {
		index = { 0,1,2,2,1,3 };
		const suika::point<float> a = { this->_B - this->_A };
		const suika::point<float> u = suika::point<float>{ a.y,-a.x };
		const suika::point<float> v = suika::point<float>{ -a.y,a.x };
		return {
			vertex::create_2d(vector::set_length(u, b / 2.0f) + _A, this->_color, { 0,0 }),
			vertex::create_2d(vector::set_length(u, b / 2.0f) + _B, this->_color, { 1,0 }),
			vertex::create_2d(vector::set_length(v, b / 2.0f) + _A, this->_color, { 0,1 }),
			vertex::create_2d(vector::set_length(v, b / 2.0f) + _B, this->_color, { 1,1 })
		};
	}

	std::vector<suika::vertex::vertex_2d> line::create_vertex_bold_round(float b) {
		return {
			vertex::create_2d(this->_A, this->_color, { 0,0 }),
			vertex::create_2d(this->_B, this->_color, { 0,0 })
		};
	}

	void line::draw() {
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::line);
		set_vs(this->_shaders.vs);
		set_ps(this->_shaders.ps);
		d3d::blend::blends[_blend].set();
		
		d3d::vertex::set_vertex_instance(create_vertex());
		d3d::vertex::set_index(index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_LINELIST);
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, this->_extend, { _color.r, _color.g, _color.b, _color.a }, { 0,0 });

	}

	void line::draw(float b, bool rounded) {
		if (b <= 1) {
			this->draw();
			return;
		}
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::line);
		set_vs(this->_shaders.vs);
		set_ps(this->_shaders.ps);
		d3d::blend::blends[_blend].set();
		
		if (rounded) {
			d3d::vertex::set_vertex_instance(create_vertex_bold_round(b));
		}
		else {
			d3d::vertex::set_vertex_instance(create_vertex_bold(b));
		}
		d3d::vertex::set_index(index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, this->_extend, { _color.r, _color.g, _color.b, _color.a }, { 0,0 });
	}
}