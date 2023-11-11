/**
* @file logger.h
* @brief ログ関係
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_LOGGER
#define _SK_LOGGER
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "def.h"
#include "base.h"

namespace suika {
	/// <summary>
	/// ログ出力に関するクラス
	/// </summary>
	class logger: public detail::ibase {
		std::chrono::system_clock::time_point _startup_count;
		FILE* fp;
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
} // namespace suika
#endif