/**
* @file texture.h
* @brief テクスチャ関係
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
	/// テクスチャ描画に関するクラス
	/// </summary>
	class texture : public detail::ishape<texture> {
	private:
		point<bool> _turn;
		string path;
	public:
		virtual texture turned(const point<bool>& turn)&&;
		virtual texture& turned(const point<bool>& turn)&;

		point<bool> turn() const;
		virtual void draw() override;
	};
}
#endif