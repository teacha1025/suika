//https://deep-verdure.hatenablog.com/entry/2022/07/26/012943
//https://deep-verdure.hatenablog.com/entry/2022/07/23/190449
#include "d3d/dwrite.h"
#include "d3d/vertex.h"
#include "../include/suika/font.h"

namespace suika {
	void font::set(canvas::canvas_id id) const{
		d3d::dwrite::set(_font, (DWRITE_FONT_WEIGHT)_weight, (DWRITE_FONT_STYLE)_style, (DWRITE_FONT_STRETCH)_stretch, _size, _locale, (DWRITE_TEXT_ALIGNMENT)_alignment, _color, id);
	}

	void font::draw()const{
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::font);
		set(_cid);
		auto p = float2{ _transition.x - _center.x, _transition.y - _center.y };
		d3d::dwrite::draw(_text, p, _cid, D2D1_DRAW_TEXT_OPTIONS_NONE, _color.a);
	}

	rect font::rect()const{
		set(_cid);
		return suika::rect(d3d::dwrite::get_size(_text, _cid)).at(_transition).centered(_center);
	}
}  // namespace suika