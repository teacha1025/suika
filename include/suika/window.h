#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_WINDOW
#define _SK_WINDOW
#include <windows.h>
#include <string>
#include "def.h"
#include "point.h"
#include "color.h"
#include "string.h"
#include "canvas.h"

namespace suika {
	namespace window {
		using id = HWND;
		extern id default_id;
		id create(const point<uint>& size, point<double> rate, const color& bg, const string& title);
		id create(const point<uint>& size, point<double> rate, const color& bg, const string& title, const point<uint>& pos);
		bool process();
		void flip();
		void clear();

		/// <summary>
		/// 画面の大きさを設定
		/// </summary>
		/// <param name="size">大きさ</param>
		/// <param name="id">ウィンドウ識別ID</param>
		void size(const point<uint>& size, id id = default_id);

		/// <summary>
		/// フルスクリーンの設定
		/// </summary>
		/// <param name="flag">フルスクリーンにするか</param>
		/// <param name="type">フルスクリーンの種類</param>
		//void fullscreen(bool flag, uint16 type = fullscreen_type::borderless | fullscreen_type::dotbydot);

		/// <summary>
		/// ウィンドウの拡大縮小
		/// </summary>
		/// <param name="rate">拡大比</param>
		/// <param name="id">ウィンドウ識別ID</param>
		void extends(point<double> rate, id id = default_id);

		/// <summary>
		/// 背景色の設定
		/// </summary>
		/// <param name="bg_color">背景色</param>
		/// <param name="id">ウィンドウ識別ID</param>
		void background(const color& bg_color, id id = default_id);

		/// <summary>
		/// ウィンドウタイトルの設定
		/// </summary>
		/// <param name="title">タイトルの文字列</param>
		/// <param name="id">ウィンドウ識別ID</param>
		void title(const string& title, id id = default_id);

		/// <summary>
		/// ウィンドウのキャンバスを変更
		/// </summary>
		/// <param name="canvas">新しいキャンバス</param>
		/// <param name="id">ウィンドウ識別ID</param>
		void canvas(const std::shared_ptr<suika::canvas>& canvas, id id = default_id);


		/// <summary>
		/// ウィンドウの大きさ取得
		/// </summary>
		/// <param name="id">ウィンドウ識別ID</param>
		/// <returns>ウィンドウの大きさ</returns>
		point<uint> size(id id = default_id);

		/// <summary>
		/// ウィンドウの中心座標を取得
		/// </summary>
		/// <param name="id">ウィンドウ識別ID</param>
		/// <returns>ウィンドウの中心座標</returns>
		point<double> center(id id = default_id);

		/// <summary>
		/// フルスクリーンかどうか取得
		/// </summary>
		/// <returns>フルスクリーンかどうか</returns>
		bool fullscreen();

		/// <summary>
		/// ウィンドウの拡大縮小の取得
		/// </summary>
		/// <param name="id">ウィンドウ識別ID</param>
		/// <returns>ウィンドウの拡大比</returns>
		point<double> extends(id id = default_id);

		/// <summary>
		/// ウィンドウの背景色の取得
		/// </summary>
		/// <param name="id">ウィンドウ識別ID</param>
		/// <returns>背景色</returns>
		color background(id id = default_id);

		/// <summary>
		/// ウィンドウのタイトルの取得
		/// </summary>
		/// <param name="id">ウィンドウ識別ID</param>
		/// <returns>ウィンドウタイトル</returns>
		string title(id id = default_id);

		/// <summary>
		/// ウィンドウの描画キャンバスを取得
		/// </summary>
		/// <param name="id">ウィンドウ識別ID</param>
		/// <returns>ウィンドウのキャンバス</returns>
		std::shared_ptr<suika::canvas> canvas(id id = default_id);

	}
} // namespace suika
#endif