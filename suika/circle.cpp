// -----------------------------------------------------------
// 
// circle
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
#include "../include/suika/circle.h"

static std::vector<suika::uint16> index;

namespace suika {
	std::vector<suika::vertex::vertex_2d> circle::create_vertex() {
		index.clear();
		index.reserve((uint64)(this->_resolution) * 3);
		const double dt = PI_2 / this->_resolution;
		static std::vector<suika::vertex::vertex_2d> ret;
		ret.clear();
		ret.reserve((uint64)(this->_resolution) * 3 + 1);
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
		auto c = (this->_center * this->_extend);
		d3d::vertex::add_index(c, this->_transition - c, this->_rotation, this->_extend, { _color.r, _color.g, _color.b, _color.a }, { float2{0,0},float2{1,1} });

	}
	point<circle::position_type> circle::offset() const {
		const auto mtx = vector::affine_transformation({}, {}, (double3)_rotation, (double3)_extend);
		const auto c = mtx * double4(_center.x, _center.y, 1.0, 1.0);
		return { c.x,c.y };
	}

	vector3<circle::position_type> circle::offset_xyz() const {
		const auto mtx = vector::affine_transformation({}, {}, _rotation, (float3)_extend);
		const auto c = mtx * float4(_center.x, _center.y, _center.z, 1.0f);
		return float3{ c.x,c.y,c.z };
	}
}
