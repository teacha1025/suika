// -----------------------------------------------------------
// 
// texture
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
	protected:
		point<bool> _turn;
		point<float> _size = { 64,64 };
		string path;
		d3d::texture::texture _tex;

		point<float> _uv_lt, _uv_rt, _uv_lb, _uv_rb;
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
		/// テクスチャのUV座標を設定する
		/// </summary>
		/// <param name="lt">左上</param>
		/// <param name="rb">右下</param>
		virtual texture uv(const point<float>& lt, const point<float>& rb)&&;

		/// <summary>
		/// テクスチャのUV座標を設定する
		/// </summary>
		/// <param name="lt">左上</param>
		/// <param name="rb">右下</param>
		virtual texture& uv(const point<float>& lt, const point<float>& rb)&;

		/// <summary>
		/// テクスチャのUV座標を設定する
		/// </summary>
		/// <param name="lt">左上</param>
		/// <param name="rt">右上</param>
		/// <param name="lb">左下</param>
		/// <param name="rb">右下</param>
		virtual texture uv(const point<float>& lt, const point<float>& rt, const point<float>& lb, const point<float>& rb)&&;

		/// <summary>
		/// テクスチャのUV座標を設定する
		/// </summary>
		/// <param name="lt">左上</param>
		/// <param name="rt">右上</param>
		/// <param name="lb">左下</param>
		/// <param name="rb">右下</param>
		virtual texture& uv(const point<float>& lt, const point<float>& rt, const point<float>& lb, const point<float>& rb)&;

		/// <summary>
		/// テクスチャ反転を取得
		/// </summary>
		/// <returns>各方向の反転</returns>
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
