#include <Windows.h>
#include "../include/suika/codecvt.h"

namespace suika {
	std::string to_string(const std::u8string_view& src) {
		int		  in  = static_cast<int>(src.length());
		int		  out = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(src.data()), in, nullptr, 0);
		std::wstring r(out, L'\0');
		if (out) {
			MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(src.data()), in, &r[0], out);
		}
		return to_string(r);
	}
	std::string to_string(const std::u16string_view& src) {
		return to_string(std::wstring(src.begin(), src.end()));
	}
	std::string to_string(const std::u32string_view& src) {
		return to_string(std::wstring(src.begin(), src.end()));
	}
	std::string to_string(const std::wstring_view& src) {
		int		 in  = static_cast<int>(src.length());
		int		 out = WideCharToMultiByte(932, 0, src.data(), in, nullptr, 0, nullptr, nullptr);
		std::string r(out, '\0');
		if (out) {
			WideCharToMultiByte(932, 0, src.data(), in, &r[0], out, nullptr, nullptr);
		}
		return r;
	}

	std::wstring to_wstring(const std::u8string_view& src) {
		int		  in  = static_cast<int>(src.length());
		int		  out = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(src.data()), in, nullptr, 0);
		std::wstring r(out, L'\0');
		if (out) {
			MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(src.data()), in, &r[0], out);
		}
		return r;
	}
	std::wstring to_wstring(const std::u16string_view& src) {
		return std::wstring(src.begin(), src.end());
	}
	std::wstring to_wstring(const std::u32string_view& src) {
		return std::wstring(src.begin(), src.end());
	}
	std::wstring to_wstring(const std::string_view& src) {
		int		  in  = static_cast<int>(src.length());
		int		  out = MultiByteToWideChar(CP_ACP, 0, src.data(), in, nullptr, 0);
		std::wstring r(out, L'\0');
		if (out) {
			MultiByteToWideChar(CP_ACP, 0, src.data(), in, &r[0], out);
		}
		return r;
	}

	std::u8string to_u8string(const std::u16string_view& src) {
		auto w = to_wstring(src);
		return to_u8string(w);
	}
	std::u8string to_u8string(const std::u32string_view& src) {
		auto w = to_wstring(src);
		return to_u8string(w);
	}
	std::u8string to_u8string(const std::string_view& src) {
		auto w = to_wstring(src);
		return to_u8string(w);
	}
	std::u8string to_u8string(const std::wstring_view& src) {
		int		   in  = static_cast<int>(src.length());
		int		   out = WideCharToMultiByte(CP_UTF8, 0, src.data(), in, nullptr, 0, nullptr, nullptr);
		std::u8string r(out, u8'\0');
		if (out) {
			WideCharToMultiByte(CP_UTF8, 0, src.data(), in, reinterpret_cast<char*>(r.data()), out, nullptr, nullptr);
		}
		return r;
	}

	std::u16string to_u16string(const std::u8string_view& src) {
		auto w = to_wstring(src);
		return std::u16string(w.begin(), w.end());
	}
	std::u16string to_u16string(const std::u32string_view& src) {
		auto w = to_wstring(src);
		return std::u16string(w.begin(), w.end());
	}
	std::u16string to_u16string(const std::string_view& src) {
		auto w = to_wstring(src);
		return std::u16string(w.begin(), w.end());
	}
	std::u16string to_u16string(const std::wstring_view& src) {
		return std::u16string(src.begin(), src.end());
	}

	std::u32string to_u32string(const std::u8string_view& src) {
		auto w = to_wstring(src);
		return std::u32string(w.begin(), w.end());
	}
	std::u32string to_u32string(const std::u16string_view& src) {
		auto w = to_wstring(src);
		return std::u32string(w.begin(), w.end());
	}
	std::u32string to_u32string(const std::string_view& src) {
		auto w = to_wstring(src);
		return std::u32string(w.begin(), w.end());
	}
	std::u32string to_u32string(const std::wstring_view& src) {
		return std::u32string(src.begin(), src.end());
	}
} // namespace suika