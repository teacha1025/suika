// -----------------------------------------------------------
// 
// logger.
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

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <chrono>

#include "def.h"
#include "base.h"

namespace suika {
	/// <summary>
	/// ログ出力に関するクラス
	/// </summary>
	class logger: public detail::ibase {
		std::chrono::system_clock::time_point _startup_count;
		//FILE* fp;
		std::ofstream file;
		std::string filename = "Log.txt";
		bool flag	 = true;

	public:
		/// <summary>
		/// ログの作成
		/// </summary>
		logger();

		/// <summary>
		/// ログの解放
		/// </summary>
		~logger();

		/// <summary>
		/// ログファイルの作成
		/// </summary>
		/// <returns>ログファイルの作成に成功したか</returns>
		bool init();

		/// <summary>
		/// ログファイルの設定
		/// </summary>
		/// <param name="output_flag">ログ出力するか</param>
		/// <param name="name">ログファイルの名前</param>
		void set(bool output_flag, const string& name = "Log.txt");

		/// <summary>
		/// ログの追加
		/// </summary>
		/// <param name="str">出力する文字列</param>
		void add(const string& str);

		/// <summary>
		/// 例外について出力
		/// </summary>
		/// <param name="str">出力する文字列</param>
		void exception(const string& str);

		/// <summary>
		/// 致命的なエラーとして出力
		/// </summary>
		/// <param name="str">出力する文字列</param>
		void critical(const string& str);

		/// <summary>
		/// エラーとして出力
		/// </summary>
		/// <param name="str">出力する文字列</param>
		void error(const string& str);

		/// <summary>
		/// 警告として出力
		/// </summary>
		/// <param name="str">出力する文字列</param>
		void warn(const string& str);

		/// <summary>
		/// 情報を出力
		/// </summary>
		/// <param name="str">出力する文字列</param>
		void info(const string& str);

		/// <summary>
		/// デバッグとして出力
		/// </summary>
		/// <param name="str">出力する文字列</param>
		void debug(const string& str);

		/// <summary>
		/// windowsのHRESULTを出力
		/// </summary>
		/// <param name="result">HRESULTのエラーコード</param>
		void result(long result);

		/// <summary>
		/// ログに関する情報
		/// </summary>
		/// <returns>ログファイル名</returns>
		string to_string() const;
	};

	extern logger log;
}
