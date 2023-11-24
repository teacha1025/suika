/**
* @file string.h
* @brief 文字列関係
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_STRING
#define _SK_STRING

#include <string>
#include <format>
#include <vector>
#include "def.h"
#include "string_view.h"

namespace suika {
	/// <summary>
	/// UTF8,UTF16,UTF32,マルチバイト文字列,ワイド文字列を扱うクラス
	/// </summary>
	class string {
	public:
		using utf8	   = std::u8string;
		using utf16	  = std::u16string;
		using utf32	  = std::u32string;
		using str		= std::string;
		using wstr	   = std::wstring;
		using utf8_view  = std::u8string_view;
		using utf16_view = std::u16string_view;
		using utf32_view = std::u32string_view;
		using str_view   = std::string_view;
		using wstr_view  = std::wstring_view;

		using string_type			= utf32;
		using string_view_type	   = str_view;

		using value_type			= string_type::value_type;
		using size_type = string_type::size_type;
		using difference_type = string_type::difference_type;
		using allocator_type = string_type::allocator_type;
		using reference = string_type::reference;
		using const_reference = string_type::const_reference;
		using pointer = string_type::pointer;
		using const_pointer = string_type::const_pointer;
		using iterator = string_type::iterator;
		using const_iterator = string_type::const_iterator;
		using reverse_iterator = string_type::reverse_iterator;
		using const_reverse_iterator = string_type::const_reverse_iterator;

		static constexpr auto npos = string_type::npos;

		string() noexcept = default;

		string(const string& other) noexcept = default;
		string& operator=(const string& other) = default;
		string(const string& other, size_type pos);
		string(const string& other, size_type pos, size_type count);
		string(string&& other) noexcept = default;

		string(const utf8& s);
		//string& operator=(const utf8& other);
		string(const utf8& s, size_type pos);
		string(const utf8& s, size_type pos, size_type count);
		string(const utf16& s);
		//string& operator=(const utf16& other);
		string(const utf16& s, size_type pos);
		string(const utf16& s, size_type pos, size_type count);
		string(const utf32& s);
		//string& operator=(const utf32& other);
		string(const utf32& s, size_type pos);
		string(const utf32& s, size_type pos, size_type count);
		string(const str& s);
		//string& operator=(const str& other);
		string(const str& s, size_type pos);
		string(const str& s, size_type pos, size_type count);
		string(const wstr& s);
		//string& operator=(const wstr& other);
		string(const wstr& s, size_type pos);
		string(const wstr& s, size_type pos, size_type count);
		string(const char8* s);
		//string& operator=(const char8* other);
		string(const char8* s, size_type count);
		string(const char16* s);
		//string& operator=(const char16* other);
		string(const char16* s, size_type count);
		string(const char32* s);
		//string& operator=(const char32* other);
		string(const char32* s, size_type count);
		string(const char* s);
		//string& operator=(const char* other);
		string(const char* s, size_type count);
		string(const wchar_t* s);
		//string& operator=(const wchar_t* other);
		string(const wchar_t* s, size_type count);
		string(std::initializer_list<char8> il);
		//string& operator=(std::initializer_list<char8> il);
		string(std::initializer_list<char16> il);
		//string& operator=(std::initializer_list<char16> il);
		string(std::initializer_list<char32> il);
		//string& operator=(std::initializer_list<char32> il);
		string(std::initializer_list<char> il);
		//string& operator=(std::initializer_list<char> il);
		string(std::initializer_list<wchar_t> il);
		//string& operator=(std::initializer_list<wchar_t> il);
		string(size_type count, char8 c);
		string(size_type count, char16 c);
		string(size_type count, char32 c);
		string(size_type count, char c);
		string(size_type count, wchar_t c);
		string(utf8::iterator first, utf8::iterator last);
		string(utf16::iterator first, utf16::iterator last);
		string(utf32::iterator first, utf32::iterator last);
		string(str::iterator first, str::iterator last);
		string(wstr::iterator first, wstr::iterator last);
		
		
		string&			   operator+=(const string& str);
		string&			   operator+=(const char8* str);
		string&			   operator+=(const char16* str);
		string&			   operator+=(const char32* str);
		string&			   operator+=(const char* str);
		string&			   operator+=(const wchar_t* str);
		string&			   operator+=(char8 c);
		string&			   operator+=(char16 c);
		string&			   operator+=(char32 c);
		string&			   operator+=(char c);
		string&			   operator+=(wchar_t c);
		string&			   operator+=(const utf8& str);
		string&			   operator+=(const utf16& str);
		string&			   operator+=(const utf32& str);
		string&			   operator+=(const str& str);
		string&			   operator+=(const wstr& str);
		string&			   operator+=(const utf8_view& str);
		string&			   operator+=(const utf16_view& str);
		string&			   operator+=(const utf32_view& str);
		string&			   operator+=(const str_view& str);
		string&			   operator+=(const wstr_view& str);

		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF8文字列</returns>
		NODISCARD utf8  to_u8string() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF16文字列</returns>
		NODISCARD utf16 to_u16string() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF32文字列</returns>
		NODISCARD utf32 to_u32string() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>文字列</returns>
		NODISCARD str	to_string() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>ワイド文字列</returns>
		NODISCARD wstr  to_wstring() const;

		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF8ビュー文字列</returns>
		NODISCARD utf8_view		to_u8string_view() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF16ビュー文字列</returns>
		NODISCARD utf16_view	to_u16string_view() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF32ビュー文字列</returns>
		NODISCARD utf32_view	to_u32string_view() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>ビュー文字列</returns>
		NODISCARD str_view		to_string_view() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>ワイドビュー文字列</returns>
		NODISCARD wstr_view		to_wstring_view() const;

		/// <summary>
		/// 文字列を分割
		/// </summary>
		/// <param name="split_char">区切り文字</param>
		/// <param name="is_contain_lastempty">区切り文字が最後にある場合、最後の空白を含むか</param>
		/// <returns>分割された文字列</returns>
		NODISCARD std::vector<utf8>  split(char8 split_char, bool is_contain_lastempty = false) const;
		/// <summary>
		/// 文字列を分割
		/// </summary>
		/// <param name="split_char">区切り文字</param>
		/// <param name="is_contain_lastempty">区切り文字が最後にある場合、最後の空白を含むか</param>
		/// <returns>分割された文字列</returns>
		NODISCARD std::vector<utf16> split(char16 split_char, bool is_contain_lastempty = false) const;
		/// <summary>
		/// 文字列を分割
		/// </summary>
		/// <param name="split_char">区切り文字</param>
		/// <param name="is_contain_lastempty">区切り文字が最後にある場合、最後の空白を含むか</param>
		/// <returns>分割された文字列</returns>
		NODISCARD std::vector<utf32> split(char32 split_char, bool is_contain_lastempty = false) const;
		/// <summary>
		/// 文字列を分割
		/// </summary>
		/// <param name="split_char">区切り文字</param>
		/// <param name="is_contain_lastempty">区切り文字が最後にある場合、最後の空白を含むか</param>
		/// <returns>分割された文字列</returns>
		NODISCARD std::vector<str>   split(char split_char, bool is_contain_lastempty = false) const;
		/// <summary>
		/// 文字列を分割
		/// </summary>
		/// <param name="split_char">区切り文字</param>
		/// <param name="is_contain_lastempty">区切り文字が最後にある場合、最後の空白を含むか</param>
		/// <returns>分割された文字列</returns>
		NODISCARD std::vector<wstr>  split(wchar_t split_char, bool is_contain_lastempty = false) const;

		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		string& replace(utf8 old_string, utf8 new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		string& replace(utf16 old_string, utf16 new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		string& replace(utf32 old_string, utf32 new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		string& replace(str old_string, str new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		string& replace(wstr old_string, wstr new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		/// <returns>置き換えられた文字列</returns>
		NODISCARD string  replaced(utf8 old_string, utf8 new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		/// <returns>置き換えられた文字列</returns>
		NODISCARD string  replaced(utf16 old_string, utf16 new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		/// <returns>置き換えられた文字列</returns>
		NODISCARD string  replaced(utf32 old_string, utf32 new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		/// <returns>置き換えられた文字列</returns>
		NODISCARD string  replaced(str old_string, str new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		/// <returns>置き換えられた文字列</returns>
		NODISCARD string  replaced(wstr old_string, wstr new_string);

		operator string_view() const noexcept {
			return string_view(_string_data.c_str());
		}

		/// <summary>
		/// 始端イテレータを取得
		/// </summary>
		/// <returns>始端イテレータ</returns>
		NODISCARD constexpr iterator begin() noexcept {
			return _string_data.begin();
		}

		/// <summary>
		/// 始端イテレータを取得
		/// </summary>
		/// <returns>始端イテレータ</returns>
		NODISCARD constexpr const_iterator begin() const noexcept {
			return _string_data.begin();
		}

		/// <summary>
		/// 終端イテレータを取得
		/// </summary>
		/// <returns>終端イテレータ</returns>
		NODISCARD constexpr iterator end() noexcept {
			return _string_data.end();
		}

		/// <summary>
		/// 終端イテレータを取得
		/// </summary>
		/// <returns>終端イテレータ</returns>
		NODISCARD constexpr const_iterator end() const noexcept {
			return _string_data.end();
		}

		/// <summary>
		/// 始端イテレータを取得
		/// </summary>
		/// <returns>始端イテレータ</returns>
		NODISCARD constexpr const_iterator cbegin() const noexcept {
			return _string_data.cbegin();
		}

		/// <summary>
		/// 終端イテレータを取得
		/// </summary>
		/// <returns>終端イテレータ</returns>
		NODISCARD constexpr const_iterator cend() const noexcept {
			return _string_data.cend();
		}

		/// <summary>
		/// 逆順始端イテレータを取得
		/// </summary>
		/// <returns>逆順始端イテレータ</returns>
		NODISCARD constexpr reverse_iterator rbegin() noexcept {
			return _string_data.rbegin();
		}

		/// <summary>
		/// 逆順始端イテレータを取得
		/// </summary>
		/// <returns>逆順始端イテレータ</returns>
		NODISCARD constexpr const_reverse_iterator rbegin() const noexcept {
			return _string_data.rbegin();
		}

		/// <summary>
		/// 逆順終端イテレータを取得
		/// </summary>
		/// <returns>逆順終端イテレータ</returns>
		NODISCARD constexpr reverse_iterator rend() noexcept {
			return _string_data.rend();
		}

		/// <summary>
		/// 逆順終端イテレータを取得
		/// </summary>
		/// <returns>逆順終端イテレータ</returns>
		NODISCARD constexpr const_reverse_iterator rend() const noexcept {
			return _string_data.rend();
		}

		/// <summary>
		/// 逆順始端イテレータを取得
		/// </summary>
		/// <returns>逆順始端イテレータ</returns>
		NODISCARD constexpr const_reverse_iterator crbegin() const noexcept {
			return _string_data.crbegin();
		}

		/// <summary>
		/// 逆順終端イテレータを取得
		/// </summary>
		/// <returns>逆順終端イテレータ</returns>
		NODISCARD constexpr const_reverse_iterator crend() const noexcept {
			return _string_data.crend();
		}

		/// <summary>
		/// 文字列の長さを取得
		/// </summary>
		/// <returns>文字列の長さ</returns>
		NODISCARD constexpr size_type size() const noexcept {
			return _string_data.size();
		}

		/// <summary>
		/// 文字列の長さを取得
		/// </summary>
		/// <returns>文字列の長さ</returns>
		NODISCARD constexpr size_type length() const noexcept {
			return _string_data.length();
		}

		/// <summary>
		/// 文字列の長さを取得
		/// </summary>
		/// <returns>文字列の長さ</returns>
		NODISCARD constexpr size_type max_size() const noexcept {
			return _string_data.max_size();
		}

		/// <summary>
		/// 最大の要素数を取得
		/// </summary>
		/// <returns>最大の要素数</returns>
		NODISCARD constexpr size_type capacity() const noexcept {
			return _string_data.capacity();
		}

		/// <summary>
		/// 文字列の長さを変更
		/// </summary>
		/// <param name="n">文字列の長さ</param>
		/// <param name="c">埋める文字</param>
		constexpr void resize(size_type n, char32 c) {
			_string_data.resize(n, c);
		}

		/// <summary>
		/// 文字列の長さを変更
		/// </summary>
		/// <param name="n">文字列の長さ</param>
		constexpr void resize(size_type n) {
			_string_data.resize(n);
		}

		/// <summary>
		/// 文字列の長さを変更
		/// </summary>
		/// <param name="res_arg">文字列の長さ</param>
		constexpr void reserve(size_type res_arg) {
			_string_data.reserve(res_arg);
		}

		/// <summary>
		/// 文字列の長さを変更
		/// </summary>
		constexpr void shrink_to_fit() {
			_string_data.shrink_to_fit();
		}

		/// <summary>
		/// 文字列をクリア
		/// </summary>
		constexpr void clear() noexcept {
			_string_data.clear();
		}

		/// <summary>
		/// 文字列が空か
		/// </summary>
		/// <returns>空か</returns>
		NODISCARD constexpr bool empty() const noexcept {
			return _string_data.empty();
		}

		/// <summary>
		/// 文字列の先頭を取得
		/// </summary>
		/// <returns>文字列の先頭</returns>
		NODISCARD constexpr const_reference front() const {
			return _string_data.front();
		}

		/// <summary>
		/// 文字列の先頭を取得
		/// </summary>
		/// <returns>文字列の先頭</returns>
		NODISCARD constexpr reference front() {
			return _string_data.front();
		}

		/// <summary>
		/// 文字列の末尾を取得
		/// </summary>
		/// <returns>文字列の末尾</returns>
		NODISCARD constexpr const_reference back() const {
			return _string_data.back();
		}

		/// <summary>
		/// 文字列の末尾を取得
		/// </summary>
		/// <returns>文字列の末尾</returns>
		NODISCARD constexpr reference back() {
			return _string_data.back();
		}

		/// <summary>
		/// 任意の位置の要素を取得
		/// </summary>
		/// <param name="pos">位置</param>
		/// <returns>pos 番目の要素</returns>
		NODISCARD constexpr const_reference operator[](size_type pos) const {
			return _string_data[pos];
		}

		/// <summary>
		/// 任意の位置の要素を取得
		/// </summary>
		/// <param name="pos">位置</param>
		/// <returns>pos 番目の要素</returns>
		NODISCARD constexpr reference operator[](size_type pos) {
			return _string_data[pos];
		}

		/// <summary>
		/// 任意の位置の要素を取得
		/// </summary>
		/// <param name="pos">位置</param>
		/// <returns>pos 番目の要素</returns>
		NODISCARD constexpr const_reference at(size_type pos) const {
			return _string_data.at(pos);
		}

		/// <summary>
		/// 任意の位置の要素を取得
		/// </summary>
		/// <param name="pos">位置</param>
		/// <returns>pos 番目の要素</returns>
		NODISCARD constexpr reference at(size_type pos) {
			return _string_data.at(pos);
		}

		/// <summary>
		/// 文字列を追加
		/// </summary>
		/// <param name="str">追加する文字列</param>
		/// <returns>追加された文字列</returns>
		NODISCARD constexpr string& append(const string& str) {
			_string_data.append(str._string_data);
			return *this;
		}

		/// <summary>
		/// 文字列を追加
		/// </summary>
		/// <param name="str">追加する文字列</param>
		/// <param name="pos">追加する文字列の開始位置</param>
		/// <param name="n">追加する文字列の長さ</param>
		/// <returns>追加された文字列</returns>
		NODISCARD constexpr string& append(const string& str, size_type pos, size_type n = npos) {
			_string_data.append(str._string_data, pos, n);
			return *this;
		}

		/// <summary>
		/// 文字列を追加
		/// </summary>
		/// <param name="s">追加する文字列</param>
		/// <param name="n">追加する文字列の長さ</param>
		/// <returns>追加された文字列</returns>
		NODISCARD constexpr string& append(const char32* s, size_type n) {
			_string_data.append(s, n);
			return *this;
		}

		/// <summary>
		/// 文字列を追加
		/// </summary>
		/// <param name="s">追加する文字列</param>
		/// <returns>追加された文字列</returns>
		NODISCARD constexpr string& append(const char32* s) {
			_string_data.append(s);
			return *this;
		}

		/// <summary>
		/// 文字列を追加
		/// </summary>
		/// <param name="n">追加する文字列の長さ</param>
		/// <param name="c">追加する文字</param>
		/// <returns>追加された文字列</returns>
		NODISCARD constexpr string& append(size_type n, char32 c) {
			_string_data.append(n, c);
			return *this;
		}

		/// <summary>
		/// 文字列を追加
		/// </summary>
		/// <param name="first">追加する文字列の開始位置</param>
		/// <param name="last">追加する文字列の終了位置</param>
		/// <returns>追加された文字列</returns>
		NODISCARD constexpr string& append(iterator first, iterator last) {
			_string_data.append(first, last);
			return *this;
		}

		/// <summary>
		/// 文字列を追加
		/// </summary>
		/// <param name="il">追加する文字列</param>
		/// <returns>追加された文字列</returns>
		NODISCARD constexpr string& append(std::initializer_list<char32> il) {
			_string_data.append(il);
			return *this;
		}

		/// <summary>
		/// 文字列を追加
		/// </summary>
		/// <param name="t">追加する文字列</param>
		/// <returns>追加された文字列</returns>
		NODISCARD constexpr string& append(const string_view& t) {
			_string_data.append(t._str);
			return *this;
		}

		/// <summary>
		/// 文字列を追加
		/// </summary>
		/// <param name="t">追加する文字列</param>
		/// <param name="pos">追加する文字列の開始位置</param>
		/// <param name="n">追加する文字列の長さ</param>
		/// <returns>追加された文字列</returns>
		NODISCARD constexpr string& append(const string_view& t, size_type pos, size_type n = npos) {
			_string_data.append(t._str, pos, n);
			return *this;
		}

		/// <summary>
		/// 末尾に文字を追加
		/// </summary>
		/// <param name="c">追加する文字</param>
		constexpr void push_back(char32 c) {
			_string_data.push_back(c);
		}

		/// <summary>
		/// 文字列を代入
		/// </summary>
		/// <param name="str">代入する文字列</param>
		/// <returns>代入された文字列</returns>
		NODISCARD constexpr string& assign(const string& str) {
			_string_data.assign(str._string_data);
			return *this;
		}

		/// <summary>
		/// 文字列を代入
		/// </summary>
		/// <param name="str">代入する文字列</param>
		/// <returns>代入された文字列</returns>
		NODISCARD constexpr string& assign(string&& str) noexcept {
			_string_data.assign(std::move(str._string_data));
			return *this;
		}

		/// <summary>
		/// 文字列を代入
		/// </summary>
		/// <param name="str">代入する文字列</param>
		/// <param name="pos">代入する文字列の開始位置</param>
		/// <param name="n">代入する文字列の長さ</param>
		/// <returns>代入された文字列</returns>
		NODISCARD constexpr string& assign(const string& str, size_type pos, size_type n = npos) {
			_string_data.assign(str._string_data, pos, n);
			return *this;
		}

		/// <summary>
		/// 文字列を代入
		/// </summary>
		/// <param name="s">代入する文字列</param>
		/// <param name="n">代入する文字列の長さ</param>
		/// <returns>代入された文字列</returns>
		NODISCARD constexpr string& assign(const char32* s, size_type n) {
			_string_data.assign(s, n);
			return *this;
		}

		/// <summary>
		/// 文字列を代入
		/// </summary>
		/// <param name="s">代入する文字列</param>
		/// <returns>代入された文字列</returns>
		NODISCARD constexpr string& assign(const char32* s) {
			_string_data.assign(s);
			return *this;
		}

		/// <summary>
		/// 文字列を代入
		/// </summary>
		/// <param name="n">代入する文字列の長さ</param>
		/// <param name="c">代入する文字</param>
		/// <returns>代入された文字列</returns>
		NODISCARD constexpr string& assign(size_type n, char32 c) {
			_string_data.assign(n, c);
			return *this;
		}

		/// <summary>
		/// 文字列を代入
		/// </summary>
		/// <param name="first">代入する文字列の開始位置</param>
		/// <param name="last">代入する文字列の終了位置</param>
		/// <returns>代入された文字列</returns>
		NODISCARD constexpr string& assign(iterator first, iterator last) {
			_string_data.assign(first, last);
			return *this;
		}

		/// <summary>
		/// 文字列を代入
		/// </summary>
		/// <param name="il">代入する文字列</param>
		/// <returns>代入された文字列</returns>
		NODISCARD constexpr string& assign(std::initializer_list<char32> il) {
			_string_data.assign(il);
			return *this;
		}

		/// <summary>
		/// 文字列を代入
		/// </summary>
		/// <param name="t">代入する文字列</param>
		/// <returns>代入された文字列</returns>
		NODISCARD constexpr string& assign(const string_view& t) {
			_string_data.assign(t._str);
			return *this;
		}

		/// <summary>
		/// 文字列を代入
		/// </summary>
		/// <param name="t">代入する文字列</param>
		/// <param name="pos">代入する文字列の開始位置</param>
		/// <param name="n">代入する文字列の長さ</param>
		/// <returns>代入された文字列</returns>
		NODISCARD constexpr string& assign(const string_view& t, size_type pos, size_type n = npos) {
			_string_data.assign(t._str, pos, n);
			return *this;
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <param name="pos1">挿入する位置</param>
		/// <param name="str">挿入する文字列</param>
		/// <returns>挿入された文字列</returns>
		NODISCARD constexpr string& insert(size_type pos1, const string& str) {
			_string_data.insert(pos1, str._string_data);
			return *this;
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <param name="pos1">挿入する位置</param>
		/// <param name="str">挿入する文字列</param>
		/// <param name="pos2">挿入する文字列の開始位置</param>
		/// <param name="n">挿入する文字列の長さ</param>
		/// <returns>挿入された文字列</returns>
		NODISCARD constexpr string& insert(size_type pos1, const string& str, size_type pos2, size_type n = npos) {
			_string_data.insert(pos1, str._string_data, pos2, n);
			return *this;
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <param name="pos">挿入する位置</param>
		/// <param name="s">挿入する文字列</param>
		/// <param name="n">挿入する文字列の長さ</param>
		/// <returns>挿入された文字列</returns>
		NODISCARD constexpr string& insert(size_type pos, const char32* s, size_type n) {
			_string_data.insert(pos, s, n);
			return *this;
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <param name="pos">挿入する位置</param>
		/// <param name="s">挿入する文字列</param>
		/// <returns>挿入された文字列</returns>
		NODISCARD constexpr string& insert(size_type pos, const char32* s) {
			_string_data.insert(pos, s);
			return *this;
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <param name="pos">挿入する位置</param>
		/// <param name="n">挿入する文字列の長さ</param>
		/// <param name="c">挿入する文字</param>
		/// <returns>挿入された文字列</returns>
		NODISCARD constexpr string& insert(size_type pos, size_type n, char32 c) {
			_string_data.insert(pos, n, c);
			return *this;
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <param name="p">挿入する位置</param>
		/// <param name="c">挿入する文字</param>
		/// <returns>挿入された文字列</returns>
		NODISCARD constexpr iterator insert(const_iterator p, char32 c) {
			return _string_data.insert(p, c);
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <param name="p">挿入する位置</param>
		/// <param name="n">挿入する文字列の長さ</param>
		/// <param name="c">挿入する文字</param>
		/// <returns>挿入された文字列</returns>
		NODISCARD constexpr iterator insert(const_iterator p, size_type n, char32 c) {
			return _string_data.insert(p, n, c);
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <param name="p">挿入する位置</param>
		/// <param name="first">挿入する文字列の開始位置</param>
		/// <param name="last">挿入する文字列の終了位置</param>
		/// <returns>挿入された文字列</returns>
		NODISCARD constexpr iterator insert(const_iterator p, iterator first, iterator last) {
			return _string_data.insert(p, first, last);
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <param name="p">挿入する位置</param>
		/// <param name="il">挿入する文字列</param>
		/// <returns>挿入された文字列</returns>
		NODISCARD constexpr iterator insert(const_iterator p, std::initializer_list<char32> il) {
			return _string_data.insert(p, il);
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <typeparam name="T">挿入する文字列の型</typeparam>
		/// <param name="pos1">挿入する位置</param>
		/// <param name="t">挿入する文字列</param>
		/// <returns>挿入された文字列</returns>
		template<class T>
		NODISCARD constexpr string& insert(size_type pos1, const string_view& t) {
			_string_data.insert(pos1, t._str);
			return *this;
		}

		/// <summary>
		/// 文字列を挿入
		/// </summary>
		/// <typeparam name="T">挿入する文字列の型</typeparam>
		/// <param name="pos1">挿入する位置</param>
		/// <param name="t">挿入する文字列</param>
		/// <param name="pos2">挿入する文字列の開始位置</param>
		/// <param name="n">挿入する文字列の長さ</param>
		/// <returns>挿入された文字列</returns>
		template<class T>
		NODISCARD constexpr string& insert(size_type pos1, const string_view& t, size_type pos2, size_type n = npos) {
			_string_data.insert(pos1, t._str, pos2, n);
			return *this;
		}

		/// <summary>
		/// 文字列を削除
		/// </summary>
		/// <param name="pos">削除する位置</param>
		/// <param name="n">削除する文字列の長さ</param>
		/// <returns>削除された文字列</returns>
		NODISCARD constexpr string& erase(size_type pos = 0, size_type n = npos) {
			_string_data.erase(pos, n);
			return *this;
		}

		/// <summary>
		/// 文字列を削除
		/// </summary>
		/// <param name="p">削除する位置</param>
		/// <returns>削除された文字列</returns>
		NODISCARD constexpr iterator erase(const_iterator p) {
			return _string_data.erase(p);
		}

		/// <summary>
		/// 文字列を削除
		/// </summary>
		/// <param name="first">削除する文字列の開始位置</param>
		/// <param name="last">削除する文字列の終了位置</param>
		/// <returns>削除された文字列</returns>
		NODISCARD constexpr iterator erase(const_iterator first, const_iterator last) {
			return _string_data.erase(first, last);
		}

		/// <summary>
		/// 文字列を削除
		/// </summary>
		constexpr void pop_back() {
			_string_data.pop_back();
		}

		/// <summary>
		/// 文字列を入れ替え
		/// </summary>
		/// <param name="str">入れ替える文字列</param>
		/// <returns>入れ替えられた文字列</returns>
		constexpr void swap(string& str) noexcept {
			_string_data.swap(str._string_data);
		}

		/// <summary>
		/// 文字列の先頭を取得
		/// </summary>
		/// <returns>文字列の先頭</returns>
		NODISCARD constexpr const_pointer c_str() const noexcept {
			return _string_data.c_str();
		}

		/// <summary>
		/// 文字列の先頭を取得
		/// </summary>
		/// <returns>文字列の先頭</returns>
		NODISCARD constexpr const_pointer data() const noexcept {
			return _string_data.data();
		}

		/// <summary>
		/// 文字列の先頭を取得
		/// </summary>
		/// <returns>文字列の先頭</returns>
		NODISCARD constexpr pointer data() noexcept {
			return _string_data.data();
		}

		/// <summary>
		/// アロケータを取得
		/// </summary>
		/// <returns>アロケータ</returns>
		NODISCARD constexpr allocator_type get_allocator() const noexcept {
			return _string_data.get_allocator();
		}

		/// <summary>
		/// 文字列をコピー
		/// </summary>
		/// <param name="s">コピー先</param>
		/// <param name="n">コピーする文字列の長さ</param>
		/// <param name="pos">コピーする文字列の開始位置</param>
		/// <returns>コピーした文字列長</returns>
		constexpr size_type copy(char32* s, size_type n, size_type pos = 0) const {
			return _string_data.copy(s, n, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>検索された文字列の位置</returns>
		NODISCARD constexpr size_type find(const string& str, size_type pos = 0) const noexcept {
			return _string_data.find(str._string_data, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <param name="n">検索する文字列の長さ</param>
		/// <returns>検索された文字列の位置</returns>
		NODISCARD constexpr size_type find(const char32* s, size_type pos, size_type n) const noexcept {
			return _string_data.find(s, pos, n);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>検索された文字列の位置</returns>
		NODISCARD constexpr size_type find(const char32* s, size_type pos = 0) const noexcept {
			return _string_data.find(s, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="c">検索する文字</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>検索された文字列の位置</returns>
		NODISCARD constexpr size_type find(char32 c, size_type pos = 0) const noexcept {
			return _string_data.find(c, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="str">検索する文字</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>検索された文字列の位置</returns>
		NODISCARD constexpr size_type find(const string_view str, size_type pos = 0) const noexcept {
			return _string_data.find(str._str, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>検索された文字列の位置</returns>
		NODISCARD constexpr size_type rfind(const string& str, size_type pos = npos) const noexcept {
			return _string_data.rfind(str._string_data, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <param name="n">検索する文字列の長さ</param>
		/// <returns>検索された文字列の位置</returns>
		NODISCARD constexpr size_type rfind(const char32* s, size_type pos, size_type n) const noexcept {
			return _string_data.rfind(s, pos, n);
		}

		/// <summary>
		/// 最後に現れる指定文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>検索された文字列の位置</returns>
		NODISCARD constexpr size_type rfind(const char32* s, size_type pos = npos) const noexcept {
			return _string_data.rfind(s, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字列を検索
		/// </summary>
		/// <param name="c">検索する文字</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>検索された文字列の位置</returns>
		NODISCARD constexpr size_type rfind(char32 c, size_type pos = npos) const noexcept {
			return _string_data.rfind(c, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>検索された文字列の位置</returns>
		NODISCARD constexpr size_type rfind(const string_view& str, size_type pos = npos) const noexcept {
			return _string_data.rfind(str._str, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれかの文字が出現する最初の場所</returns>
		NODISCARD constexpr size_type find_first_of(const string& str, size_type pos = 0) const noexcept {
			return _string_data.find_first_of(str._string_data, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <param name="n">検索する文字列の長さ</param>
		/// <returns>指定された文字列中のいずれかの文字が出現する最初の場所</returns>
		NODISCARD constexpr size_type find_first_of(const char32* s, size_type pos, size_type n) const noexcept {
			return _string_data.find_first_of(s, pos, n);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれかの文字が出現する最初の場所</returns>
		NODISCARD constexpr size_type find_first_of(const char32* s, size_type pos = 0) const noexcept {
			return _string_data.find_first_of(s, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="c">検索する文字</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれかの文字が出現する最初の場所</returns>
		NODISCARD constexpr size_type find_first_of(char32 c, size_type pos = 0) const noexcept {
			return _string_data.find_first_of(c, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれかの文字が出現する最初の場所</returns>
		NODISCARD constexpr size_type find_first_of(const string_view& str, size_type pos = 0) const noexcept {
			return _string_data.find_first_of(str._str, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれかの文字が出現する最後の場所</returns>
		NODISCARD constexpr size_type find_last_of(const string& str, size_type pos = npos) const noexcept {
			return _string_data.find_last_of(str._string_data, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <param name="n">検索する文字列の長さ</param>
		/// <returns>指定された文字列中のいずれかの文字が出現する最後の場所</returns>
		NODISCARD constexpr size_type find_last_of(const char32* s, size_type pos, size_type n) const noexcept {
			return _string_data.find_last_of(s, pos, n);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれかの文字が出現する最後の場所</returns>
		NODISCARD constexpr size_type find_last_of(const char32* s, size_type pos = npos) const noexcept {
			return _string_data.find_last_of(s, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="c">検索する文字</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれかの文字が出現する最後の場所</returns>
		NODISCARD constexpr size_type find_last_of(char32 c, size_type pos = npos) const noexcept {
			return _string_data.find_last_of(c, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれかの文字が出現する最後の場所</returns>
		NODISCARD constexpr size_type find_last_of(const string_view& str, size_type pos = npos) const noexcept {
			return _string_data.find_last_of(str._str, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれかの文字が出現しない最初の場所</returns>
		NODISCARD constexpr size_type find_first_not_of(const string& str, size_type pos = 0) const noexcept {
			return _string_data.find_first_not_of(str._string_data, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <param name="n">検索する文字列の長さ</param>
		/// <returns>指定された文字列中のいずれの文字も出現しない最初の場所</returns>
		NODISCARD constexpr size_type find_first_not_of(const char32* s, size_type pos, size_type n) const noexcept {
			return _string_data.find_first_not_of(s, pos, n);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれの文字も出現しない最初の場所</returns>
		NODISCARD constexpr size_type find_first_not_of(const char32* s, size_type pos = 0) const noexcept {
			return _string_data.find_first_not_of(s, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="c">検索する文字</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれの文字も出現しない最初の場所</returns>
		NODISCARD constexpr size_type find_first_not_of(char32 c, size_type pos = 0) const noexcept {
			return _string_data.find_first_not_of(c, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれの文字も出現しない最初の場所</returns>
		NODISCARD constexpr size_type find_first_not_of(const string_view& str, size_type pos = 0) const noexcept {
			return _string_data.find_first_not_of(str._str, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれの文字も出現しない最後の場所</returns>
		NODISCARD constexpr size_type find_last_not_of(const string& str, size_type pos = npos) const noexcept {
			return _string_data.find_last_not_of(str._string_data, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <param name="n">検索する文字列の長さ</param>
		/// <returns>指定された文字列中のいずれの文字も出現しない最後の場所</returns>
		NODISCARD constexpr size_type find_last_not_of(const char32* s, size_type pos, size_type n) const noexcept {
			return _string_data.find_last_not_of(s, pos, n);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="s">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれの文字も出現しない最後の場所</returns>
		NODISCARD constexpr size_type find_last_not_of(const char32* s, size_type pos = npos) const noexcept {
			return _string_data.find_last_not_of(s, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="c">検索する文字</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれの文字も出現しない最後の場所</returns>
		NODISCARD constexpr size_type find_last_not_of(char32 c, size_type pos = npos) const noexcept {
			return _string_data.find_last_not_of(c, pos);
		}

		/// <summary>
		/// 文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の開始位置</param>
		/// <returns>指定された文字列中のいずれの文字も出現しない最後の場所</returns>
		NODISCARD constexpr size_type find_last_not_of(const string_view& str, size_type pos = npos) const noexcept {
			return _string_data.find_last_not_of(str._str, pos);
		}

		/// <summary>
		/// 部分文字列を取得
		/// </summary>
		/// <param name="pos">取得する部分文字列の開始位置</param>
		/// <param name="n">取得する部分文字列の長さ</param>
		/// <returns>部分文字列</returns>
		NODISCARD string substr(size_type pos = 0, size_type n = npos) const {
			return string(_string_data.substr(pos, n));
		}
		
		/// <summary>
		/// 文字列を比較
		/// </summary>
		/// <param name="str">比較する文字列</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(const string& str) const noexcept {
			return _string_data.compare(str._string_data);
		}

		/// <summary>
		/// 文字列を比較
		/// </summary>
		/// <param name="pos1">比較する文字列の開始位置</param>
		/// <param name="n1">比較する文字列の長さ</param>
		/// <param name="str">比較する文字列</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(size_type pos1, size_type n1, const string& str) const {
			return _string_data.compare(pos1, n1, str._string_data);
		}

		/// <summary>
		/// 文字列を比較
		/// </summary>
		/// <param name="pos1">比較する文字列の開始位置</param>
		/// <param name="n1">比較する文字列の長さ</param>
		/// <param name="str">比較する文字列</param>
		/// <param name="pos2">比較する文字列の開始位置</param>
		/// <param name="n2">比較する文字列の長さ</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(size_type pos1, size_type n1, const string& str, size_type pos2, size_type n2) const {
			return _string_data.compare(pos1, n1, str._string_data, pos2, n2);
		}

		/// <summary>
		/// 文字列を比較
		/// </summary>
		/// <param name="s">比較する文字列</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(const char32* s) const {
			return _string_data.compare(s);
		}

		/// <summary>
		/// 文字列を比較
		/// </summary>
		/// <param name="pos1">比較する文字列の開始位置</param>
		/// <param name="n1">比較する文字列の長さ</param>
		/// <param name="s">比較する文字列</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(size_type pos1, size_type n1, const char32* s) const {
			return _string_data.compare(pos1, n1, s);
		}

		/// <summary>
		/// 文字列を比較
		/// </summary>
		/// <param name="pos1">比較する文字列の開始位置</param>
		/// <param name="n1">比較する文字列の長さ</param>
		/// <param name="s">比較する文字列</param>
		/// <param name="n2">比較する文字列の長さ</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(size_type pos1, size_type n1, const char32* s, size_type n2) const {
			return _string_data.compare(pos1, n1, s, n2);
		}

		/// <summary>
		/// 文字列を比較
		/// </summary>
		/// <param name="str">比較する文字列</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(const string_view& str) const noexcept {
			return _string_data.compare(str._str);
		}

		/// <summary>
		/// 文字列を比較
		/// </summary>
		/// <param name="pos1">比較する文字列の開始位置</param>
		/// <param name="n1">比較する文字列の長さ</param>
		/// <param name="str">比較する文字列</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(size_type pos1, size_type n1, const string_view& str) const {
			return _string_data.compare(pos1, n1, str._str);
		}

		/// <summary>
		/// 文字列を比較
		/// </summary>
		/// <param name="pos1">比較する文字列の開始位置</param>
		/// <param name="n1">比較する文字列の長さ</param>
		/// <param name="str">比較する文字列</param>
		/// <param name="pos2">比較する文字列の開始位置</param>
		/// <param name="n2">比較する文字列の長さ</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(size_type pos1, size_type n1, const string_view& str, size_type pos2, size_type n2) const {
			return _string_data.compare(pos1, n1, str._str, pos2, n2);
		}

		/// <summary>
		/// 指定の文字列で始まるか判定
		/// </summary>
		/// <param name="str">判定する文字列</param>
		/// <returns>指定の文字列で始まるか</returns>
		NODISCARD constexpr bool starts_with(const string& str) const noexcept {
			return _string_data.starts_with(str._string_data);
		}

		/// <summary>
		/// 指定の文字列で始まるか判定
		/// </summary>
		/// <param name="str">判定する文字列</param>
		/// <returns>指定の文字列で始まるか</returns>
		NODISCARD constexpr bool starts_with(const string_view& str) const noexcept {
			return _string_data.starts_with(str._str);
		}

		/// <summary>
		/// 指定の文字列で始まるか判定
		/// </summary>
		/// <param name="str">判定する文字列</param>
		/// <returns>指定の文字列で始まるか</returns>
		NODISCARD constexpr bool starts_with(const char32* str) const noexcept {
			return _string_data.starts_with(str);
		}

		/// <summary>
		/// 指定の文字で始まるか判定
		/// </summary>
		/// <param name="c">判定する文字</param>
		/// <returns>指定の文字で始まるか</returns>
		NODISCARD constexpr bool starts_with(char32 c) const noexcept {
			return _string_data.starts_with(c);
		}

		/// <summary>
		/// 指定の文字列で終わるか判定
		/// </summary>
		/// <param name="str">判定する文字列</param>
		/// <returns>指定の文字列で終わるか</returns>
		NODISCARD constexpr bool ends_with(const string& str) const noexcept {
			return _string_data.ends_with(str._string_data);
		}

		/// <summary>
		/// 指定の文字列で終わるか判定
		/// </summary>
		/// <param name="str">判定する文字列</param>
		/// <returns>指定の文字列で終わるか</returns>
		NODISCARD constexpr bool ends_with(const string_view& str) const noexcept {
			return _string_data.ends_with(str._str);
		}

		/// <summary>
		/// 指定の文字列で終わるか判定
		/// </summary>
		/// <param name="str">判定する文字列</param>
		/// <returns>指定の文字列で終わるか</returns>
		NODISCARD constexpr bool ends_with(const char32* str) const noexcept {
			return _string_data.ends_with(str);
		}

		/// <summary>
		/// 指定の文字で終わるか判定
		/// </summary>
		/// <param name="c">判定する文字</param>
		/// <returns>指定の文字で終わるか</returns>
		NODISCARD constexpr bool ends_with(char32 c) const noexcept {
			return _string_data.ends_with(c);
		}

		/// <summary>
		/// 特定の文字列が含まれるか判定
		/// </summary>
		/// <param name="str">判定する文字列</param>
		/// <returns>特定の文字列が含まれるか</returns>
		NODISCARD constexpr bool contains(const string_view& str) const noexcept {
			return find(str) != npos;
		}

		/// <summary>
		/// 特定の文字が含まれるか判定
		/// </summary>
		/// <param name="c">判定する文字</param>
		/// <returns>特定の文字が含まれるか</returns>
		NODISCARD constexpr bool contains(char32 c) const noexcept {
			return find(c) != npos;
		}

		/// <summary>
		/// 特定の文字列が含まれるか判定
		/// </summary>
		/// <param name="str">判定する文字列</param>
		/// <returns>特定の文字列が含まれるか</returns>
		NODISCARD constexpr bool contains(const_pointer str) const noexcept {
			return find(str) != npos;
		}

#if __cpp_lib_three_way_comparison

		/// <summary>
		/// 3項比較演算子
		/// </summary>
		/// <param name="rhs">比較対象</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr std::strong_ordering operator <=>(const string& rhs) const noexcept = default;

#else
		/// <summary>
		/// 比較演算子
		/// </summary>
		/// <param name="rhs">比較対象</param>
		/// <returns>比較結果</returns>
		NODISCARD friend constexpr bool operator ==(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) == 0);
		}

		/// <summary>
		/// 比較演算子
		/// </summary>
		/// <param name="rhs">比較対象</param>
		/// <returns>比較結果</returns>
		NODISCARD friend constexpr bool operator !=(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) != 0);
		}

		/// <summary>
		/// 比較演算子
		/// </summary>
		/// <param name="rhs">比較対象</param>
		/// <returns>比較結果</returns>
		NODISCARD friend constexpr bool operator <(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) < 0);
		}

		/// <summary>
		/// 比較演算子
		/// </summary>
		/// <param name="rhs">比較対象</param>
		/// <returns>比較結果</returns>
		NODISCARD friend constexpr bool operator <=(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) <= 0);
		}

		/// <summary>
		/// 比較演算子
		/// </summary>
		/// <param name="rhs">比較対象</param>
		/// <returns>比較結果</returns>
		NODISCARD friend constexpr bool operator >(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) > 0);
		}

		/// <summary>
		/// 比較演算子
		/// </summary>
		/// <param name="rhs">比較対象</param>
		/// <returns>比較結果</returns>
		NODISCARD friend constexpr bool operator >=(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) >= 0);
		}

#endif

		size_t hash() const noexcept {
			return std::hash<string_type>()(_string_data);
		}
	private:
		string_type _string_data;
	};

	//constexpr bool operator==(const string& rhs, const string& lhs);	  //
	//constexpr bool operator==(const string& lhs, const string::str& rhs); //
	//constexpr bool operator==(const string::str& lhs, const string& rhs); //
	//constexpr bool operator==(const char* lhs, const string& rhs);		//
	//constexpr bool operator==(const string& lhs, const char* rhs);		//
	//template<class string_t>
	//bool operator==(const string& lhs, const string_t& rhs); //
	//template<class string_t>
	//bool operator==(const string_t& lhs, const string& rhs); //
	//template<class char_t>
	//bool operator==(const string& lhs, const char_t* rhs); //
	//template<class char_t>
	//bool operator==(const char_t* lhs, const string& rhs); //
	//
	//
	//constexpr std::strong_ordering operator<=>(const string& rhs, const string& lhs);//
	//constexpr std::strong_ordering operator<=>(const string& lhs, const string::str& rhs);//
	//constexpr std::strong_ordering operator<=>(const string::str& lhs, const string& rhs);//
	//constexpr std::strong_ordering operator<=>(const char* lhs, const string& rhs);//
	//constexpr std::strong_ordering operator<=>(const string& lhs, const char* rhs);//
	//template<class string_t>
	//std::strong_ordering operator<=>(const string& lhs, const string_t& rhs);//
	//template<class string_t>
	//std::strong_ordering operator<=>(const string_t& lhs, const string& rhs);//
	//template<class char_t>
	//std::strong_ordering operator<=>(const string& lhs, const char_t* rhs);//
	//template<class char_t>
	//std::strong_ordering operator<=>(const char_t* lhs, const string& rhs);//

	string operator+(const string& lhs, const string& rhs);//
	string operator+(const string& lhs, const string::str& rhs);//
	string operator+(const string::string_type& lhs, const string& rhs);//
	string operator+(string&& lhs, const string& rhs);//
	string operator+(const string& lhs, string&& rhs);//
	string operator+(string&& lhs, string&& rhs);//
	string operator+(const char* lhs, const string& rhs);
	string operator+(const char* lhs, string&& rhs);
	string operator+(char lhs, const string& rhs);
	string operator+(char lhs, string&& rhs);
	string operator+(const string& lhs, const char* rhs);
	string operator+(string&& lhs, const char* rhs);
	string operator+(const string& lhs, char rhs);
	string operator+(string&& lhs, char rhs);
	template<class string_t>
	string operator+(const string& lhs, const string_t& rhs);//
	template<class string_t>
	string operator+(const string_t& lhs, const string& rhs); //
	template<class string_t>
	string operator+(string&& lhs, const string_t& rhs);//
	template<class string_t>
	string operator+(const string_t& lhs, string&& rhs);//
	template<class string_t>
	string operator+(string_t&& lhs, string&& rhs);//
	template<class string_t>
	string operator+(string&& lhs, string_t&& rhs); //
	template<class char_t>
	string operator+(const char_t* lhs, const string& rhs);
	template<class char_t>
	string operator+(const char_t* lhs, string&& rhs);
	template<class char_t>
	string operator+(char_t lhs, const string& rhs);
	template<class char_t>
	string operator+(char_t lhs, string&& rhs);
	template<class char_t>
	string operator+(const string& lhs, const char_t* rhs);
	template<class char_t>
	string operator+(string&& lhs, const char_t* rhs);
	template<class char_t>
	string operator+(const string& lhs, char_t rhs);
	template<class char_t>
	string operator+(string&& lhs, char_t rhs);

	
} // namespace suika

namespace std {
	template <>
	inline void swap(suika::string& a, suika::string& b) noexcept {
		a.swap(b);
	}

	template<>
	struct formatter<suika::string> : formatter<suika::string::str, suika::string::str::value_type> {
		auto format(suika::string str, format_context& ctx) const {
			return formatter<suika::string::str, suika::string::str::value_type>::format(str.to_string(), ctx);
		}
	};

	template<>
	struct hash<suika::string> {
	public:
		size_t operator()(const suika::string& data)const {
			return hash<suika::string::string_type>()(data.to_u32string());
		}
	};
}

#include "detail/string.ipp"

#endif