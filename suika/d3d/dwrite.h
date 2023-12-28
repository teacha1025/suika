// -----------------------------------------------------------
// 
// direct write.
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
#include <dwrite.h>
#include <d2d1.h>

#include "info.hpp"
#include "../../include/suika/string.h"
#include "../../include/suika/color.h"
#include "../../include/suika/point.h"

namespace suika {
	namespace d3d{
		namespace dwrite {
			void init(canvas_id window);
			void set(const string& font, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch, float size, const string& locale, DWRITE_TEXT_ALIGNMENT alignment, canvas_id window);
			void draw(string str, point<float> pos, canvas_id window, const color_f& color, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS::D2D1_DRAW_TEXT_OPTIONS_NONE, float alpha = 1.0f);
			void draw(string font, float size, string str, point<float> pos, canvas_id window, const color_f& color, uint32 edge_px, const color_f& edge_color, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS::D2D1_DRAW_TEXT_OPTIONS_NONE, float alpha = 1.0f, const string& key = "");
			point<float> get_size(string str, canvas_id window);
			point<float> get_size_edged(const string& font, const string& str, float size, uint32 edge_width, const string& key);
			void free();
		}
	}
}
