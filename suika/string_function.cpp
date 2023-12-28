// -----------------------------------------------------------
// 
// string function
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

#include <sstream>

#include "../include/suika/def.h"
#include "../include/suika/string_function.h"

namespace suika {
	std::vector<std::u8string> split(const std::u8string& s, char8 split_char, bool is_contain_lastempty) {
		size_t first = 0;
		size_t last = s.find_first_of(split_char);

		std::vector<std::u8string> result;

		while (first < s.size()) {
			std::u8string subStr(s, first, last - first);

			result.push_back(subStr);

			first = last + 1;
			last = s.find_first_of(split_char, first);

			if (last == std::u8string::npos) {
				last = s.size();
			}
		}
		if (first == s.size() && is_contain_lastempty) {
			result.push_back(u8"");
		}

		return result;
	}

	std::vector<std::u16string> split(const std::u16string& s, char16 split_char, bool is_contain_lastempty) {
		size_t first = 0;
		size_t last = s.find_first_of(split_char);

		std::vector<std::u16string> result;

		while (first < s.size()) {
			std::u16string subStr(s, first, last - first);

			result.push_back(subStr);

			first = last + 1;
			last = s.find_first_of(split_char, first);

			if (last == std::u16string::npos) {
				last = s.size();
			}
		}
		if (first == s.size() && is_contain_lastempty) {
			result.push_back(u"");
		}

		return result;
	}

	std::vector<std::u32string> split(const std::u32string& s, char32 split_char, bool is_contain_lastempty) {
		size_t first = 0;
		size_t last = s.find_first_of(split_char);

		std::vector<std::u32string> result;

		while (first < s.size()) {
			std::u32string subStr(s, first, last - first);

			result.push_back(subStr);

			first = last + 1;
			last = s.find_first_of(split_char, first);

			if (last == std::string::npos) {
				last = s.size();
			}
		}
		if (first == s.size() && is_contain_lastempty) {
			result.push_back(U"");
		}

		return result;
	}

	std::vector<std::string> split(const std::string& s, char split_char, bool is_contain_lastempty) {
		size_t first = 0;
		size_t last = s.find_first_of(split_char);

		std::vector<std::string> result;

		while (first < s.size()) {
			std::string subStr(s, first, last - first);

			result.push_back(subStr);

			first = last + 1;
			last = s.find_first_of(split_char, first);

			if (last == std::string::npos) {
				last = s.size();
			}
		}
		if (first == s.size() && is_contain_lastempty) {
			result.push_back("");
		}

		return result;
	}

	std::vector<std::wstring> split(const std::wstring& s, wchar_t split_char, bool is_contain_lastempty) {
		size_t first = 0;
		size_t last = s.find_first_of(split_char);

		std::vector<std::wstring> result;

		while (first < s.size()) {
			std::wstring subStr(s, first, last - first);

			result.push_back(subStr);

			first = last + 1;
			last = s.find_first_of(split_char, first);

			if (last == std::wstring::npos) {
				last = s.size();
			}
		}
		if (first == s.size() && is_contain_lastempty) {
			result.push_back(L"");
		}

		return result;
	}

	std::u8string replace_string(std::u8string source, const std::u8string& old_val, const std::u8string& new_val) {
		std::u8string::size_type Pos(source.find(old_val));

		while (Pos != std::u8string::npos) {
			source.replace(Pos, old_val.length(), new_val);
			Pos = source.find(old_val, Pos + new_val.length());
		}

		return source;
	}

	std::u16string replace_string(std::u16string source, const std::u16string& old_val, const std::u16string& new_val) {
		std::u16string::size_type Pos(source.find(old_val));

		while (Pos != std::u16string::npos) {
			source.replace(Pos, old_val.length(), new_val);
			Pos = source.find(old_val, Pos + new_val.length());
		}

		return source;
	}

	std::u32string replace_string(std::u32string source, const std::u32string& old_val, const std::u32string& new_val) {
		std::u32string::size_type Pos(source.find(old_val));

		while (Pos != std::u32string::npos) {
			source.replace(Pos, old_val.length(), new_val);
			Pos = source.find(old_val, Pos + new_val.length());
		}

		return source;
	}

	std::string replace_string(std::string source, const std::string& old_val, const std::string& new_val) {
		std::string::size_type Pos(source.find(old_val));

		while (Pos != std::string::npos) {
			source.replace(Pos, old_val.length(), new_val);
			Pos = source.find(old_val, Pos + new_val.length());
		}

		return source;
	}

	std::wstring replace_string(std::wstring source, const std::wstring& old_val, const std::wstring& new_val) {
		std::wstring::size_type Pos(source.find(old_val));

		while (Pos != std::wstring::npos) {
			source.replace(Pos, old_val.length(), new_val);
			Pos = source.find(old_val, Pos + new_val.length());
		}

		return source;
	}

}
