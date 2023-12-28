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
			vertex::create_2d(this->_B, this->_color, { 1,1 })
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
		const auto c = _center * double3{ (_extend.x), (_extend.y), (_extend.z) };
		d3d::vertex::set_vertex_instance(create_vertex());
		d3d::vertex::set_index(index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_LINELIST);
		d3d::vertex::add_index((float3)c, this->_transition - (float3)c, this->_rotation, this->_extend, {_color.r, _color.g, _color.b, _color.a}, {float2{0,0},float2{1,1}});

	}
	template<concepts::numbers T>
	matrix<T> to_matrix(DirectX::XMMATRIX m) {
		matrix<T> ret;
		ret.resize(4, 4);
		ret.at(0, 0) = m.r[0].m128_f32[0];
		ret.at(0, 1) = m.r[0].m128_f32[1];
		ret.at(0, 2) = m.r[0].m128_f32[2];
		ret.at(0, 3) = m.r[0].m128_f32[3];

		ret.at(1, 0) = m.r[1].m128_f32[0];
		ret.at(1, 1) = m.r[1].m128_f32[1];
		ret.at(1, 2) = m.r[1].m128_f32[2];
		ret.at(1, 3) = m.r[1].m128_f32[3];

		ret.at(2, 0) = m.r[2].m128_f32[0];
		ret.at(2, 1) = m.r[2].m128_f32[1];
		ret.at(2, 2) = m.r[2].m128_f32[2];
		ret.at(2, 3) = m.r[2].m128_f32[3];

		ret.at(3, 0) = m.r[3].m128_f32[0];
		ret.at(3, 1) = m.r[3].m128_f32[1];
		ret.at(3, 2) = m.r[3].m128_f32[2];
		ret.at(3, 3) = m.r[3].m128_f32[3];
		return ret;
	}
	static matrix<float> calc_matrix(const suika::vector3<float>& origine, const suika::vector3<float>& translate, const suika::vector3<float>& rotate, const suika::vector3<float>& extend) {
		auto m = (DirectX::XMMatrixAffineTransformation({ extend.x,extend.y,extend.z }, { origine.x,origine.y,origine.z }, DirectX::XMQuaternionRotationRollPitchYawFromVector({ rotate.x,rotate.y,rotate.z }), { translate.x,translate.y,translate.z }));

		return (to_matrix<float>(DirectX::XMMatrixTranspose(m)));
	}

	point<float> line::A() const {
		const auto ct = _center * double3{ sqrt(_extend.x), sqrt(_extend.y), sqrt(_extend.z) };
		const matrix<double> mtx = vector::affine_transformation((double3)_center, (double3)_transition, (double3)_rotation, (double3)_extend);
		const auto c = mtx * double4(_A.x, _A.y, 1.0, 1.0);
		return { c.x,c.y };
	}

	point<float> line::B() const{
		const auto ct = _center * double3{ sqrt(_extend.x), sqrt(_extend.y), sqrt(_extend.z) };
		const matrix<double> mtx = vector::affine_transformation((double3)_center, (double3)_transition, (double3)_rotation, (double3)_extend);
		const auto c = mtx * double4(_B.x, _B.y, 1.0, 1.0);
		return { c.x,c.y };
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
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, this->_extend, { _color.r, _color.g, _color.b, _color.a }, { float2{ 0,0 },float2{1,1} });
	}
}
