// -----------------------------------------------------------
// 
// window
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

		/// <summary>
		/// メインウィンドウのID
		/// </summary>
		extern id default_id;

		/// <summary>
		/// ウィンドウを作成する
		/// </summary>
		/// <param name="size">ウィンドウサイズ</param>
		/// <param name="rate">ウィンドウの拡大率</param>
		/// <param name="bg">背景色</param>
		/// <param name="title">ウィンドウのタイトル</param>
		/// <param name="vsync">垂直同期を使用するか</param>
		/// <returns>作成したウィンドウのID</returns>
		id create(const point<uint>& size, point<double> rate, const color& bg, const string& title, bool vsync);

		/// <summary>
		/// ウィンドウを作成する
		/// </summary>
		/// <param name="size">ウィンドウサイズ</param>
		/// <param name="rate">ウィンドウの拡大率</param>
		/// <param name="bg">背景色</param>
		/// <param name="title">ウィンドウのタイトル</param>
		/// <param name="vsync">垂直同期を使用するか</param>
		/// <param name="pos">ウィンドウの位置</param>
		/// <returns>作成したウィンドウのID</returns>
		id create(const point<uint>& size, point<double> rate, const color& bg, const string& title, bool vsync, const point<uint>& pos);

		/// <summary>
		/// プロセスを処理する
		/// </summary>
		/// <returns>処理に成功したか</returns>
		bool process();

		/// <summary>
		/// ウィンドウに表示する
		/// </summary>
		void flip();

		/// <summary>
		/// ウィンドウをクリアする
		/// </summary>
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
		/// 垂直同期の設定
		/// </summary>
		/// <param name="flag">垂直同期をするか</param>
		/// <param name="id">ウィンドウ識別ID</param>
		void vsync(bool flag, id id = default_id);


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
		/// 垂直同期設定の取得
		/// </summary>
		/// <param name="id">ウィンドウ識別ID</param>
		/// <returns>垂直同期をしているか</returns>
		bool vsync(id id = default_id);

		/// <summary>
		/// 作成されたウィンドウIDをすべて取得する
		/// </summary>
		/// <returns></returns>
		std::vector<id> all_id();

		/// <summary>
		/// ウィンドウの描画キャンバスを取得
		/// </summary>
		/// <param name="id">ウィンドウ識別ID</param>
		/// <returns>ウィンドウのキャンバス</returns>
		std::shared_ptr<suika::canvas> canvas(id id = default_id);
	}
} // namespace suika
