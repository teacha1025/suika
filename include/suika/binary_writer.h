// -----------------------------------------------------------
// 
// binary writer
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
#include "concepts.h"
#include "string.h"
#include "filesystem.h"

namespace suika {
	/// <summary>
/// ファイル操作に関する関数、クラス群
/// </summary>
	namespace filesystem {
		/// <summary>
		/// バイナリデータの書込み
		/// </summary>
		class binary_writer {
		private:
			path_type _path;

			std::unique_ptr<FILE, detail::file_deleter> _file;

			void close();
		public:
			/// <summary>
			/// ライターを作成
			/// </summary>
			/// <param name="path">書き込むファイルのパス</param>
			binary_writer(path_type path);
			binary_writer(const binary_writer&) = delete;

			/// <summary>
			///	ムーブコンストラクタ
			/// </summary>
			/// <param name="writer">ムーブ元</param>
			binary_writer(binary_writer&& writer);

			/// <summary>
			/// デストラクタ
			/// </summary>
			~binary_writer();

			/// <summary>
			/// バイナリを書き込む
			/// </summary>
			/// <param name="source">書き込むデータへのポインタ</param>
			/// <param name="size">書き込むサイズ</param>
			void write(void* source, size_t size);

			/// <summary>
			/// バイナリを書き込む
			/// </summary>
			/// <typeparam name="T">トリビアルコピー可能なデータ型</typeparam>
			/// <param name="source">書き込むデータ</param>
			template<concepts::trivially T>
			void write(T source) {
				write(&source, sizeof(T));
			}
		};
	}
} // namespace suika
