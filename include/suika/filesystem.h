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

#include "def.h"
#include "string.h"

namespace suika {
	namespace detail{
		struct file_deleter {
			void operator()(FILE* file) const noexcept {
				fclose(file);
			}
		};
	}
	enum class encode {
		shift_jis,
		utf8,
		utf8_bom,
		utf16,
		utf16_bom,
		utf32,
		utf32_bom,
	};

	enum class new_line {
		crlf,
		lf,
		cr,
	};

	namespace filesystem {
		using path_type = string_view;
		bool exists(path_type path);

		class text_writer {
		private:
			path_type _path;
			encode _encode = encode::utf8;
			new_line _new_line = new_line::crlf;

			std::unique_ptr<FILE, detail::file_deleter> _file;
		public:
			text_writer(path_type path, encode encode);
			~text_writer();

			void write(string_view text);
			void writeln(string_view text);
		};
	}
} // namespace suika