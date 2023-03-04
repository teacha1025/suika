#pragma once
#include <dwrite.h>
#include "../../include/suika/string.h"
#include "../../include/suika/color.h"
#include "../../include/suika/point.h"

namespace suika {
	namespace d3d{
		namespace dwrite {
			struct font_data {
				string font;					// �t�H���g��
				//IDWriteFontCollection* fontCollection;		// �t�H���g�R���N�V����
				DWRITE_FONT_WEIGHT fontWeight;			// �t�H���g�̑���
				DWRITE_FONT_STYLE fontStyle;			// �t�H���g�X�^�C��
				DWRITE_FONT_STRETCH fontStretch;		// �t�H���g�̕�
				float fontSize;					// �t�H���g�T�C�Y
				string localeName;			// ���P�[����
				DWRITE_TEXT_ALIGNMENT textAlignment;		// �e�L�X�g�̔z�u
				color Color;				// �t�H���g�̐F
			};
		}
	}
}