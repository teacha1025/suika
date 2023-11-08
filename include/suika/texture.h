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
#include "vertex.h"
#include "point.h"
#include "../../suika/d3d/texture.hpp"

namespace suika {
	/// <summary>
	/// テクスチャ描画に関するクラス
	/// </summary>
	class texture : public detail::ishape<texture> {
	private:
		point<bool> _turn;
		point<float> _size = { 64,64 };
		string path;
		d3d::texture::texture _tex;
	protected:
		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// テクスチャを作成
		/// </summary>
		/// <param name="path">テクスチャのパス</param>
		texture(string path) :path(path) {
			_tex = d3d::texture::texture(path);
			_size = _tex.size;
			_shaders = { TEXTURE_VERTEX, TEXTURE_PIXEL };
		}

		/// <summary>
		/// テクスチャを反転させる
		/// </summary>
		/// <param name="turn">各方向の反転</param>
		virtual texture turned(const point<bool>& turn)&&;
		/// <summary>
		/// テクスチャを反転させる
		/// </summary>
		/// <param name="turn">各方向の反転</param>
		virtual texture& turned(const point<bool>& turn)&;

		/// <summary>
		/// テクスチャ反転を取得
		/// </summary>
		/// <param name="turn">各方向の反転</param>
		point<bool> turn() const;
		/// <summary>
		/// テクスチャの大きさを取得
		/// </summary>
		/// <returns>テクスチャの大きさ</returns>
		point<float> size() const;
		/// <summary>
		/// テクスチャを描画する
		/// </summary>
		virtual void draw() override;
	};
}
#endif