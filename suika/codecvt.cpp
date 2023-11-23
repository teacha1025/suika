#include <array>
#include <string>
#include <Windows.h>
#include "../include/suika/def.h"
#include "../include/suika/except.h"

#define CODECVT_CONSTEXPR 
namespace {
	define WC_SIZE = sizeof(wchar_t);
	//string;CP932
	//u8string:UTF8
	//wstring:UTF16
	static CODECVT_CONSTEXPR std::wstring cp_to_wide(const std::string_view& s, UINT codepage) {
		int in_length = (int)s.length();
		int out_length =
			MultiByteToWideChar(codepage, 0, s.data(), in_length, 0, 0);
		std::wstring result(out_length, L'\0');
		if (out_length)
			MultiByteToWideChar(codepage, 0, s.data(), in_length, &result[0],
				out_length);
		return result;
	}
	static CODECVT_CONSTEXPR std::string wide_to_cp(const std::wstring_view& s, UINT codepage) {
		int in_length = (int)s.length();
		int out_length =
			WideCharToMultiByte(codepage, 0, s.data(), in_length, 0, 0, 0, 0);
		std::string result(out_length, '\0');
		if (out_length)
			WideCharToMultiByte(codepage, 0, s.data(), in_length, &result[0],
				out_length, 0, 0);
		return result;
	}

	static CODECVT_CONSTEXPR int u8_count(char8_t ch) {
		if (0 <= uint8_t(ch) && uint8_t(ch) < 0x80) {
			return 1;
		}
		if (0xC2 <= uint8_t(ch) && uint8_t(ch) < 0xE0) {
			return 2;
		}
		if (0xE0 <= uint8_t(ch) && uint8_t(ch) < 0xF0) {
			return 3;
		}
		if (0xF0 <= uint8_t(ch) && uint8_t(ch) < 0xF8) {
			return 4;
		}
		return 0;
	}
	static CODECVT_CONSTEXPR bool u8_later(char ch) {
		return 0x80 <= uint8_t(ch) && uint8_t(ch) < 0xC0;
	}
	static CODECVT_CONSTEXPR bool u16_h(char16_t ch) { return 0xD800 <= ch && ch < 0xDC00; }
	static CODECVT_CONSTEXPR bool u16_l(char16_t ch) { return 0xDC00 <= ch && ch < 0xE000; }
	static CODECVT_CONSTEXPR char32_t to_u32_c(const std::array<char8_t, 4>& c) {
		switch (u8_count(c[0])) {
			case 0: {
				throw suika::exception("invalid charactor. (utf8 to utf32)");
				break;
			}
			case 1: {
				return char32_t(uint8_t(c[0]));
				break;
			}
			case 2: {
				if (!u8_later(c[1]) || (uint8_t(c[0]) & 0x1E) == 0) throw suika::exception("invalid charactor. (utf8 to utf32)");
				char32_t r = char32_t(c[0] & 0x1F) << 6;
				r |= char32_t(c[1] & 0x3F);
				return r;
			}
			case 3: {
				if (!u8_later(c[1]) || !u8_later(c[2])) throw suika::exception("invalid charactor. (utf8 to utf32)");
				if ((uint8_t(c[0]) & 0x0F) == 0 && (uint8_t(c[1]) & 0x20) == 0) throw suika::exception("invalid charactor. (utf8 to utf32)");
				char32_t r = char32_t(c[0] & 0x0F) << 12;
				r |= char32_t(c[1] & 0x3F) << 6;
				r |= char32_t(c[2] & 0x3F);
				return r;
			}
			case 4: {
				if (!u8_later(c[1]) || !u8_later(c[2]) || !u8_later(c[3])) throw suika::exception("invalid charactor. (utf8 to utf32)");
				if ((uint8_t(c[0]) & 0x07) == 0 && (uint8_t(c[1]) & 0x30) == 0) throw suika::exception("invalid charactor. (utf8 to utf32)");
				char32_t r = char32_t(c[0] & 0x07) << 18;
				r |= char32_t(c[1] & 0x3F) << 12;
				r |= char32_t(c[2] & 0x3F) << 6;
				r |= char32_t(c[3] & 0x3F);
				return r;
			}
			default: {
				throw suika::exception("invalid charactor. (utf8 to utf32)");
			}
		}
		return char32_t(0);
	}
	static CODECVT_CONSTEXPR char32_t to_u32_c(const std::array<char16_t, 2>& c) {
		if (u16_h(c[0])) {
			if (u16_l(c[1])) {
				return 0x10000 + (char32_t(c[0]) - 0xD800) * 0x400 + (char32_t(c[1]) - 0xDC00);
			}
			else if (c[1] == 0) {
				return char32_t(c[0]);
			}
		}
		else if (u16_l(c[0])) {
			if (c[1] == 0) {
				return char32_t(c[0]);
			}
		}
		else {
			return char32_t(c[0]);
		}
		throw suika::exception("invalid charactor. (utf16 to utf32)");
	}
	static CODECVT_CONSTEXPR char32_t to_u32_c(const std::array<wchar_t, 4 / WC_SIZE>& c) {
		if constexpr (WC_SIZE == 4) {
			return char32_t(c[0]);
		}
		else if constexpr (WC_SIZE == 2) {
			return to_u32_c(std::array<char16_t, 2>{char16_t(c[0]), char16_t(c[1])});
		}
		else {
			throw suika::exception("invalid charactor. (wchar_t to utf32)");
		}
	}
	static CODECVT_CONSTEXPR char32_t to_u32_c(const std::array<char, 4>& c) {
		return to_u32_c(std::array<char8_t, 4>{char8_t(c[0]), char8_t(c[1]), char8_t(c[2]), char8_t(c[3])});
	}
	static CODECVT_CONSTEXPR std::array<char16_t, 2> to_u16_c(char32_t c) {
		std::array<char16_t, 2> u16Ch;
		if (c < 0 || c > 0x10FFFF) {
			throw suika::exception("invalid charactor. (utf32 to utf16)");
		}

		if (c < 0x10000) {
			u16Ch[0] = char16_t(c);
			u16Ch[1] = 0;
		}
		else {
			u16Ch[0] = char16_t((c - 0x10000) / 0x400 + 0xD800);
			u16Ch[1] = char16_t((c - 0x10000) % 0x400 + 0xDC00);
		}

		return u16Ch;
	}
	static CODECVT_CONSTEXPR std::array<char16_t, 2> to_u16_c(const std::array<char8_t, 4> c) {
		return to_u16_c(to_u32_c(c));
	}
	static CODECVT_CONSTEXPR std::array<char16_t, 2> to_u16_c(const std::array<wchar_t, 4 / WC_SIZE>& c) {
		return to_u16_c(to_u32_c(c));
	}
	static CODECVT_CONSTEXPR std::array<char16_t, 2> to_u16_c(const std::array<char, 4>& c) {
		return to_u16_c(std::array<char8_t, 4>{ char8_t(c[0]), char8_t(c[1]), char8_t(c[2]), char8_t(c[3]) });
	}
	static CODECVT_CONSTEXPR std::array<char8_t, 4> to_u8_c(char32_t c) {
		std::array<char8_t, 4> u8;
		if (c < 0 || c > 0x10FFFF) {
			throw suika::exception("invalid charactor. (utf32 to utf8)");
		}

		if (c < 128) {
			u8[0] = char8_t(c);
			u8[1] = 0;
			u8[2] = 0;
			u8[3] = 0;
		}
		else if (c < 2048) {
			u8[0] = 0xC0 | char8_t(c >> 6);
			u8[1] = 0x80 | (char8_t(c) & 0x3F);
			u8[2] = 0;
			u8[3] = 0;
		}
		else if (c < 65536) {
			u8[0] = 0xE0 | char8_t(c >> 12);
			u8[1] = 0x80 | (char8_t(c >> 6) & 0x3F);
			u8[2] = 0x80 | (char8_t(c) & 0x3F);
			u8[3] = 0;
		}
		else {
			u8[0] = 0xF0 | char8_t(c >> 18);
			u8[1] = 0x80 | (char8_t(c >> 12) & 0x3F);
			u8[2] = 0x80 | (char8_t(c >> 6) & 0x3F);
			u8[3] = 0x80 | (char8_t(c) & 0x3F);
		}
		return u8;
	}
	static CODECVT_CONSTEXPR std::array<char8_t, 4> to_u8_c(const std::array<char16_t, 2>& c) {
		return to_u8_c(to_u32_c(c));
	}
	static CODECVT_CONSTEXPR std::array<char8_t, 4> to_u8_c(const std::array<wchar_t, 4 / WC_SIZE>& c) {
		return to_u8_c(to_u32_c(c));
	}
	static CODECVT_CONSTEXPR std::array<char8_t, 4> to_u8_c(const std::array<char, 4>& c) {
		return { char8_t(c[0]),char8_t(c[1]),char8_t(c[2]),char8_t(c[3]) };
	}
	static CODECVT_CONSTEXPR std::array<char, 4> to_char_c(char32_t c) {
		auto chr = to_u8_c(c);
		return { char(chr[0]),char(chr[1]),char(chr[2]),char(chr[3]) };
	}
	static CODECVT_CONSTEXPR std::array<char, 4> to_char_c(const std::array<char16_t, 2>& c) {
		auto chr = to_u8_c(c);
		return { char(chr[0]),char(chr[1]),char(chr[2]),char(chr[3]) };
	}
	static CODECVT_CONSTEXPR std::array<char, 4> to_char_c(const std::array<wchar_t, 4 / WC_SIZE>& c) {
		auto chr = to_u8_c(c);
		return { char(chr[0]),char(chr[1]),char(chr[2]),char(chr[3]) };
	}
	static CODECVT_CONSTEXPR std::array<char, 4> to_char_c(const std::array<char8_t, 2>& c) {
		return { char(c[0]),char(c[1]),char(c[2]),char(c[3]) };
	}
}
namespace suika {
	CODECVT_CONSTEXPR std::u32string to_u32string(const std::string_view& str) {
		return to_u32string(to_wstring(str));
	}
	CODECVT_CONSTEXPR std::u32string to_u32string(const std::u8string_view& str) {
		std::u32string ret;
		for (auto u8It = str.begin(); u8It != str.end(); ++u8It) {
			auto bytes = u8_count((*u8It));
			if (bytes == 0) {
				throw exception("invalid string. (utf8 to utf32)");
			}

			std::array<char, 4> u8;
			u8[0] = (*u8It);
			for (int i = 1; i < bytes; i++) {
				++u8It;
				if (u8It == str.end()) {
					throw exception("invalid string. (utf8 to utf32)");
				}
				u8[i] = (*u8It);
			}

			ret.push_back(to_u32_c(u8));
		}
		return ret;
	}
	CODECVT_CONSTEXPR std::u32string to_u32string(const std::wstring_view& str) {
		std::u32string ret;
		for (auto u16It = str.begin(); u16It != str.end(); ++u16It) {
			std::array<wchar_t, 2> u16;

			if (u16_h((*u16It))) {
				u16[0] = (*u16It);
				++u16It;
				if (u16It == str.end()) {
					throw exception("invalid string. (wstring to utf32)");
				}
				u16[1] = (*u16It);
			}
			else {
				u16[0] = (*u16It);
				u16[1] = 0;
			}

			ret.push_back(to_u32_c(u16));
		}
		return ret;
	}
	CODECVT_CONSTEXPR std::u32string to_u32string(const std::u16string_view& str) {
		std::u32string ret;
		for (auto u16It = str.begin(); u16It != str.end(); ++u16It) {
			std::array<char16_t, 2> u16;

			if (u16_h((*u16It))) {
				u16[0] = (*u16It);
				++u16It;
				if (u16It == str.end()) {
					throw exception("invalid string. (utf16 to utf32)");
				}
				u16[1] = (*u16It);
			}
			else {
				u16[0] = (*u16It);
				u16[1] = 0;
			}

			ret.push_back(to_u32_c(u16));
		}
		return ret;
	}
	CODECVT_CONSTEXPR std::string to_string(const std::u8string_view& src) {
		return to_string(to_wstring(src));
	}
	CODECVT_CONSTEXPR std::string to_string(const std::u16string_view& src) {
		return to_string(to_wstring(src));
	}
	CODECVT_CONSTEXPR std::string to_string(const std::u32string_view& src) {
		return to_string(to_wstring(src));
	}
	CODECVT_CONSTEXPR std::string to_string(const std::wstring_view& src) {
		return ::wide_to_cp(src, 932);
	}
	CODECVT_CONSTEXPR std::wstring to_wstring(const std::u8string_view& src) {
		if constexpr (WC_SIZE == 2) {
			auto s = to_u16string(src);
			return std::wstring(s.begin(), s.end());
		}
		else if constexpr (WC_SIZE == 4) {
			auto s = to_u32string(src);
			return std::wstring(s.begin(), s.end());
		}
		else {
			throw exception("invalid string. (utf8 to wstring)");
		}
		return L"";
	}
	CODECVT_CONSTEXPR std::wstring to_wstring(const std::u16string_view& src) {
		if constexpr (WC_SIZE == 2) {
			return std::wstring(src.begin(), src.end());
		}
		else if constexpr (WC_SIZE == 4) {
			auto s = to_u32string(src);
			return std::wstring(s.begin(), s.end());
		}
		else {
			throw exception("invalid string. (utf16 to wstring)");
		}
		return L"";
	}
	CODECVT_CONSTEXPR std::wstring to_wstring(const std::u32string_view& src) {
		if constexpr (WC_SIZE == 2) {
			auto s = to_u16string(src);
			return std::wstring(s.begin(), s.end());
		}
		else if constexpr (WC_SIZE == 4) {
			return std::wstring(src.begin(), src.end());
		}
		else {
			throw exception("invalid string. (utf32 to wstring)");
		}
		return L"";
	}
	CODECVT_CONSTEXPR std::wstring to_wstring(const std::string_view& src) {
		return ::cp_to_wide(src, 932);
	}
	CODECVT_CONSTEXPR std::u8string to_u8string(const std::u16string_view& src) {
		std::u8string u8Str;
		for (auto u16It = src.begin(); u16It != src.end(); ++u16It) {
			std::array<char16_t, 2> u16Ch;
			if (u16_h((*u16It))) {
				u16Ch[0] = (*u16It);
				++u16It;
				if (u16It == src.end()) {
					throw exception("invalid string. (utf16 to utf8)");
				}
				u16Ch[1] = (*u16It);
			}
			else {
				u16Ch[0] = (*u16It);
				u16Ch[1] = 0;
			}

			std::array<char8_t, 4> u8Ch=to_u8_c(u16Ch);
			if (u8Ch[0] != 0) {
				u8Str.push_back(u8Ch[0]);
			}
			if (u8Ch[1] != 0) {
				u8Str.push_back(u8Ch[1]);
			}
			if (u8Ch[2] != 0) {
				u8Str.push_back(u8Ch[2]);
			}
			if (u8Ch[3] != 0) {
				u8Str.push_back(u8Ch[3]);
			}
		}
		return u8Str;
	}
	CODECVT_CONSTEXPR std::u8string to_u8string(const std::u32string_view& src) {
		std::u8string u8Str;
		for (auto u32It = src.begin(); u32It != src.end(); ++u32It) {
			std::array<char8_t, 4> u8Ch=to_u8_c(*u32It);

			if (u8Ch[0] != 0) {
				u8Str.push_back(u8Ch[0]);
			}
			if (u8Ch[1] != 0) {
				u8Str.push_back(u8Ch[1]);
			}

			if (u8Ch[2] != 0) {
				u8Str.push_back(u8Ch[2]);
			}
			if (u8Ch[3] != 0) {
				u8Str.push_back(u8Ch[3]);
			}
		}
		return u8Str;
	}
	CODECVT_CONSTEXPR std::u8string to_u8string(const std::string_view& src) {
		return to_u8string(to_u32string(src));
	}
	CODECVT_CONSTEXPR std::u8string to_u8string(const std::wstring_view& src) {
		return to_u8string(to_u16string(src));
	}
	CODECVT_CONSTEXPR std::u16string to_u16string(const std::u8string_view& src) {
		std::u16string u16Str;
		for (auto u8It = src.begin(); u8It != src.end(); ++u8It) {
			auto numBytes = u8_count((*u8It));
			if (numBytes == 0) {
				throw exception("invalid string. (utf8 to utf16)");
			}

			std::array<char, 4> u8Ch;
			u8Ch[0] = (*u8It);
			for (int i = 1; i < numBytes; i++) {
				++u8It;
				if (u8It == src.end()) {
					throw exception("invalid string. (utf8 to utf16)");
				}
				u8Ch[i] = (*u8It);
			}

			std::array<char16_t, 2> u16Ch = to_u16_c(u8Ch);
			u16Str.push_back(u16Ch[0]);
			if (u16Ch[1] != 0) {
				u16Str.push_back(u16Ch[1]);
			}
		}
		return u16Str;
	}
	CODECVT_CONSTEXPR std::u16string to_u16string(const std::u32string_view& src) {
		std::u16string u16Str;
		for (auto u32It = src.begin(); u32It != src.end(); ++u32It) {
			std::array<char16_t, 2> u16Ch = to_u16_c((*u32It));

			if (u16Ch[0] != 0) {
				u16Str.push_back(u16Ch[0]);
			}
			if (u16Ch[1] != 0) {
				u16Str.push_back(u16Ch[1]);
			}
		}
		return u16Str;
	}
	CODECVT_CONSTEXPR std::u16string to_u16string(const std::string_view& src) {
		return to_u16string(to_wstring(src));
	}
	CODECVT_CONSTEXPR std::u16string to_u16string(const std::wstring_view& src) {
		if constexpr (WC_SIZE == 2) {
			return std::u16string(src.begin(), src.end());
		}
		else if constexpr (WC_SIZE == 4) {
			return to_u16string(std::u32string(src.begin(), src.end()));
		}
		else {
			throw exception("invalid string. (wstring to utf16)");
		}
		return u"";
	}
	CODECVT_CONSTEXPR std::string to_string(const std::string_view& src) {
		return std::string(src.begin(), src.end());
	}
	CODECVT_CONSTEXPR std::wstring to_wstring(const std::wstring_view& src) {
		return std::wstring(src.begin(), src.end());
	}
	CODECVT_CONSTEXPR std::u8string to_u8string(const std::u8string_view& src) {
		return std::u8string(src.begin(), src.end());
	}
	CODECVT_CONSTEXPR std::u16string to_u16string(const std::u16string_view& src) {
		return std::u16string(src.begin(), src.end());
	}
	CODECVT_CONSTEXPR std::u32string to_u32string(const std::u32string_view& src) {
		return std::u32string(src.begin(), src.end());
	}
} // namespace suika
#undef CODECVT_CONSTEXPR 