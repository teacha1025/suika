// -----------------------------------------------------------
// 
// texture
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

#include "d3d/vs.hpp"
#include "d3d/ps.hpp"
#include "d3d/cbuffer.hpp"
#include "d3d/blend.hpp"
#include "d3d/dwrite.h"
#include "d3d/texture.hpp"
#include "d3d/vertex.h"

#include "../include/suika/shader.h"
#include "../include/suika/texture.h"
#include "../include/suika/vertex.h"
#include "../include/suika/palette.h"

static const std::vector<suika::uint16> index =
{
	0, 1, 2,
	2, 1, 3,
};

namespace suika {
	std::vector<suika::vertex::vertex_2d> texture::create_vertex() {
		return {
				vertex::create_2d({0.f,0.f},{0,0,0,1.0f},{0.0f,0.0f}),
				vertex::create_2d({this->_size.x,0.f},{0,0,0,1.0f},{1.0f,0.0f}),
				vertex::create_2d({0.f,this->_size.y},{0,0,0,1.0f},{0.0f,1.0f}),
				vertex::create_2d({this->_size.x,this->_size.y},{0,0,0,1.0f},{1.0f, 1.0f}),
		};
	}

	texture& texture::turned(const point<bool>& turn)& {
		_turn = turn;
		return static_cast<texture&>(*this);
	}

	texture texture::turned(const point<bool>& turn)&& {
		_turn = turn;
		return static_cast<texture&&>(std::move(*this));
	}

	texture texture::uv(const point<float>& lt, const point<float>& rb)&& {
		_uv_lt = lt;
		_uv_rb = rb;
		return static_cast<texture&&>(std::move(*this));
	}

	texture& texture::uv(const point<float>& lt, const point<float>& rb)& {
		_uv_lt = lt;
		_uv_rb = rb;
		return static_cast<texture&>(*this);
	}

	point<bool> texture::turn() const {
		return _turn;
	}

	point<float> texture::size() const {
		return _size;
	}

	void texture::draw() {
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::texture);
		set_vs(this->_shaders.vs);
		set_ps(this->_shaders.ps);
		suika::d3d::blend::blends[_blend].set();
		suika::d3d::vertex::set_index(index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		suika::d3d::texture::set(_tex);
		d3d::vertex::set_vertex_instance(create_vertex());
		const auto left = _turn.x ? _uv_rb.x : _uv_lt.x;
		const auto right = _turn.x ? _uv_lt.x : _uv_rb.x;
		const auto top = _turn.y ? _uv_rb.y : _uv_lt.y;
		const auto bottom = _turn.y ? _uv_lt.y : _uv_rb.y;
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, this->_extend, { 0,0,0,0 }, { float2{left,top},float2{right, bottom} });
	}
}