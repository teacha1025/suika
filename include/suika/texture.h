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
		texture(string path) :path(path) {
			_tex = d3d::texture::texture(path);
			_size = _tex.size;
			_shaders = { "texture", "texture" };
		}

		virtual texture turned(const point<bool>& turn)&&;
		virtual texture& turned(const point<bool>& turn)&;

		point<bool> turn() const;
		virtual void draw() override;
	};
}
#endif