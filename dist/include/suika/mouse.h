// -----------------------------------------------------------
// 
// mouse.
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

#include "point.h"
#include "window.h"
#include "input_base.h"

namespace suika {
	/// <summary>
	/// 内部的な実装
	/// </summary>
	namespace detail {
		/// <summary>
		/// マウス
		/// </summary>
		class mouse : public input_base {
		public:
			/// <summary>
			/// マウスキーの作成
			/// </summary>
			/// <param name="code">マウスコード</param>
			/// <param name="name">マウスの名前</param>
			mouse(unsigned int code, string name);

			/// <summary>
			/// デフォルト入力
			/// </summary>
			mouse() {}

			/// <summary>
			/// マウスの更新
			/// </summary>
			void update();
		};
	}
	/// <summary>
	/// キー入力の定義及び関数
	/// </summary>
	namespace mouse {
		/// <summary>
		/// 左ボタン
		/// </summary>
		extern detail::mouse Left;

		/// <summary>
		/// 中ボタン
		/// </summary>
		extern detail::mouse Middle;

		/// <summary>
		/// 右ボタン
		/// </summary>
		extern detail::mouse Right;

		extern detail::mouse Button4;
		extern detail::mouse Button5;
		extern detail::mouse Button6;
		extern detail::mouse Button7;
		extern detail::mouse Button8;

		/// <summary>
		/// カーソルの種類
		/// </summary>
		enum cursor {
			//! 標準
			icon,
			//! 標準
			arrow,
			//! 上向き矢印
			up_arrow,
			//! Iマーク
			ibeam,
			//! 十字
			cross,
			//! 人差し指
			hand,
			//! 禁止
			no,
			//! 上下矢印
			resize_NS,
			//! 左右矢印
			resize_WE,
			//! 右上と左下矢印
			resize_NWSE,
			//! 左上と右下矢印
			resize_NESW,
			//! 十字矢印
			resize_all,
			//! ヘルプ
			help,
			//! ピンマーク
			pin,
			//! 人
			person,
			//! ぐるぐる(砂時計)
			wait,
			//! 矢印とぐるぐる
			appstarting
		};

		/// <summary>
		/// マウスカーソルの位置を取得
		/// </summary>
		/// <param name="id">ウィンドウのID</param>
		/// <returns>カーソルの位置</returns>
		point<int> position(window::id id = window::default_id);

		/// <summary>
		/// マウスカーソルの位置を設定
		/// </summary>
		/// <param name="p">位置</param>
		/// <param name="id">ウィンドウID</param>
		/// <param name="flag">ウィンドウがアクティブの時だけカーソルを設定する</param>
		void position(const point<int>& p, window::id id = window::default_id, bool flag = true);

		/// <summary>
		/// カーソル移動量を取得
		/// </summary>
		/// <param name="id">ウィンドウID</param>
		/// <returns>１フレームのカーソル移動量</returns>
		point<int> delta_position(window::id id = window::default_id);

		/// <summary>
		/// ホイール回転量を取得
		/// </summary>
		/// <returns>１フレームのホイール回転量</returns>
		int wheel();

		/// <summary>
		/// カーソルの見た目を変更する
		/// </summary>
		/// <param name="style">カーソルの種類</param>
		void style(cursor style);
	}
}