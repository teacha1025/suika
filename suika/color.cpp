// -----------------------------------------------------------
// 
// color.
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

#include <format>

#include "../include/suika/def.h"
#include "../include/suika/color.h"

namespace suika {
	unsigned int color::to_int() const {
		return 0;
	}

	string color::to_string() const {
		return std::format("#{:02x}{:02x}{:02x}{:02x}", r, g, b, a);
	}

	hsv color::to_hsv() const {
		hsv	out;
		double min, max, _r = r / 255.0, _g = g / 255.0, _b = b / 255.0;

		out.a = a;

		min = _r < _g ? _r : _g;
		min = min < _b ? min : _b;

		max   = _r > _g ? _r : _g;
		max   = max > _b ? max : _b;
		out.v = max;

		auto d = max - min;
		if (d == 0 || max == 0) {
			return out;
		}

		out.s	= d / max;
		double h = 0;
		if (max == _r) {
			h = (_g - _b) / d;
		}
		else if (max == _g) {
			h = 2.0 + (_b - _r) / d;
		}
		else {
			h = 4.0 + (_r - _g) / d;
		}
		h *= 60;

		if (h < 0.0)
			h += 360;
		if (h > 360.0)
			h -= 360;
		out.h = (int)h;

		return out;
	}

	color_f color::to_color_f() const {
		return color_f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}

	color::operator color_f() const {
		return to_color_f();
	}

	unsigned int color_f::to_int() const {
		return 0;
	}

	string color_f::to_string() const {
		return std::format("#r:{:.2f}, g:{:.2f}, b:{:.2f}, a{:.2f}", r, g, b, a);
	}

	hsv color_f::to_hsv() const {
		return to_color().to_hsv();
	}

	color color_f::to_color() const {
		return color((ubyte)(r * 255.0f), (ubyte)(g * 255.0f), (ubyte)(b * 255.0f), (ubyte)(a * 255.0f));
	}

	unsigned int hsv::to_int() const {
		return to_color().to_int();
	}

	string hsv::to_string() const {
		return std::format("#h:{}, s:{}, v{}, a{}", h, s, v, a);
	}


	color hsv::to_color() const {
		double hh, ff;
		long   i;
		ubyte  p, q, t, _v;
		color  out;

		out.a = a;

		_v = (ubyte)(v * 255);

		if (s <= 0.0) {
			out.r = _v;
			out.g = _v;
			out.b = _v;
		}
		else {
			hh = h;
			if (hh >= 360.0)
				hh = 0.0;
			hh /= 60.0;
			i  = (long)hh;
			ff = hh - i;
			p  = (ubyte)(_v * (1.0 - s));
			q  = (ubyte)(_v * (1.0 - (s * ff)));
			t  = (ubyte)(_v * (1.0 - (s * (1.0 - ff))));

			switch (i) {
			case 0:
				out.r = _v;
				out.g = t;
				out.b = p;
				break;
			case 1:
				out.r = q;
				out.g = _v;
				out.b = p;
				break;
			case 2:
				out.r = p;
				out.g = _v;
				out.b = t;
				break;

			case 3:
				out.r = p;
				out.g = q;
				out.b = _v;
				break;
			case 4:
				out.r = t;
				out.g = p;
				out.b = _v;
				break;
			case 5:
			default:
				out.r = _v;
				out.g = p;
				out.b = q;
				break;
			}
		}
		return out;
	}
} // namespace suika
