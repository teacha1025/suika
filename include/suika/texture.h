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

namespace suika {
	/// <summary>
	/// テクスチャ描画に関するクラス
	/// </summary>
	class texture : public detail::ishape<texture> {
	protected:
		point<bool> _turn;
		point<float> _size = { 64,64 }, _draw_size = { 64,64 };
		string _path;

		point<float> _uv_lt = { 0,0 }, _uv_rb = { 1,1 };
		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// テクスチャを作成
		/// </summary>
		/// <param name="path">テクスチャのパス</param>
		texture(string path);

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
