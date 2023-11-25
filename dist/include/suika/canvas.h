// -----------------------------------------------------------
// 
// canvas.
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
#include "color.h"
#include "point.h"

namespace suika {
	struct canvas {
		using canvas_id = uint;
		canvas_id id;
		color bg_color;

		/// <summary>
		/// キャンバスを作成する
		/// </summary>
		/// <param name="size">キャンバスサイズ</param>
		/// <param name="top">トップ座標</param>
		/// <param name="hWnd">ウィンドウID</param>
		/// <param name="bg">塗りつぶしの色</param>
		canvas(const point<float>& size, const point<float>& top, HWND hWnd, const color& bg);

		/// <summary>
		/// キャンバスをクリアする
		/// </summary>
		void clear() const;

		/// <summary>
		/// 描画先のキャンバスに設定する
		/// </summary>
		void set() const;

		/// <summary>
		/// キャンバスをウィンドウに転写する
		/// </summary>
		/// <param name="vsync">垂直同期をするか</param>
		void present(bool vsync = false) const;
	};

	/// <summary>
	/// キャンバスを作成する
	/// </summary>
	/// <param name="size">キャンバスサイズ</param>
	/// <param name="top">トップ座標</param>
	/// <param name="hWnd">ウィンドウID</param>
	/// <param name="fillcolor">塗りつぶしの色</param>
	/// <returns>作成されたキャンバス</returns>
	std::shared_ptr<canvas> make_canvas(const point<float>& size, const point<float>& top, HWND hWnd, const color& fillcolor);
}