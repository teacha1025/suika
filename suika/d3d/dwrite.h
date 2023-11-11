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
			struct font_data {
				string font = "メイリオ";					// フォント名
				//IDWriteFontCollection* fontCollection;		// フォントコレクション
				DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL;			// フォントの太さ
				DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL;			// フォントスタイル
				DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL;		// フォントの幅
				float size = 20.0f;					// フォントサイズ
				string locale = L"";			// ロケール名
				DWRITE_TEXT_ALIGNMENT alignment = DWRITE_TEXT_ALIGNMENT_LEADING;		// テキストの配置
				color_f color = color_f(255, 255, 255, 255);				// フォントの色
			};

			void init(canvas_id window);
			void set(const font_data& font, canvas_id window);
			void set(const string& font, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch, float size, const string& locale, DWRITE_TEXT_ALIGNMENT alignment, const color_f& color, canvas_id window);
			void draw(string str, point<float> pos, canvas_id window, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS::D2D1_DRAW_TEXT_OPTIONS_NONE, float alpha = 1.0f);
			point<float> get_size(string str, canvas_id window);
			void free();
		}
	}
}