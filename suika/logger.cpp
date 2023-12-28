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

#define NOMINMAX
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <format>
#include <chrono>
#include <Windows.h>
#include <system_error>
#include <mutex>

#include "../include/suika/def.h"
#include "../include/suika/logger.h"

namespace suika {
	logger::logger() {
		_startup_count = std::chrono::system_clock::now();
		fp			 = nullptr;
	}

	logger::~logger() {
		if (!flag)
			return;
		if (fp != nullptr) {
			fclose(fp);
		}
	}

	bool logger::init() {
		if (!flag)
			return 0;

		namespace chrono		 = std::chrono;
		chrono::local_seconds lt = chrono::zoned_seconds { "Asia/Tokyo", chrono::floor<chrono::seconds>(chrono::system_clock::now()) }.get_local_time();

		auto e = fopen_s(&fp, filename.c_str(), "w");
		if (e != 0) {
			while (true) {
				OutputDebugString((L"ログファイルの作成に失敗"));
				auto id = MessageBox(NULL, (L"ログファイルを作成できません。\nフォルダが書き込み禁止になってませんか？"), (L"ログファイルの作成に失敗"), MB_ABORTRETRYIGNORE | MB_ICONERROR);
				if (id == IDABORT) {
					return false;
				}
				else if (id == IDRETRY || id == IDTRYAGAIN) {
					e = fopen_s(&fp, filename.c_str(), "w");
					if (e != 0)
						continue;
					else {
						add(std::format("起動時刻 {:%Y/%m/%d %X}  Lib version: {}", lt, suika::VERSION_S));
						return true;
					}
				}
				else if (id == IDIGNORE) {
					flag = false;
					return true;
				}
			}
		}
		else {
			add(std::format("起動時刻 {:%Y/%m/%d %X}  Lib version: {}", lt, suika::VERSION_S));
			return true;
		}
	}

	void logger::set(bool output_flag, const string& name) {
		filename	   = name.to_string();
		this->flag	 = output_flag;
	}

	std::mutex mtx;
	void	   logger::add(const string& str) {
		std::lock_guard<std::mutex> lock(mtx);
		static string log;
		auto			   t = std::chrono::system_clock::now();
		auto			   d = std::chrono::duration_cast<std::chrono::milliseconds>(t - _startup_count);
		log = std::format("[{}]\t{}\n", d.count(), str.to_string());
		OutputDebugString(log.to_wstring().c_str());
		if (!flag)
			return;
		if (fp == nullptr) {
			if (init() != 0)
				return;
		}
		if (fp != nullptr)
			fprintf(fp, log.to_string().c_str());
	}

	void logger::exception(const string& str) {
		add(L"Exception: " + str.to_wstring());
	}

	void logger::critical(const string& str) {
		add(L"Critical: " + str.to_wstring());
	}

	void logger::error(const string& str) {
		add(L"Error: " + str.to_wstring());
	}

	void logger::warn(const string& str) {
		add(L"Warning: " + str.to_wstring());
	}

	void logger::info(const string& str) {
		add(L"Info: " + str.to_wstring());
	}

	void logger::debug(const string& str) {
		add(L"Debug: " + str.to_wstring());
	}

	void logger::result(long result) {
		switch (result) {
		case S_OK:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "成功"));
			break;
		}
		case E_ABORT:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "操作の中断"));
			break;
		}
		case E_ACCESSDENIED:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "アクセスの拒否"));
			break;
		}
		case E_FAIL:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "失敗"));
			break;
		}
		case E_HANDLE:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "無効なハンドル"));
			break;
		}
		case E_INVALIDARG:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "引数が無効"));
			break;
		}
		case E_NOINTERFACE:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "サポートされていないインターフェイス"));
			break;
		}
		case E_NOTIMPL:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "未実装"));
			break;
		}
		case E_OUTOFMEMORY:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "メモリ割り当てに失敗"));
			break;
		}
		case E_POINTER:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "無効なポインタ"));
			break;
		}
		case E_UNEXPECTED:
		{
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, "予期しないエラー"));
			break;
		}
		default: {
			add(std::format("\t\tコード:{0:#x} {1}", (long)result, std::system_category().message(result)));
			break;
		}
		}
	}

	string logger::to_string() const {
		return std::format("logfile:{}", filename);
	}

	logger log;
} // namespace suika
