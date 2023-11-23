#pragma once
#include "def.h"
#include <string_view>
#include <string>

namespace suika {
	class string_view {
	public:
		using string_view_type = std::u32string_view;
		using traits_type = typename string_view_type::traits_type;
		using value_type = typename string_view_type::value_type;
		using char_t = typename value_type;
		using pointer = typename string_view_type::pointer;
		using const_pointer = typename string_view_type::const_pointer;
		using reference = typename string_view_type::reference;
		using const_reference = typename string_view_type::const_reference;
		using const_iterator = typename string_view_type::const_iterator;
		using iterator = typename string_view_type::iterator;
		using const_reverse_iterator = typename string_view_type::const_reverse_iterator;
		using reverse_iterator = typename string_view_type::reverse_iterator;
		using size_type = typename string_view_type::size_type;
		using difference_type = typename string_view_type::difference_type;

		using str = std::string;
		using wstr = std::wstring;
		using utf8 = std::u8string;
		using utf16 = std::u16string;
		using utf32 = std::u32string;
		using str_view = std::string_view;
		using wstr_view = std::wstring_view;
		using utf8_view = std::u8string_view;
		using utf16_view = std::u16string_view;
		using utf32_view = std::u32string_view;
		static constexpr size_type npos{ static_cast<size_type>(-1) };

		constexpr string_view() noexcept = default;
		constexpr string_view(const string_view&) noexcept = default;
		constexpr string_view(const char_t* str) noexcept;
		constexpr string_view(nullptr_t) = delete;
		constexpr string_view(const char_t* str, size_type len) noexcept;

		template<class _it, class _end>
		constexpr string_view(_it begin, _end end) {
			_str = string_view_type(begin, end);
		}

		constexpr string_view(const string_view_type& str) noexcept;

		constexpr string_view(string_view&&) noexcept = default;

		str to_string() const;
		wstr to_wstring() const;
		utf8 to_utf8() const;
		utf16 to_utf16() const;
		utf32 to_utf32() const;
	private:
		string_view_type _str;
	};
}