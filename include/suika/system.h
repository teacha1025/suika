/**
* @file system.h
* @brief システム関係
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_SYSTEM
#define _SK_SYSTEM
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
	}
}

#endif