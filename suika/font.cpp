// -----------------------------------------------------------
// 
// font draw.
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

#include "d3d/dwrite.h"
#include "d3d/vertex.h"
#include "../include/suika/font.h"

namespace suika {
	string font::create_key() const {
		return std::to_string((int)_style) + std::to_string((int)_weight) + std::to_string((int)_alignment) + std::to_string((int)_stretch) + std::to_string(_size) + std::to_string(_edge_width);
	}

	void font::set(canvas::canvas_id id) const{
		d3d::dwrite::set(_font, (DWRITE_FONT_WEIGHT)_weight, (DWRITE_FONT_STYLE)_style, (DWRITE_FONT_STRETCH)_stretch, _size, _locale, (DWRITE_TEXT_ALIGNMENT)_alignment, id);
	}

	void font::draw() const {
		if(_size == 0.0f) return;
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::font);
		set(_cid);
		auto p = float2{ _transition.x - _center.x, _transition.y - _center.y };
		if (!_edge_enabled) {
			d3d::dwrite::draw(_text, p, _cid, _color, D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT, _color.a);
		}
		else {
			d3d::dwrite::draw(_font, _size,_text, p, _cid, _color, _edge_width, _edge_color, D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT,  _color.a, create_key());
		}
	}

	rect font::rect() const {
		if (_size == 0.0f) return suika::rect({ 0,0 });
		set(_cid);
		if (_edge_enabled) {
			const auto r = d3d::dwrite::get_size_edged(_font, _text, _size, _edge_width, create_key());
			return suika::rect({ r.x,r.y }).at(_transition).centered({ r.x / 2.0, r.y / 2.0 });
		}
		else {
			const auto r = d3d::dwrite::get_size(_text, _cid);
			return suika::rect({ r.x,r.y }).at(_transition).centered({ r.x / 2.0, r.y / 2.0 });
		}
	}
}  // namespace suika
