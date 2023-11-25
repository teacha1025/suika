// -----------------------------------------------------------
// 
// system
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

#include <chrono>

#include "string.h"

namespace suika {
	namespace sys {
		/// <summary>
		/// フレームを更新する
		/// </summary>
		/// <returns></returns>
		bool update();

		/// <summary>
		/// 次フレームでプログラムを終了する
		/// </summary>
		void exit();

		/// <summary>
		/// プログラムを指定時間停止する
		/// </summary>
		/// <param name="t">停止時間</param>
		/// <remarks>プログラムすべての処理が停止します。</remarks>
		void sleep(std::chrono::nanoseconds t);

		/// <summary>
		/// プログラムを指定まで時間停止する
		/// </summary>
		/// <param name="t">再開時刻</param>
		/// <remarks>プログラムすべての処理が停止します。</remarks>
		void wait(std::chrono::system_clock::time_point t);

		/// <summary>
		/// フレームレートを取得
		/// </summary>
		/// <returns>現在のフレームレート</returns>
		float fps();

		/// <summary>
		/// 前のフレームからの経過時間を取得
		/// </summary>
		/// <returns>経過時間(秒)</returns>
		double delta();

		/// <summary>
		/// 前のフレームからの経過時間を取得
		/// </summary>
		/// <returns>経過時間(ナノ秒)</returns>
		long long delta_nano();
	}
}
