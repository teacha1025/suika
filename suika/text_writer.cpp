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
			const wchar_t* opt = L"w";

			switch (encode) {
				case encode::shift_jis: opt = L"w, ccs=SHIFT_JIS"; break;
				case encode::utf8: opt = L"w, ccs=UTF-8"; break;
				case encode::utf16: opt = L"w, ccs=UTF-16"; break;
				//case encode::utf32: opt = L"w, ccs=UTF-32"; break;
			}

			FILE* fp = new FILE();
			auto err = _wfopen_s(&fp, path.to_wstring().c_str(), opt);
			_file.reset(fp);
			if (err != 0) {
				return;
			}
			_encode = encode;
		}
		text_writer::~text_writer() {
		}

		void text_writer::write(string_view text) {
			switch (_encode) {
				case encode::shift_jis: {
					std::string s = text.to_string();
					fwrite(s.c_str(), sizeof(char), s.size(), _file.get());
					break;
				}
				case encode::utf8: {
					std::u8string s = text.to_utf8();
					fwrite(s.c_str(), sizeof(char8_t), s.size(), _file.get());
					break;
				}
				case encode::utf16: {
					std::wstring s = text.to_wstring();
					fwrite(s.c_str(), sizeof(wchar_t), s.size(), _file.get());
					break;
				}
			}
		}
		void text_writer::writeln(string_view text) {
			switch (_encode) {
				case encode::shift_jis: {
					std::string s = text.to_string();
					fwrite(s.c_str(), sizeof(char), s.size(), _file.get());
					fwrite(nl(_new_line).to_string().c_str(), sizeof(char), nl(_new_line).size(), _file.get());
					break;
				}
				case encode::utf8: {
					std::u8string s = text.to_utf8();
					fwrite(s.c_str(), sizeof(char8_t), s.size(), _file.get());
					fwrite(nl(_new_line).to_utf8().c_str(), sizeof(char8_t), nl(_new_line).size(), _file.get());
					break;
				}
				case encode::utf16: {
					std::wstring s = text.to_wstring();
					fwrite(s.c_str(), sizeof(wchar_t), s.size(), _file.get());
					fwrite(nl(_new_line).to_wstring().c_str(), sizeof(wchar_t), nl(_new_line).size(), _file.get());
					break;
				}
			}
		}
	}
}