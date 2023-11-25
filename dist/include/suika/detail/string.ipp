// -----------------------------------------------------------
// 
// string
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

#include <string>

#include "../codecvt.h"
#include "../string_function.h"
#include "string.h"

namespace suika {
#define TR(s) suika::to_u32string(s)
#define TRC(s) suika::to_u32string(s)
#define TRM to_u32string
#pragma region constructor
	inline string::string(const string& other, size_type pos):
		_string_data(string_type(other._string_data, pos)) {}

	inline string::string(const string& other, size_type pos, size_type count):
		_string_data(string_type(other._string_data, pos, count)) {}

	inline string::string(const utf8& other):
		_string_data(TR(other)) {}

	inline string::string(const utf8& other, size_type pos):
		_string_data(TR(std::u8string(other, pos))) {}

	inline string::string(const utf8& other, size_type pos, size_type count):
		_string_data(TR(std::u8string(other, pos, count))) {}

	inline string::string(const utf16& other):
		_string_data(TR(other)) {}

	inline string::string(const utf16& other, size_type pos):
		_string_data(TR(std::u16string(other, pos))) {}

	inline string::string(const utf16& other, size_type pos, size_type count):
		_string_data(TR(std::u16string(other, pos, count))) {}

	inline string::string(const utf32& other):
		_string_data(TR(other)) {}

	inline string::string(const utf32& other, size_type pos):
		_string_data(TR(std::u32string(other, pos))) {}

	inline string::string(const utf32& other, size_type pos, size_type count):
		_string_data(TR(std::u32string(other, pos, count))) {}

	inline string::string(const str& other):
		_string_data(TR(other)) {}

	inline string::string(const str& other, size_type pos):
		_string_data(TR(std::string(other, pos))) {}

	inline string::string(const str& other, size_type pos, size_type count):
		_string_data(TR(std::string(other, pos, count))) {}

	inline string::string(const wstr& other):
		_string_data(TR(other)) {}

	inline string::string(const wstr& other, size_type pos):
		_string_data(TR(std::wstring(other, pos))) {}

	inline string::string(const wstr& other, size_type pos, size_type count):
		_string_data(TR(std::wstring(other, pos, count))) {}

	inline string::string(const char8* other):
		_string_data(TRC(other)) {}

	inline string::string(const char8* other, size_type pos):
		_string_data(TR(std::u8string(other, pos))) {}

	inline string::string(const char16* other):
		_string_data(TRC(other)) {}

	inline string::string(const char16* other, size_type pos):
		_string_data(TR(std::u16string(other, pos))) {}

	inline string::string(const char32* other):
		_string_data(TRC(other)) {}

	inline string::string(const char32* other, size_type pos):
		_string_data(TR(std::u32string(other, pos))) {}

	inline string::string(const char* other):
		_string_data(TR(std::string(other))) {}

	inline string::string(const char* other, size_type pos):
		_string_data(TR(std::string(other, pos))) {}

	inline string::string(const wchar_t* other):
		_string_data(TRC(other)) {}

	inline string::string(const wchar_t* other, size_type pos):
		_string_data(TR(std::wstring(other, pos))) {}

	inline string::string(std::initializer_list<char8> il):
		_string_data(TR(std::u8string(il))) {}

	inline string::string(std::initializer_list<char16> il):
		_string_data(TR(std::u16string(il))) {}

	inline string::string(std::initializer_list<char32> il):
		_string_data(TR(std::u32string(il))) {}

	inline string::string(std::initializer_list<char> il):
		_string_data(TR(std::string(il))) {}

	inline string::string(std::initializer_list<wchar_t> il):
		_string_data(TR(std::wstring(il))) {}

	inline string::string(size_type count, char8 c):
		_string_data(TR(std::u8string(count, c))) {}

	inline string::string(size_type count, char16 c):
		_string_data(TR(std::u16string(count, c))) {}

	inline string::string(size_type count, char32 c):
		_string_data(TR(std::u32string(count, c))) {}

	inline string::string(size_type count, char c):
		_string_data(TR(std::string(count, c))) {}

	inline string::string(size_type count, wchar_t c):
		_string_data(TR(std::wstring(count, c))) {}

	inline string::string(utf8::iterator first, utf8::iterator last):
		_string_data(TR(std::u8string(first, last))) {}

	inline string::string(utf16::iterator first, utf16::iterator last):
		_string_data(TR(std::u16string(first, last))) {}

	inline string::string(utf32::iterator first, utf32::iterator last):
		_string_data(TR(std::u32string(first, last))) {}

	inline string::string(str::iterator first, str::iterator last):
		_string_data(TR(std::string(first, last))) {}

	inline string::string(wstr::iterator first, wstr::iterator last):
		_string_data(TR(std::wstring(first, last))) {}

#pragma endregion
#pragma region plus operator
	inline string operator+(const string& lhs, const string& rhs) {
		return string(lhs.TRM() + rhs.TRM());
	}

	inline string operator+(const string& lhs, const string::str& rhs) {
		return string(lhs.TRM() + TR(rhs));
	}

	template<class string_t>
	inline string operator+(const string& lhs, const string_t& rhs) {
		return string(lhs.TRM() + rhs.TRM());
	}

	inline string operator+(const string::string_type& lhs, const string& rhs) {
		return string(lhs + rhs.TRM());
	}

	template<class string_t>
	inline string operator+(const string_t& lhs, const string& rhs) {
		return string(TR(lhs) + rhs.TRM());
	}
	
	inline string operator+(const string& lhs, string&& rhs) {
		return string(lhs.TRM() + rhs.TRM());
	}

	inline string operator+(string&& lhs, string&& rhs) {
		return string(lhs.TRM() + rhs.TRM());
	}

	inline string operator+(string&& lhs, const string& rhs) {
		return string(lhs.TRM() + rhs.TRM());
	}

	template<class string_t>
	inline string operator+(string_t&& lhs, const string& rhs) {
		return string(TR(lhs) + rhs.TRM());
	}

	template<class string_t>
	inline string operator+(string&& lhs, const string_t& rhs) {
		return string(lhs.TRM() + TR(rhs));
	}

	template<class string_t>
	inline string operator+(const string_t& lhs, string&& rhs) {
		return string(TR(lhs) + rhs.TRM());
	}

	template<class string_t>
	inline string operator+(string_t&& lhs, string&& rhs) {
		return string(TR(lhs) + rhs.TRM());
	}

	template<class string_t>
	inline string operator+(string&& lhs, string_t&& rhs) {
		return string(lhs.TRM() + TR(rhs));
	}

	inline string operator+(const char* lhs, const string& rhs) {
		return string(TRC(lhs) + rhs.TRM());
	}

	inline string operator+(const char* lhs, string&& rhs) {
		return string(TRC(lhs) + rhs.TRM());
	}

	inline string operator+(char lhs, const string& rhs) {
		return string(lhs + rhs.TRM());
	}

	inline string operator+(char lhs, string&& rhs) {
		return string(lhs + rhs.TRM());
	}

	inline string operator+(const string& lhs, const char* rhs) {
		return string(lhs.TRM() + TRC(rhs));
	}

	inline string operator+(string&& lhs, const char* rhs) {
		return string(lhs.TRM() + TRC(rhs));
	}

	inline string operator+(const string& lhs, char rhs) {
		return string(lhs.TRM() + rhs);
	}

	inline string operator+(string&& lhs, char rhs) {
		return string(lhs.TRM() + rhs);
	}

	template<class char_t>
	inline string operator+(const char_t* lhs, const string& rhs) {
		return string(TR(lhs) + rhs.TRM());
	}

	template<class char_t>
	inline string operator+(const char_t* lhs, string&& rhs) {
		return string(TR(lhs) + rhs.TRM());
	}

	template<class char_t>
	inline string operator+(char_t lhs, const string& rhs) {
		auto s = string(1, rhs).TRM();
		return string(s + rhs.TRM());
	}

	template<class char_t>
	inline string operator+(char_t lhs, string&& rhs) {
		auto s = string(1, rhs).TRM();
		return string(s + rhs.TRM());
	}

	template<class char_t>
	inline string operator+(const string& lhs, const char_t* rhs) {
		return string(lhs.TRM() + TR(rhs));
	}

	template<class char_t>
	inline string operator+(string&& lhs, const char_t* rhs) {
		return string(lhs.TRM() + TR(rhs));
	}

	template<class char_t>
	inline string operator+(const string& lhs, char_t rhs) {
		auto s = string(1, rhs).TRM();
		return string(lhs.TRM() + s);
	}

	template<class char_t>
	inline string operator+(string&& lhs, char_t rhs) {
		auto s = string(1, rhs).TRM();
		return string(lhs.TRM() + s);
	}
#pragma endregion
#pragma region converter
	inline std::u8string string::to_u8string() const {
		return suika::to_u8string(_string_data.c_str());
	}
	inline std::u16string string::to_u16string() const {
		return suika::to_u16string(_string_data.c_str());
	}
	inline std::u32string string::to_u32string() const {
		return suika::to_u32string(_string_data.c_str());
	}
	inline std::string string::to_string() const {
		return suika::to_string(_string_data.c_str());
	}
	inline std::wstring string::to_wstring() const {
		return suika::to_wstring(_string_data.c_str());
	}

#if 0
	inline std::u8string_view string::to_u8string_view() const {
		auto s = suika::to_u8string(_string_data);
		return std::u8string_view(s);
	}
	inline std::u16string_view string::to_u16string_view() const {
		auto s = suika::to_u16string(_string_data);
		return std::u16string_view(s);
	}
	inline std::u32string_view string::to_u32string_view() const {
		auto s = suika::to_u32string(_string_data);
		return std::u32string_view(s);
	}
	inline std::string_view string::to_string_view() const {
		auto s = suika::to_string(_string_data);
		return std::string_view(s);
	}
	inline std::wstring_view string::to_wstring_view() const {
		auto s = suika::to_wstring(_string_data);
		return std::wstring_view(s);
	}
#endif
#pragma endregion
#pragma region splitter
	inline std::vector<std::u8string> string::split(char8 split_char, bool is_contain_lastempty) const {
		return suika::split(suika::to_u8string(_string_data.c_str()), split_char, is_contain_lastempty);
	}
	inline std::vector<std::u16string> string::split(char16 split_char, bool is_contain_lastempty) const {
		return suika::split(suika::to_u16string(_string_data.c_str()), split_char, is_contain_lastempty);
	}
	inline std::vector<std::u32string> string::split(char32 split_char, bool is_contain_lastempty) const {
		return suika::split(suika::to_u32string(_string_data.c_str()), split_char, is_contain_lastempty);
	}
	inline std::vector<std::string> string::split(char split_char, bool is_contain_lastempty) const {
		return suika::split(suika::to_string(_string_data.c_str()), split_char, is_contain_lastempty);
	}
	inline std::vector<std::wstring> string::split(wchar_t split_char, bool is_contain_lastempty) const {
		return suika::split(suika::to_wstring(_string_data.c_str()), split_char, is_contain_lastempty);
	}
#pragma endregion
#pragma region replacer
	inline string& string::replace(utf8 old_string, utf8 new_string) {
		_string_data = TR(suika::replace_string(suika::to_u8string(_string_data.c_str()), old_string, new_string));
		return *this;
	}
	inline string& string::replace(utf16 old_string, utf16 new_string) {
		_string_data = TR(suika::replace_string(suika::to_u16string(_string_data.c_str()), old_string, new_string));
		return *this;
	}
	inline string& string::replace(utf32 old_string, utf32 new_string) {
		_string_data = TR(suika::replace_string(suika::to_u32string(_string_data.c_str()), old_string, new_string));
		return *this;
	}
	inline string& string::replace(str old_string, str new_string) {
		_string_data = TR(suika::replace_string(suika::to_string(_string_data.c_str()), old_string, new_string));
		return *this;
	}
	inline string& string::replace(wstr old_string, wstr new_string) {
		_string_data = TR(suika::replace_string(suika::to_wstring(_string_data.c_str()), old_string, new_string));
		return *this;
	}

	inline string string::replaced(utf8 old_string, utf8 new_string) {
		return string(TR(suika::replace_string(suika::to_u8string(_string_data.c_str()), old_string, new_string)));
	}
	inline string string::replaced(utf16 old_string, utf16 new_string) {
		return string(TR(suika::replace_string(suika::to_u16string(_string_data.c_str()), old_string, new_string)));
	}
	inline string string::replaced(utf32 old_string, utf32 new_string) {
		return string(TR(suika::replace_string(suika::to_u32string(_string_data.c_str()), old_string, new_string)));
	}
	inline string string::replaced(str old_string, str new_string) {
		return string(TR(suika::replace_string(suika::to_string(_string_data.c_str()), old_string, new_string)));
	}
	inline string string::replaced(wstr old_string, wstr new_string) {
		return string(TR(suika::replace_string(suika::to_wstring(_string_data.c_str()), old_string, new_string)));
	}
#pragma endregion
#undef TR
#undef TRM
} // namespace suika
