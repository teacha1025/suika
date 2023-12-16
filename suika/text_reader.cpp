// -----------------------------------------------------------
// 
// text reader
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
#define _CRT_SECURE_NO_WARNINGS
#include <filesystem>

#include "../include/suika/text_reader.h"
#include "../include/suika/filesystem.h"

namespace suika {
	namespace filesystem {
		static constexpr string_view nl(new_line n) {
			switch (n) {
				case new_line::crlf: return U"\r\n";
				case new_line::lf: return U"\n";
				case new_line::cr: return U"\r";
			}
			return U"";
		}

		text_reader::text_reader(path_type path, encode encode, new_line nl) {
			_path = path;

			_file.open(path.to_wstring(), std::ios::in | std::ios::binary);
			
			if (!_file) {
				return;
			}

			_encode = encode;

			_new_line = nl;
		}
		text_reader::~text_reader() {
			_file.close();
		}

		string text_reader::read() {
			//std::vector<char> ret;
			//std::vector<char> buf;
			//ret.reserve(16 * 1024);
			/*buf.reserve(4 * 1024);
			while (!_file.eof()) {
				buf.clear();
				_file.read(buf.data(), buf.capacity());
				std::copy(ret.begin(), ret.end(), std::back_inserter(buf));
			}*/
			std::vector<char> ret{ std::istreambuf_iterator<char>(_file), std::istreambuf_iterator<char>() };
			switch (_encode) {
				case encode::shift_jis: {
					return string(std::string(reinterpret_cast<const char*>(ret.data()), ret.size() / sizeof(char)));
				}
				case encode::utf8: {
					return string(std::u8string(reinterpret_cast<const char8_t*>(ret.data()), ret.size() / sizeof(char8_t)));
				}
				case encode::utf16: {
					return string(std::u16string(reinterpret_cast<const char16_t*>(ret.data()), ret.size() / sizeof(char16_t)));
				}
			}
			return "";
		}
		std::vector<string> text_reader::readln() {
			auto s = split(replace_string(read().to_u32string(), nl(_new_line).to_u32string(), U"\n"), U'\n');
			std::vector<string> ret;
			for (auto& i : s) {
				ret.push_back(string(i));
			}
			return ret;
		}
	}
}