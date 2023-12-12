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
				if (file)
					fclose(file);
			}
		};
	}
	namespace filesystem {
		enum class encode {
			shift_jis,
			utf8,
			utf16,
			//utf32,
		};

		enum class new_line {
			crlf,
			lf,
			cr,
		};

		bool exists(path_type path);

		path_type current_path();

		//ディレクトリ内のファイルを列挙する
		std::vector<path_type> enumerate_files(path_type path);
	}
} // namespace suika