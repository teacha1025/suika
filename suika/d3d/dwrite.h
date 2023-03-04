#pragma once
#include <dwrite.h>
#include "../../include/suika/string.h"
#include "../../include/suika/color.h"
#include "../../include/suika/point.h"

namespace suika {
	namespace d3d{
		namespace dwrite {
			struct font_data {
				string font;					// フォント名
				//IDWriteFontCollection* fontCollection;		// フォントコレクション
				DWRITE_FONT_WEIGHT fontWeight;			// フォントの太さ
				DWRITE_FONT_STYLE fontStyle;			// フォントスタイル
				DWRITE_FONT_STRETCH fontStretch;		// フォントの幅
				float fontSize;					// フォントサイズ
				string localeName;			// ロケール名
				DWRITE_TEXT_ALIGNMENT textAlignment;		// テキストの配置
				color Color;				// フォントの色
			};
		}
	}
}