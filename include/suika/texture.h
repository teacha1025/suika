/**
* @file texture.h
* @brief �e�N�X�`���֌W
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_TEXTURE
#define _SK_TEXTURE
#include "def.h"
#include "base.h"
#include "draw.h"
#include "point.h"

namespace suika {
	/// <summary>
	/// �e�N�X�`���`��Ɋւ���N���X
	/// </summary>
	class texture : public detail::ishape<texture> {
	private:
		point<bool> _turn;
	public:

	};
}
#endif