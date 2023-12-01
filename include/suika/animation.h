// -----------------------------------------------------------
// 
// animation
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
#include "rect.h"

namespace suika {
	/// <summary>
	/// アニメーションを再生するクラス
	/// </summary>
	class animation : public detail::ishape<animation> {
	protected:
		point<bool> _turn;
		point<float> _size = { 64,64 }, _draw_size = { 64,64 }, _region_lt = { 0,0 }, _region_rb = { 1,1 };
		point<uint> _div = { 1,1 };
		std::vector<uint> _pattern;
		std::vector<double> _interval;
		double dt = 0;
		uint _index = 0;
		string _path;
		bool _is_loop = true, _is_finished = false;

		point<float> _uv_lt = { 0,0 }, _uv_rb = { 1,1 };
		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		animation() = default;

		/// <summary>
		/// テクスチャを作成
		/// </summary>
		/// <param name="path">テクスチャのパス</param>
		/// <param name="div">分割数</param>
		animation(string path, const point<uint>& div);

		/// <summary>
		/// テクスチャを作成
		/// </summary>
		/// <param name="path">テクスチャのパス</param>
		/// <param name="div">分割数</param>
		/// <param name="region_lt">テクスチャの領域の左上</param>
		/// <param name="region_rb">テクスチャの領域の右下</param>
		animation(string path, const point<uint>& div, const point<float>& region_lt, const point<float>& region_rb);

		/// <summary>
		/// テクスチャを反転させる
		/// </summary>
		/// <param name="turn">各方向の反転</param>
		virtual animation turned(const point<bool>& turn)&&;

		/// <summary>
		/// テクスチャを反転させる
		/// </summary>
		/// <param name="turn">各方向の反転</param>
		virtual animation& turned(const point<bool>& turn)&;

		/// <summary>
		/// アニメーションのパターンを設定する
		/// </summary>
		/// <param name="pattern">パターンの示した配列</param>
		/// <param name="interval">切り替えの間隔を示した配列</param>
		/// <param name="loop">アニメーションを繰り返すか</param>
		virtual animation patterned(const std::vector<uint>& pattern, const std::vector<double>& interval, bool loop = true)&&;

		/// <summary>
		/// アニメーションのパターンを設定する
		/// </summary>
		/// <param name="pattern">パターンの示した配列</param>
		/// <param name="interval">切り替えの間隔を示した配列</param>
		/// <param name="loop">アニメーションを繰り返すか</param>
		virtual animation& patterned(const std::vector<uint>& pattern, const std::vector<double>& interval, bool loop = true)&;

		/// <summary>
		/// アニメーションのパターンを設定する
		/// </summary>
		/// <param name="pattern">パターンの示した配列</param>
		/// <param name="interval">切り替えの間隔</param>
		/// <param name="loop">アニメーションを繰り返すか</param>
		virtual animation patterned(const std::vector<uint>& pattern, double interval = 1, bool loop = true)&&;

		/// <summary>
		/// アニメーションのパターンを設定する
		/// </summary>
		/// <param name="pattern">パターンの示した配列</param>
		/// <param name="interval">切り替えの間隔</param>
		/// <param name="loop">アニメーションを繰り返すか</param>
		virtual animation& patterned(const std::vector<uint>& pattern, double interval = 1, bool loop = true)&;

		/// <summary>
		/// アニメーションを更新する
		/// </summary>
		/// <param name="t">変化時間</param>
		virtual void updated(double t);

		/// <summary>
		/// アニメーションのインデックスを設定する
		/// </summary>
		/// <param name="index">インデックス</param>
		virtual void indexed(uint index);

		/// <summary>
		/// 再生中のアニメーションのインデックスを取得
		/// </summary>
		/// <returns>インデックス</returns>
		virtual uint index() const;

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
		/// アニメーションの再生が終了したか取得
		/// </summary>
		/// <returns>アニメーションの再生が終了したか</returns>
		bool finished() const;

		/// <summary>
		/// テクスチャの領域を示す矩形を取得する
		/// </summary>
		/// <returns>テクスチャの領域を示す矩形</returns>
		rect rect() const;

		/// <summary>
		/// テクスチャを描画する
		/// </summary>
		virtual void draw() override;
	};
}
