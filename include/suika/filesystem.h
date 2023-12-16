// -----------------------------------------------------------
// 
// filesystem
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

#include <memory>
#include <vector>

#include "def.h"
#include "string.h"

namespace suika {
	namespace detail {
		struct file_deleter {
			void operator()(FILE* file) const noexcept {
				if (file != nullptr)
					fclose(file);
			}
		};
	}

	/// <summary>
	/// ファイル操作に関する関数、クラス群
	/// </summary>
	namespace filesystem {
		/// <summary>
		/// エンコードの種類
		/// </summary>
		enum class encode {
			//! Shift-JIS文字コード(cp932)
			shift_jis,
			//! UTF-8(BOMあり)
			utf8,
			//! UTF16(LE)
			utf16,
			//utf32,
		};

		enum class new_line {
			//! CRLF
			crlf,
			//! LF
			lf,
			//! CR
			cr,
		};

		/// <summary>
		/// ファイルが存在するかを取得
		/// </summary>
		/// <param name="path">ファイルのパス</param>
		/// <returns>存在するかどうか</returns>
		bool exists(path_type path);

		/// <summary>
		/// 現在のディレクトリを取得
		/// </summary>
		/// <returns>実行ファイルがあるディレクトリへのパス</returns>
		path_type current_path();

		/// <summary>
		/// ディレクトリ内の要素を列挙する
		/// </summary>
		/// <param name="path">ディレクトリのパス</param>
		/// <returns>ディレクトリ内のファイル、フォルダ名</returns>
		std::vector<path_type> enumerate_files(path_type path);
	}
} // namespace suika