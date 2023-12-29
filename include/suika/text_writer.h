// -----------------------------------------------------------
// 
// text writer
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
#include <fstream>

#include "def.h"
#include "string.h"
#include "filesystem.h"

namespace suika {
	/// <summary>
	/// ファイル操作に関する関数、クラス群
	/// </summary>
	namespace filesystem {
		/// <summary>
		/// 文字列書き出し
		/// </summary>
		class text_writer {
		private:
			path_type _path;
			encode _encode = encode::utf8;
			new_line _new_line = new_line::crlf;

			//std::unique_ptr<FILE, detail::file_deleter> _file;
			std::ofstream _file;
		public:
			/// <summary>
			/// ライターの作成
			/// </summary>
			/// <param name="path">ファイルへのパス</param>
			/// <param name="encode">書き込み時の文字列エンコード</param>
			/// <param name="nl">改行文字の種類</param>
			text_writer(path_type path, encode encode = encode::utf8, new_line nl = new_line::crlf);
			
			/// <summary>
			/// デストラクタ
			/// </summary>
			~text_writer();

			/// <summary>
			/// 文字列を書き込む
			/// </summary>
			/// <param name="text">書き込む文字列</param>
			void write(string text);

			/// <summary>
			/// 行に文字列を書き込む
			/// </summary>
			/// <param name="text">書き込む文字列</param>
			void writeln(string text);
		};
	}
} // namespace suika
