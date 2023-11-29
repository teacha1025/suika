// -----------------------------------------------------------
// 
// animation
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

#include <vector>

#include "d3d/vs.hpp"
#include "d3d/ps.hpp"
#include "d3d/cbuffer.hpp"
#include "d3d/blend.hpp"
#include "d3d/dwrite.h"
#include "d3d/texture.hpp"
#include "d3d/vertex.h"

#include "../include/suika/except.h"
#include "../include/suika/shader.h"
#include "../include/suika/animation.h"
#include "../include/suika/vertex.h"
#include "../include/suika/rect.h"
#include "../include/suika/palette.h"

static const std::vector<suika::uint16> index =
{
	0, 1, 2,
	2, 1, 3,
};

namespace suika {
	extern std::unordered_map<string, d3d::texture::texture> textures;
	animation::animation(string path, const point<uint>& div) :_path(path) {
		if (!textures.contains(path)) {
			textures[path] = d3d::texture::texture(path);
		}
		_size = textures[path].size;
		_div = div;
		_draw_size = _size / _div;
		_shaders = { TEXTURE_VERTEX, TEXTURE_PIXEL };
		_pattern = { 0 };
		auto& idx = _pattern[0];
		point<uint> i = { idx % _div.x, idx / _div.x };
		_uv_lt = { (float)i.x / _div.x, (float)i.y / _div.y };
		_uv_rb = { (float)(i.x + 1) / _div.x, (float)(i.y + 1) / _div.y };
		_uv_lt = _region_lt + (_region_rb - _region_lt) * _uv_lt;
		_uv_rb = _region_lt + (_region_rb - _region_lt) * _uv_rb;
	}
	animation::animation(string path, const point<uint>& div, const point<float>& region_lt, const point<float>& region_rb) :_path(path) {
		if (!textures.contains(path)) {
			textures[path] = d3d::texture::texture(path);
		}
		_size = textures[path].size;
		_draw_size = _size;
		_shaders = { TEXTURE_VERTEX, TEXTURE_PIXEL };
		_pattern = { 0 };
		auto& idx = _pattern[0];
		point<uint> i = { idx % _div.x, idx / _div.x };
		_uv_lt = { (float)i.x / _div.x, (float)i.y / _div.y };
		_uv_rb = { (float)(i.x + 1) / _div.x, (float)(i.y + 1) / _div.y };
		_uv_lt = _region_lt + (_region_rb - _region_lt) * _uv_lt;
		_uv_rb = _region_lt + (_region_rb - _region_lt) * _uv_rb;
	}

	std::vector<suika::vertex::vertex_2d> animation::create_vertex() {
		return {
			vertex::create_2d({0.f,0.f},{0,0,0,1.0f},{0.0f,0.0f}),
			vertex::create_2d({1.f,0.f},{0,0,0,1.0f},{1.0f,0.0f}),
			vertex::create_2d({0.f,1.f},{0,0,0,1.0f},{0.0f,1.0f}),
			vertex::create_2d({1.f,1.f},{0,0,0,1.0f},{1.0f,1.0f}),
		};
	}

	animation& animation::turned(const point<bool>& turn)& {
		_turn = turn;
		return static_cast<animation&>(*this);
	}

	animation animation::turned(const point<bool>& turn)&& {
		_turn = turn;
		return static_cast<animation&&>(std::move(*this));
	}

	animation& animation::patterned(const std::vector<uint>& pattern, const std::vector<double>& interval, bool loop)& {
		if (_pattern != pattern) {
			dt = 0;
			_index = 0;
			_pattern = pattern;
			auto& idx = _pattern[0];
			point<uint> i = { idx % _div.x, idx / _div.x };
			_uv_lt = { (float)i.x / _div.x, (float)i.y / _div.y };
			_uv_rb = { (float)(i.x + 1) / _div.x, (float)(i.y + 1) / _div.y };
			_uv_lt = _region_lt + (_region_rb - _region_lt) * _uv_lt;
			_uv_rb = _region_lt + (_region_rb - _region_lt) * _uv_rb;
		}

		_index %= _pattern.size();
		_is_finished = false;
		_is_loop = loop;
		return static_cast<animation&>(*this);
	}

	animation animation::patterned(const std::vector<uint>& pattern, const std::vector<double>& interval, bool loop)&& {
		if (_pattern != pattern) {
			dt = 0;
			_pattern = pattern;
			_index = 0;
			auto& idx = _pattern[0];
			point<uint> i = { idx % _div.x, idx / _div.x };
			_uv_lt = { (float)i.x / _div.x, (float)i.y / _div.y };
			_uv_rb = { (float)(i.x + 1) / _div.x, (float)(i.y + 1) / _div.y };
			_uv_lt = _region_lt + (_region_rb - _region_lt) * _uv_lt;
			_uv_rb = _region_lt + (_region_rb - _region_lt) * _uv_rb;
		}

		_interval = interval;
		_index %= _pattern.size();
		_is_finished = false;
		_is_loop = loop;
		return static_cast<animation&&>(std::move(*this));
	}

	animation& animation::patterned(const std::vector<uint>& pattern, double interval, bool loop)& {
		if (_pattern != pattern) {
			dt = 0;
			_pattern = pattern;
			_index = 0;
			auto& idx = _pattern[0];
			point<uint> i = { idx % _div.x, idx / _div.x };
			_uv_lt = { (float)i.x / _div.x, (float)i.y / _div.y };
			_uv_rb = { (float)(i.x + 1) / _div.x, (float)(i.y + 1) / _div.y };
			_uv_lt = _region_lt + (_region_rb - _region_lt) * _uv_lt;
			_uv_rb = _region_lt + (_region_rb - _region_lt) * _uv_rb;
		}

		_interval.resize(_pattern.size());
		std::fill(_interval.begin(), _interval.end(), interval);
		_index %= _pattern.size();
		_is_finished = false;
		_is_loop = loop;

		return static_cast<animation&>(*this);
	}

	animation animation::patterned(const std::vector<uint>& pattern, double interval, bool loop)&& {
		if (_pattern != pattern) {
			dt = 0;
			_pattern = pattern;
			_index = 0;
			auto& idx = _pattern[0];
			point<uint> i = { idx % _div.x, idx / _div.x };
			_uv_lt = { (float)i.x / _div.x, (float)i.y / _div.y };
			_uv_rb = { (float)(i.x + 1) / _div.x, (float)(i.y + 1) / _div.y };
			_uv_lt = _region_lt + (_region_rb - _region_lt) * _uv_lt;
			_uv_rb = _region_lt + (_region_rb - _region_lt) * _uv_rb;
		}

		_interval.resize(_pattern.size());
		std::fill(_interval.begin(), _interval.end(), interval);
		_index %= _pattern.size();
		_is_finished = false;
		_is_loop = loop;

		return static_cast<animation&&>(std::move(*this));
	}

	void animation::updated(double t) {
		dt += t;
		if (!_is_finished && dt >= _interval[_index]) {
			dt = 0;
			if (!_is_loop && _index + 1 == _pattern.size()) {
				_is_finished = true;
			}
			else {
				_index++;
				_index %= _pattern.size();
				auto& idx = _pattern[_index];

				point<uint> i = { idx % _div.x, idx / _div.x };
				_uv_lt = { (float)i.x / _div.x, (float)i.y / _div.y };
				_uv_rb = { (float)(i.x + 1) / _div.x, (float)(i.y + 1) / _div.y };
				_uv_lt = _region_lt + (_region_rb - _region_lt) * _uv_lt;
				_uv_rb = _region_lt + (_region_rb - _region_lt) * _uv_rb;
			}
		}
	}

	point<bool> animation::turn() const {
		return _turn;
	}

	point<float> animation::size() const {
		return _draw_size;
	}

	bool animation::finished() const {
		return _is_finished;
	}

	rect animation::rect() const
	{
		return suika::rect(_draw_size).at(_transition).rotated(_rotation).centered(_center).extended(_extend);
	}

	void animation::indexed(uint i) {
		_index = i;
		auto& idx = _pattern[_index];
		point<uint> j = { idx % _div.x, idx / _div.x };
		_uv_lt = { (float)j.x / _div.x, (float)j.y / _div.y };
		_uv_rb = { (float)(j.x + 1) / _div.x, (float)(j.y + 1) / _div.y };
		_uv_lt = _region_lt + (_region_rb - _region_lt) * _uv_lt;
		_uv_rb = _region_lt + (_region_rb - _region_lt) * _uv_rb;
	}

	uint animation::index() const {
		return _index;
	}

	void animation::draw() {
		const auto left = _turn.x ? _uv_rb.x : _uv_lt.x;
		const auto right = _turn.x ? _uv_lt.x : _uv_rb.x;
		const auto top = _turn.y ? _uv_rb.y : _uv_lt.y;
		const auto bottom = _turn.y ? _uv_lt.y : _uv_rb.y;

		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::texture);
		suika::d3d::texture::set(textures[_path]);
		set_vs(this->_shaders.vs);
		set_ps(this->_shaders.ps);
		suika::d3d::blend::blends[_blend].set();
		suika::d3d::vertex::set_index(::index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		d3d::vertex::set_vertex_instance(create_vertex());
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, double3{ this->_extend.x* this->_draw_size.x, this->_extend.y* this->_draw_size.y, this->_extend.z }, { 0,0,0,0 }, { float2{left,top},float2{right, bottom} });
	}
}