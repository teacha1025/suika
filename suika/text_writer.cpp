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
#define _CRT_SECURE_NO_WARNINGS
#include <filesystem>

#include "../include/suika/text_writer.h"
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

		text_writer::text_writer(path_type path, encode encode, new_line nl) {
			_path = path;

			_file.open(path.to_wstring(), std::ios::out | std::ios::binary);
			
			_encode = encode;
			_new_line = nl;
		}
		text_writer::~text_writer() {
			_file.close();
		}

		void text_writer::write(string text) {
			switch (_encode) {
				case encode::shift_jis: {
					auto s = text.to_string();
					_file.write(std::bit_cast<const char*>(s.c_str()), s.size() * sizeof(char));
					_file.flush();
					break;
				}
				case encode::utf8: {
					auto s = text.to_u8string();
					_file.write(std::bit_cast<const char*>(s.c_str()), s.size() * sizeof(char8_t));
					_file.flush();
					break;
				}
				case encode::utf16: {
					auto s = text.to_u16string();
					_file.write(std::bit_cast<const char*>(s.c_str()), s.size() * sizeof(char16_t));
					_file.flush();
					break;
				}
			}
		}
		void text_writer::writeln(string text) {
			auto n = nl(_new_line);
			switch (_encode) {
				case encode::shift_jis: {
					auto s = text.to_string();
					s += n.to_string();
					_file.write(std::bit_cast<const char*>(s.c_str()), s.size() * sizeof(char));
					_file.flush();
					break;
				}
				case encode::utf8: {
					auto s = text.to_u8string();
					s += n.to_u8string();
					_file.write(std::bit_cast<const char*>(s.c_str()), s.size() * sizeof(char8_t));
					_file.flush();
					break;
				}
				case encode::utf16: {
					auto s = text.to_u16string();
					s += n.to_u16string();
					_file.write(std::bit_cast<const char*>(s.c_str()), s.size() * sizeof(char16_t));
					_file.flush();
					break;
				}
			}
		}
	}
}
