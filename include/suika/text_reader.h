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
#include <fstream>

#include "def.h"
#include "string.h"
#include "filesystem.h"

namespace suika {
	namespace filesystem {
		
		class text_reader {
		private:
			path_type _path;
			encode _encode = encode::utf8;
			new_line _new_line = new_line::crlf;

			//std::unique_ptr<FILE, detail::file_deleter> _file;
			std::ifstream _file;
		public:
			text_reader(path_type path, encode encode = encode::utf8, new_line nl = new_line::crlf);
			~text_reader();

			string read();
			std::vector<string> readln();
		};
	}
} // namespace suika