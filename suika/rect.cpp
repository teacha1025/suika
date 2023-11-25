// -----------------------------------------------------------
// 
// rect
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
	std::vector<suika::vertex::vertex_2d> rect::create_vertex() {
		return {
			vertex::create_2d({0.f,0.f},this->_color,{0,0}),
			vertex::create_2d({this->_size.x,0.f},this->_color,{1,0}),
			vertex::create_2d({0.f,this->_size.y},this->_color,{0,1}),
			vertex::create_2d({this->_size.x,this->_size.y},this->_color,{1,1}),
		};
	}
	void rect::draw() {
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::rect);
		set_vs(this->_shaders.vs);
		set_ps(this->_shaders.ps);
		suika::d3d::blend::blends[_blend].set();
		suika::d3d::vertex::set_index(index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		d3d::vertex::set_vertex_instance(create_vertex());
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, this->_extend, { _color.r, _color.g, _color.b, _color.a }, { 0,0 });
	}
#endif
}