/** @example{lineno} animator.hpp
 * アニメーションのサンプル
*/

// -----------------------------------------------------------
// 
// animator
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

#include <unordered_map>
#include <functional>

#include "def.h"
#include "base.h"
#include "draw.h"
#include "vertex.h"
#include "point.h"
#include "animation.h"


namespace suika {
	/// <summary>
	/// アニメーション再生を管理するクラス
	/// </summary>
	class animator : public detail::ishape<animator> {
	private:
		struct hash_pair {
			template<class T1, class T2>
			size_t operator()(const std::pair<T1, T2>& p) const {
				auto hash1 = std::hash<T1>{}(p.first);
				auto hash2 = std::hash<T2>{}(p.second);
				size_t seed = 0;
				seed ^= hash1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				seed ^= hash2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				return seed;
			}
		};

		animation _anm;
		struct pattern {
			std::vector<uint> pattern;
			double interval = 1;
			bool loop = true;
			uint next = 0;
			bool _smooth = false;
		};
		std::unordered_map<uint, pattern> _pattern;

		std::unordered_map<std::pair<uint, uint>, std::pair<std::function<bool()>, bool>, hash_pair> _condition;

		uint _key = 0;

		point<bool> _turn;

		virtual std::vector<vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// 新しいアニメーターを作成する
		/// </summary>
		animator() = default;

		/// <summary>
		/// 新しいアニメーターを作成する
		/// </summary>
		/// <param name="path">テクスチャのパス</param>
		/// <param name="div">縦横の分割数</param>
		animator(string path, const point<uint>& div);

		/// <summary>
		/// 新しいアニメーターを作成する
		/// </summary>
		/// <param name="path">テクスチャのパス</param>
		/// <param name="div">縦横の分割数</param>
		/// <param name="region_lt">テクスチャの左上のUV</param>
		/// <param name="region_rb">テクスチャの右下のUV</param>
		animator(string path, const point<uint>& div, const point<float>& region_lt, const point<float>& region_rb);

		/// <summary>
		/// アニメーションのパターンを追加する
		/// </summary>
		/// <param name="key">パターンの識別キー</param>
		/// <param name="pattern">再生の順番(画像の左上からZの順に1,2,...)</param>
		/// <param name="interval">次の画像に遷移するまでのカウント</param>
		/// <param name="resume">再生が終わったときに、次に再生されるパターンのキー</param>
		void add(uint key, std::vector<uint> pattern, double interval, uint next);

		/// <summary>
		/// アニメーションのパターンを追加する
		/// </summary>
		/// <param name="key">パターンの識別キー</param>
		/// <param name="pattern">再生の順番(画像の左上からZの順に1,2,...)</param>
		/// <param name="interval">次の画像に遷移するまでのカウント</param>
		void add(uint key, std::vector<uint> pattern, double interval);

		/// <summary>
		/// 特定条件でアニメーションを遷移させる
		/// </summary>
		/// <param name="from">遷移前のアニメーションのキー</param>
		/// <param name="to">遷移先のアニメーションのキー</param>
		/// <param name="cond">条件判定の関数</param>
		/// <param name="smooth">切り替えを滑らかに行うか</param>
		/// <remarks>condは、引数無しでboolを返えす関数</remarks>
		/// <remarks>スムーズな切り替えは簡易的なものであり、完全にスムーズに行えるわけではないです</remarks>
		void condition(uint from, uint to, std::function<bool()> cond, bool smooth = true);

		/// <summary>
		/// テクスチャ反転を取得
		/// </summary>
		/// <returns>各方向の反転</returns>
		animator& turned(const point<bool>& turn)&;

		/// <summary>
		/// テクスチャ反転を取得
		/// </summary>
		/// <returns>各方向の反転</returns>
		animator turned(const point<bool>& turn)&&;

		/// <summary>
		/// アニメーションを更新する
		/// </summary>
		/// <param name="t">変化時間</param>
		virtual void updated(double t);

		/// <summary>
		/// 再生するアニメーションのキーを設定する
		/// </summary>
		/// <param name="key">アニメーションのキー</param>
		void set(uint key);

		/// <summary>
		/// テクスチャの領域を示す矩形を取得する
		/// </summary>
		/// <returns>テクスチャの領域を示す矩形</returns>
		rect rect() const;

		/// <summary>
		/// アニメーションを描画する
		/// </summary>
		virtual void draw() override;
	};
}
