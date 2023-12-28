// -----------------------------------------------------------
// 
// animator
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

#include "../include/suika/animator.h"

namespace suika {
	std::vector<vertex::vertex_2d> animator::create_vertex() {
		return {};
	}

	animator::animator(string path, const point<uint>& div) {
		_anm = animation(path, div);
	}

	animator::animator(string path, const point<uint>& div, const point<float>& region_lt, const point<float>& region_rb) {
		_anm = animation(path, div, region_lt, region_rb);
	}

	void animator::add(uint key, std::vector<uint> pattern, double interval, uint next) {
		if (_pattern.empty()) {
			_key = key;
		}
		_pattern[key] = { pattern, interval, false, next };
	}

	void animator::add(uint key, std::vector<uint> pattern, double interval) {
		if (_pattern.empty()) {
			_key = key;
		}
		_pattern[key] = { pattern, interval, true, 0 };
	}

	void animator::condition(uint from, uint to, std::function<bool()> cond, bool smooth) {
		_condition[{from, to}] = { cond, smooth };
	}

	animator& animator::turned(const point<bool>& turn)& {
		_turn = turn;
		return static_cast<animator&>(*this);
	}

	animator animator::turned(const point<bool>& turn)&& {
		_turn = turn;
		return static_cast<animator&&>(std::move(*this));
	}

	void animator::updated(double t) {
		if (_pattern.empty()) {
			return;
		}
		for (const auto& [key, cond] : _condition) {
			if (key.first == _key) {
				if (cond.first()) {
					auto k = _key;
					int ind = (int)_anm.index();
					_key = key.second;
					_anm.patterned(_pattern[_key].pattern, _pattern[_key].interval, _pattern[_key].loop);
					if (cond.second && !_pattern[k].loop) {
						_anm.indexed(std::clamp((int)_pattern[k].pattern.size() - ind, 0, (int)_pattern[_key].pattern.size() - 1));
					}
					return;
				}
			}
		}
		if (_anm.finished()) {
			_key = _pattern[_key].next;
			_anm.patterned(_pattern[_key].pattern, _pattern[_key].interval, _pattern[_key].loop);
			return;
		}
		_anm.updated(t);
	}

	void animator::set(uint key) {
		_key = key;
		_anm.patterned(_pattern[_key].pattern, _pattern[_key].interval, _pattern[_key].loop);
	}

	rect animator::rect() const {
		return _anm.rect();
	}

	void animator::draw() {
		_anm.at(_transition).blended(_blend).centered(_center).extended(_extend).rotated(_rotation).turned(_turn).draw();
	}
}
