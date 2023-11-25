// -----------------------------------------------------------
// 
// string_view
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

#include <string_view>
#include <string>
#include <format>

#include "def.h"
#include "codecvt.h"

namespace suika {
	class string;
	class string_view {
		friend string;
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

		/// <summary>
		/// 空の文字列ビューを作成
		/// </summary>
		constexpr string_view() noexcept = default;

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="str">コピーする文字列ビュー</param>
		constexpr string_view(const string_view& str) noexcept = default;

		/// <summary>
		/// UTF32文字列から文字列ビューを作成
		/// </summary>
		/// <param name="str">文字列</param>
		constexpr string_view(const char_t* str) noexcept {
			_str = string_view_type(str);
		}
#if _HAS_CXX23
		constexpr string_view(nullptr_t) = delete;
#endif
		/// <summary>
		/// UTF32文字列とその長さから文字列ビューを作成
		/// </summary>
		/// <param name="str">文字列</param>
		/// <param name="len">長さ</param>
		constexpr string_view(const char_t* str, size_type len) noexcept {
			_str = string_view_type(str, len);
		}

		/// <summary>
		/// UTF32文字列イテレータから文字列ビューを作成
		/// </summary>
		/// <typeparam name="_it">イテレータ</typeparam>
		/// <typeparam name="_end">イテレータ</typeparam>
		/// <param name="begin">始端</param>
		/// <param name="end">終端</param>
		template<class _it, class _end>
		constexpr string_view(_it begin, _end end) noexcept(noexcept(end - begin)) {
			_str = string_view_type(begin, end);
		}

		/// <summary>
		/// UTF32文字列ビューから文字列ビューを作成
		/// </summary>
		/// <param name="str">文字列ビュー</param>
		constexpr string_view(const string_view_type& str) noexcept {
			_str = str;
		}

		/// <summary>
		/// ムーブコンストラクタ
		/// </summary>
		/// <param name="str">文字列ビュー</param>
		constexpr string_view(string_view&& str) noexcept = default;

		/// <summary>
		/// コピー代入演算子
		/// </summary>
		/// <param name="str">文字列ビュー</param>
		/// <returns></returns>
		constexpr string_view& operator=(const string_view& str) noexcept = default;

		/// <summary>
		/// 文字列を変換
		/// </summary>
		/// <returns>shift-jis文字列</returns>
		NODISCARD str to_string() const;

		/// <summary>
		/// 文字列を変換
		/// </summary>
		/// <returns>ワイド文字列</returns>
		NODISCARD wstr to_wstring() const;

		/// <summary>
		/// 文字列を変換
		/// </summary>
		/// <returns>UTF8文字列</returns>
		NODISCARD utf8 to_utf8() const;

		/// <summary>
		/// 文字列を変換
		/// </summary>
		/// <returns>UTF16文字列</returns>
		NODISCARD utf16 to_utf16() const;

		/// <summary>
		/// 文字列を変換
		/// </summary>
		/// <returns>UTF32文字列</returns>
		NODISCARD utf32 to_utf32() const;

#pragma region STD_FUNCTION
		/// <summary>
		/// 始端イテレータを取得
		/// </summary>
		/// <returns>始端イテレータ</returns>
		NODISCARD constexpr const_iterator begin() const noexcept {
			return _str.begin();
		}

		/// <summary>
		/// 終端イテレータを取得
		/// </summary>
		/// <returns>終端イテレータ</returns>
		NODISCARD constexpr const_iterator end() const noexcept {
			return _str.end();
		}

		/// <summary>
		/// 始端イテレータを取得
		/// </summary>
		/// <returns>始端イテレータ</returns>
		NODISCARD constexpr const_iterator cbegin() const noexcept {
			return _str.cbegin();
		}

		/// <summary>
		/// 終端イテレータを取得
		/// </summary>
		/// <returns>終端イテレータ</returns>
		NODISCARD constexpr const_iterator cend() const noexcept {
			return _str.cend();
		}

		/// <summary>
		/// 逆順始端イテレータを取得
		/// </summary>
		/// <returns>逆順始端イテレータ</returns>
		NODISCARD constexpr const_reverse_iterator rbegin() const noexcept {
			return _str.rbegin();
		}

		/// <summary>
		/// 逆順終端イテレータを取得
		/// </summary>
		/// <returns>逆順終端イテレータ</returns>
		NODISCARD constexpr const_reverse_iterator rend() const noexcept {
			return _str.rend();
		}

		/// <summary>
		/// 逆順始端イテレータを取得
		/// </summary>
		/// <returns>逆順始端イテレータ</returns>
		NODISCARD constexpr const_reverse_iterator crbegin() const noexcept {
			return _str.crbegin();
		}

		/// <summary>
		/// 逆順終端イテレータを取得
		/// </summary>
		/// <returns>逆順終端イテレータ</returns>
		NODISCARD constexpr const_reverse_iterator crend() const noexcept {
			return _str.crend();
		}

		/// <summary>
		/// 文字列の長さを取得
		/// </summary>
		/// <returns>文字列の長さ</returns>
		NODISCARD constexpr size_type size() const noexcept {
			return _str.size();
		}

		/// <summary>
		/// 文字列の長さを取得
		/// </summary>
		/// <returns>文字列の長さ</returns>
		NODISCARD constexpr size_type length() const noexcept {
			return _str.length();
		}

		/// <summary>
		/// 文字列の長さを取得
		/// </summary>
		/// <returns>文字列の長さ</returns>
		NODISCARD constexpr size_type max_size() const noexcept {
			return _str.max_size();
		}

		/// <summary>
		/// 文字列が空かどうかを取得
		/// </summary>
		/// <returns>文字列が空かどうか</returns>
		NODISCARD constexpr bool empty() const noexcept {
			return _str.empty();
		}
		
		/// <summary>
		/// 任意の位置の文字を取得
		/// </summary>
		/// <param name="pos"></param>
		/// <returns>pos番目の文字</returns>
		NODISCARD constexpr const_reference operator[](size_type pos) const noexcept {
			return _str[pos];
		}

		/// <summary>
		/// 任意の位置の文字を取得
		/// </summary>
		/// <param name="pos"></param>
		/// <returns>pos番目の文字</returns>
		NODISCARD constexpr const_reference at(size_type pos) const {
			return _str.at(pos);
		}

		/// <summary>
		/// 文字列の先頭を取得
		/// </summary>
		/// <returns>文字列の先頭</returns>
		NODISCARD constexpr const_reference front() const noexcept {
			return _str.front();
		}

		/// <summary>
		/// 文字列の末尾を取得
		/// </summary>
		/// <returns>文字列の末尾</returns>
		NODISCARD constexpr const_reference back() const noexcept {
			return _str.back();
		}

		/// <summary>
		/// 文字配列表現を取得
		/// </summary>
		/// <returns>文字配列表現</returns>
		NODISCARD constexpr const_pointer data() const noexcept {
			return _str.data();
		}

		/// <summary>
		/// 先頭の文字を削除
		/// </summary>
		/// <param name="n">削除する文字数</param>
		NODISCARD constexpr void remove_prefix(size_type n) noexcept {
			_str.remove_prefix(n);
		}

		/// <summary>
		/// 末尾の文字を削除
		/// </summary>
		/// <param name="n">削除する文字数</param>
		NODISCARD constexpr void remove_suffix(size_type n) noexcept {
			_str.remove_suffix(n);
		}

		/// <summary>
		/// 他のstring_viewとデータを入れ替える
		/// </summary>
		/// <param name="str">入れ替えるstring_view</param>
		NODISCARD constexpr void swap(string_view& str) noexcept {
			_str.swap(str._str);
		}

		/// <summary>
		/// 他の文字列に、自身の文字列をコピーする
		/// </summary>
		/// <param name="dest">コピー先</param>
		/// <param name="count">コピーする文字数</param>
		/// <param name="pos">コピーする文字列の位置</param>
		/// <returns>コピーした文字数</returns>
		NODISCARD constexpr size_type copy(char_t* dest, size_type count, size_type pos = 0) const {
			return _str.copy(dest, count, pos);
		}

		/// <summary>
		/// 文字列の一部を取得
		/// </summary>
		/// <param name="pos">取得する文字列の位置</param>
		/// <param name="count">取得する文字数</param>
		/// <returns>取得した文字列</returns>
		NODISCARD constexpr string_view substr(size_type pos = 0, size_type count = string_view::npos) const {
			return _str.substr(pos, count);
		}

		/// <summary>
		/// 文字列の比較
		/// </summary>
		/// <param name="str">比較する文字列</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(string_view str) const noexcept {
			return _str.compare(str._str);
		}

		/// <summary>
		/// 文字列の比較
		/// </summary>
		/// <param name="pos">比較する文字列の位置</param>
		/// <param name="count">比較する文字数</param>
		/// <param name="str">比較する文字列</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(size_type pos, size_type count, string_view str) const {
			return _str.compare(pos, count, str._str);
		}

		/// <summary>
		/// 文字列の比較
		/// </summary>
		/// <param name="pos">比較する文字列の位置</param>
		/// <param name="count">比較する文字数</param>
		/// <param name="str">比較する文字列</param>
		/// <param name="subpos">比較する文字列の位置</param>
		/// <param name="subcount">比較する文字数</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(size_type pos, size_type count, string_view str, size_type subpos, size_type subcount) const {
			return _str.compare(pos, count, str._str, subpos, subcount);
		}

		/// <summary>
		/// 文字列の比較
		/// </summary>
		/// <param name="str">比較する文字列</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr int compare(const_pointer str) const {
			return _str.compare(str);
		}

		/// <summary>
		/// 文字列の比較
		/// </summary>
		/// <param name="pos">比較する文字列の位置</param>
		/// <param name="count">比較する文字数</param>
		/// <param name="str">比較する文字列</param>
		NODISCARD constexpr int compare(size_type pos, size_type count, const_pointer str) const {
			return _str.compare(pos, count, str);
		}

		/// <summary>
		/// 文字列の比較
		/// </summary>
		/// <param name="pos">比較する文字列の位置</param>
		/// <param name="count">比較する文字数</param>
		/// <param name="str">比較する文字列</param>
		/// <param name="subcount">比較する文字数</param>
		NODISCARD constexpr int compare(size_type pos, size_type count, const_pointer str, size_type subcount) const {
			return _str.compare(pos, count, str, subcount);
		}

		/// <summary>
		/// 指定の文字列で始まるか判定
		/// </summary>
		/// <param name="str">初めの文字列</param>
		/// <returns>指定の文字列で始まるか</returns>
		NODISCARD constexpr bool starts_with(string_view str) const noexcept {
			return _str.starts_with(str._str);
		}

		/// <summary>
		/// 指定の文字列で始まるか判定
		/// </summary>
		/// <param name="str">初めの文字</param>
		/// <returns>指定の文字列で始まるか</returns>
		NODISCARD constexpr bool starts_with(char_t str) const noexcept {
			return _str.starts_with(str);
		}

		/// <summary>
		/// 指定の文字列で始まるか判定
		/// </summary>
		/// <param name="str">初めの文字列</param>
		/// <returns>指定の文字列で始まるか</returns>
		NODISCARD constexpr bool starts_with(const_pointer str) const noexcept {
			return _str.starts_with(str);
		}

		/// <summary>
		/// 指定の文字列で終わるか判定
		/// </summary>
		/// <param name="str">終わりの文字列</param>
		/// <returns>指定の文字列で終わるか</returns>
		NODISCARD constexpr bool ends_with(string_view str) const noexcept {
			return _str.ends_with(str._str);
		}

		/// <summary>
		/// 指定の文字列で終わるか判定
		/// </summary>
		/// <param name="str">終わりの文字</param>
		/// <returns>指定の文字列で終わるか</returns>
		NODISCARD constexpr bool ends_with(char_t str) const noexcept {
			return _str.ends_with(str);
		}

		/// <summary>
		/// 指定の文字列で終わるか判定
		/// </summary>
		/// <param name="str">終わりの文字列</param>
		/// <returns>指定の文字列で終わるか</returns>
		NODISCARD constexpr bool ends_with(const_pointer str) const noexcept {
			return _str.ends_with(str);
		}

		/// <summary>
		/// 指定の文字列を含むか判定
		/// </summary>
		/// <param name="str">含む文字列</param>
		/// <returns>指定の文字列を含むか</returns>
		NODISCARD constexpr bool contains(string_view str) const noexcept {
			return _str.find(str._str) != string_view::npos;
		}

		/// <summary>
		/// 指定の文字を含むか判定
		/// </summary>
		/// <param name="str">含む文字</param>
		/// <returns>指定の文字を含むか</returns>
		NODISCARD constexpr bool contains(char_t str) const noexcept {
			return _str.find(str) != string_view::npos;
		}

		/// <summary>
		/// 指定の文字列を含むか判定
		/// </summary>
		/// <param name="str">含む文字列</param>
		/// <returns>指定の文字列を含むか</returns>
		NODISCARD constexpr bool contains(const_pointer str) const {
			return _str.find(str) != string_view::npos;
		}

		/// <summary>
		/// 指定の文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posから、*thisに含まれる部分文字列strが最初に現れる位置</returns>
		NODISCARD constexpr size_type find(string_view str, size_type pos = 0) const noexcept {
			return _str.find(str._str, pos);
		}

		/// <summary>
		/// 指定の文字列を検索
		/// </summary>
		/// <param name="c">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posから、*thisに含まれる文字cが最初に現れる位置</returns>
		NODISCARD constexpr size_type find(char_t c, size_type pos = 0) const noexcept {
			return _str.find(c, pos);
		}

		/// <summary>
		/// 指定の文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <param name="n">検索する文字数</param>
		/// <returns> 指定した位置posから、*thisに含まれる部分文字列strの先頭n文字が最初に現れる位置</returns>
		NODISCARD constexpr size_type find(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.find(str, pos, n);
		}

		/// <summary>
		/// 指定の文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posから、*thisに含まれる部分文字列strが最初に現れる位置</returns>
		NODISCARD constexpr size_type find(const_pointer str, size_type pos) const noexcept {
			return _str.find(str, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posより前で、*thisに含まれる部分文字列strが最後に現れる位置</returns>
		NODISCARD constexpr size_type rfind(string_view str, size_type pos) const noexcept {
			return _str.rfind(str._str, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字列を検索
		/// </summary>
		/// <param name="c">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posより前で、*thisに含まれる文字cが最後に現れる位置</returns>
		NODISCARD constexpr size_type rfind(char_t c, size_type pos) const noexcept {
			return _str.rfind(c, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <param name="n">検索する文字数</param>
		/// <returns>指定した位置posより前で、*thisに含まれる部分文字列strの先頭n文字が最後に現れる位置</returns>
		NODISCARD constexpr size_type rfind(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.rfind(str, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字列を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posより前で、*thisに含まれる部分文字列strが最後に現れる位置</returns>
		NODISCARD constexpr size_type rfind(const_pointer str, size_type pos = 0) const noexcept{
			return _str.rfind(str, pos);
		}

		/// <summary>
		/// 最初に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posから、文字列str内のいずれかの文字が最初に現れる位置</returns>
		NODISCARD constexpr size_type find_first_of(string_view str, size_type pos = 0) const noexcept {
			return _str.find_first_of(str._str, pos);
		}

		/// <summary>
		/// 最初に現れる指定文字を検索
		/// </summary>
		/// <param name="c">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posから、文字cが最初に現れる位置</returns>
		NODISCARD constexpr size_type find_first_of(char_t c, size_type pos = 0) const noexcept {
			return _str.find_first_of(c, pos);
		}

		/// <summary>
		/// 最初に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <param name="n">検索する文字数</param>
		/// <returns> 指定した位置posから、文字列strの先頭n文字のいずれかの文字が最初に現れる位置</returns>
		NODISCARD constexpr size_type find_first_of(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.find_first_of(str, pos, n);
		}

		/// <summary>
		/// 最初に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posから、文字列str内のいずれかの文字が最初に現れる位置</returns>
		NODISCARD constexpr size_type find_first_of(const_pointer str, size_type pos) const noexcept {
			return _str.find_first_of(str, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posより前で、文字列str内のいずれかの文字が最後に現れる位置</returns>
		NODISCARD constexpr size_type find_last_of(string_view str, size_type pos = 0) const noexcept {
			return _str.find_last_of(str._str, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字を検索
		/// </summary>
		/// <param name="c">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posより前で、文字cが最後に現れる位置</returns>
		NODISCARD constexpr size_type find_last_of(char_t c, size_type pos = 0) const noexcept {
			return _str.find_last_of(c, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <param name="n">検索する文字数</param>
		/// <returns> 指定した位置posより前で、文字列strの先頭n文字のいずれかの文字が最後に現れる位置</returns>
		NODISCARD constexpr size_type find_last_of(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.find_last_of(str, pos, n);
		}

		/// <summary>
		/// 最後に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posより前で、文字列str内のいずれかの文字が最後に現れる位置</returns>
		NODISCARD constexpr size_type find_last_of(const_pointer str, size_type pos) const noexcept {
			return _str.find_last_of(str, pos);
		}

		/// <summary>
		/// 最初に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posから、文字列str内のいずれの文字にも一致しない位置</returns>
		NODISCARD constexpr size_type find_first_not_of(string_view str, size_type pos = 0) const noexcept {
			return _str.find_first_not_of(str._str, pos);
		}

		/// <summary>
		/// 最初に現れる指定文字を検索
		/// </summary>
		/// <param name="c">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posから、文字cに一致しない最初の位置</returns>
		NODISCARD constexpr size_type find_first_not_of(char_t c, size_type pos = 0) const noexcept {
			return _str.find_first_not_of(c, pos);
		}

		/// <summary>
		/// 最初に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <param name="n">検索する文字数</param>
		/// <returns> 指定した位置posから、文字列strの先頭n文字のいずれかの文字にも一致しない最初の位置</returns>
		NODISCARD constexpr size_type find_first_not_of(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.find_first_not_of(str, pos, n);
		}

		/// <summary>
		/// 最初に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posから、文字列str内のいずれかの文字にも一致しない最初の位置</returns>
		NODISCARD constexpr size_type find_first_not_of(const_pointer str, size_type pos) const noexcept {
			return _str.find_first_not_of(str, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posより前で、文字列str内のいずれかの文字にも一致しない最後の位置</returns>
		NODISCARD constexpr size_type find_last_not_of(string_view str, size_type pos = 0) const noexcept {
			return _str.find_last_not_of(str._str, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字を検索
		/// </summary>
		/// <param name="c">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posより前で、文字cに一致しない最後の位置</returns>
		NODISCARD constexpr size_type find_last_not_of(char_t c, size_type pos = 0) const noexcept {
			return _str.find_last_not_of(c, pos);
		}

		/// <summary>
		/// 最後に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <param name="n">検索する文字数</param>
		/// <returns> 指定した位置posより前で、文字列strの先頭n文字のいずれかの文字にも一致しない最後の位置</returns>
		NODISCARD constexpr size_type find_last_not_of(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.find_last_not_of(str, pos, n);
		}

		/// <summary>
		/// 最後に現れる指定文字を検索
		/// </summary>
		/// <param name="str">検索する文字列</param>
		/// <param name="pos">検索する文字列の位置</param>
		/// <returns>指定した位置posより前で、文字列str内のいずれかの文字にも一致しない最後の位置</returns>
		NODISCARD constexpr size_type find_last_not_of(const_pointer str, size_type pos) const noexcept {
			return _str.find_last_not_of(str, pos);
		}
#pragma endregion
#if __cpp_lib_three_way_comparison

		/// <summary>
		/// 3項比較演算子
		/// </summary>
		/// <param name="rhs">比較対象</param>
		/// <returns>比較結果</returns>
		NODISCARD constexpr std::strong_ordering operator <=>(const string_view& rhs) const noexcept = default;

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

		size_t hash() const noexcept{
			return std::hash<string_view_type>()(_str);
		}
	private:
		string_view_type _str;
	};
}

namespace std {
	template <>
	inline void swap(suika::string_view& a, suika::string_view& b) noexcept {
		a.swap(b);
	}

	template <>
	struct hash<suika::string_view> {
		[[nodiscard]]
		size_t operator ()(const suika::string_view& value) const noexcept {
			return value.hash();
		}
	};

	template<>
	struct formatter<suika::string_view> : formatter<suika::string_view::str, suika::string_view::str::value_type> {
		auto format(suika::string_view str, format_context& ctx) const {
			return formatter<suika::string_view::str, suika::string_view::str::value_type>::format(str.to_string(), ctx);
		}
	};
}