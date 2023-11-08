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
		void clear();

		/// <summary>
		/// 描画先のキャンバスに設定する
		/// </summary>
		void set();

		/// <summary>
		/// キャンバスをウィンドウに転写する
		/// </summary>
		/// <param name="vsync">垂直同期をするか</param>
		void present(bool vsync = false);
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