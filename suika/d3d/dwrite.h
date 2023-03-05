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
				string font = "���C���I";					// �t�H���g��
				//IDWriteFontCollection* fontCollection;		// �t�H���g�R���N�V����
				DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL;			// �t�H���g�̑���
				DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL;			// �t�H���g�X�^�C��
				DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL;		// �t�H���g�̕�
				float fontSize = 20.0f;					// �t�H���g�T�C�Y
				string localeName = L"";			// ���P�[����
				DWRITE_TEXT_ALIGNMENT textAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;		// �e�L�X�g�̔z�u
				color Color = color(255, 255, 255, 255);				// �t�H���g�̐F
			};

			void init(canvas_id window);
			void set(const font_data& font, canvas_id window);
			void draw(string str, point<float> pos, canvas_id window, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS::D2D1_DRAW_TEXT_OPTIONS_NONE);
			void free();
		}
	}
}