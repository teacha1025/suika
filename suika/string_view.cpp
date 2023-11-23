#include "../include/suika/def.h"
#include "../include/suika/string_view.h"
#include "../include/suika/codecvt.h"
#include "../include/suika/except.h"
#include <string>
#include <string_view>
#include <array>
#include <Windows.h>

namespace suika {
	constexpr string_view::string_view(const string_view_type& str) noexcept {
		_str = str;
	}
	constexpr string_view::string_view(const char_t* str) noexcept {
		_str = string_view_type(str);
	}
	constexpr string_view::string_view(const char_t* str, size_type len) noexcept{
		_str = string_view_type(str, len);
	}

	string_view::str string_view::to_string() const {
		return suika::to_string(_str);
	}
	string_view::wstr string_view::to_wstring() const {
		return suika::to_wstring(_str);
	}
	string_view::utf8 string_view::to_utf8() const {
		return suika::to_u8string(_str);
	}
	string_view::utf16 string_view::to_utf16() const {
		return suika::to_u16string(_str);
	}
	string_view::utf32 string_view::to_utf32() const {
		return suika::to_u32string(_str);
	}
}