/**
* @file text.h
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

		using string_type			= wstr;
		using string_view_type	   = str_view;

		using size_type = string_type::size_type;

		static constexpr auto npos = string_type::npos;

		string();

		string(const string& other);
		string& operator=(const string& other);
		string(const string& other, size_type pos);
		string(const string& other, size_type pos, size_type count);
		string(string&& other) noexcept;

		string(const utf8& s);
		string& operator=(const utf8& other);
		string(const utf8& s, size_type pos);
		string(const utf8& s, size_type pos, size_type count);
		string(const utf16& s);
		string& operator=(const utf16& other);
		string(const utf16& s, size_type pos);
		string(const utf16& s, size_type pos, size_type count);
		string(const utf32& s);
		string& operator=(const utf32& other);
		string(const utf32& s, size_type pos);
		string(const utf32& s, size_type pos, size_type count);
		string(const str& s);
		string& operator=(const str& other);
		string(const str& s, size_type pos);
		string(const str& s, size_type pos, size_type count);
		string(const wstr& s);
		string& operator=(const wstr& other);
		string(const wstr& s, size_type pos);
		string(const wstr& s, size_type pos, size_type count);
		string(const char8* s);
		string& operator=(const char8* other);
		string(const char8* s, size_type count);
		string(const char16* s);
		string& operator=(const char16* other);
		string(const char16* s, size_type count);
		string(const char32* s);
		string& operator=(const char32* other);
		string(const char32* s, size_type count);
		string(const char* s);
		string& operator=(const char* other);
		string(const char* s, size_type count);
		string(const wchar_t* s);
		string& operator=(const wchar_t* other);
		string(const wchar_t* s, size_type count);
		string(std::initializer_list<char8> il);
		string& operator=(std::initializer_list<char8> il);
		string(std::initializer_list<char16> il);
		string& operator=(std::initializer_list<char16> il);
		string(std::initializer_list<char32> il);
		string& operator=(std::initializer_list<char32> il);
		string(std::initializer_list<char> il);
		string& operator=(std::initializer_list<char> il);
		string(std::initializer_list<wchar_t> il);
		string& operator=(std::initializer_list<wchar_t> il);
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
		
		bool				   operator==(const string& str) const;
		bool				 operator==(const utf8& str) const;
		bool				   operator==(const utf16& str) const;
		bool				 operator==(const utf32& str) const;
		bool				   operator==(const str& str) const;
		bool				 operator==(const wstr& str) const;
		bool				   operator==(const char8* str) const;
		bool				 operator==(const char16* str) const;
		bool				 operator==(const char32* str) const;
		bool				   operator==(const char* str) const;
		bool				   operator==(const wchar_t* str) const;
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
		utf8  to_u8string() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF16文字列</returns>
		utf16 to_u16string() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF32文字列</returns>
		utf32 to_u32string() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>文字列</returns>
		str	to_string() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>ワイド文字列</returns>
		wstr  to_wstring() const;

		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF8ビュー文字列</returns>
		utf8_view		to_u8string_view() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF16ビュー文字列</returns>
		utf16_view	to_u16string_view() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>UTF32ビュー文字列</returns>
		utf32_view	to_u32string_view() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>ビュー文字列</returns>
		str_view		to_string_view() const;
		/// <summary>
		/// 文字コードを変換
		/// </summary>
		/// <returns>ワイドビュー文字列</returns>
		wstr_view		to_wstring_view() const;

		/// <summary>
		/// 文字列を分割
		/// </summary>
		/// <param name="split_char">区切り文字</param>
		/// <param name="is_contain_lastempty">区切り文字が最後にある場合、最後の空白を含むか</param>
		/// <returns>分割された文字列</returns>
		std::vector<utf8>  split(char8 split_char, bool is_contain_lastempty = false) const;
		/// <summary>
		/// 文字列を分割
		/// </summary>
		/// <param name="split_char">区切り文字</param>
		/// <param name="is_contain_lastempty">区切り文字が最後にある場合、最後の空白を含むか</param>
		/// <returns>分割された文字列</returns>
		std::vector<utf16> split(char16 split_char, bool is_contain_lastempty = false) const;
		/// <summary>
		/// 文字列を分割
		/// </summary>
		/// <param name="split_char">区切り文字</param>
		/// <param name="is_contain_lastempty">区切り文字が最後にある場合、最後の空白を含むか</param>
		/// <returns>分割された文字列</returns>
		std::vector<utf32> split(char32 split_char, bool is_contain_lastempty = false) const;
		/// <summary>
		/// 文字列を分割
		/// </summary>
		/// <param name="split_char">区切り文字</param>
		/// <param name="is_contain_lastempty">区切り文字が最後にある場合、最後の空白を含むか</param>
		/// <returns>分割された文字列</returns>
		std::vector<str>   split(char split_char, bool is_contain_lastempty = false) const;
		/// <summary>
		/// 文字列を分割
		/// </summary>
		/// <param name="split_char">区切り文字</param>
		/// <param name="is_contain_lastempty">区切り文字が最後にある場合、最後の空白を含むか</param>
		/// <returns>分割された文字列</returns>
		std::vector<wstr>  split(wchar_t split_char, bool is_contain_lastempty = false) const;

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
		string  replaced(utf8 old_string, utf8 new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		/// <returns>置き換えられた文字列</returns>
		string  replaced(utf16 old_string, utf16 new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		/// <returns>置き換えられた文字列</returns>
		string  replaced(utf32 old_string, utf32 new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		/// <returns>置き換えられた文字列</returns>
		string  replaced(str old_string, str new_string);
		/// <summary>
		/// 文字列を置換
		/// </summary>
		/// <param name="old_string">置き換え対象の文字列</param>
		/// <param name="new_string">置き換える文字列</param>
		/// <returns>置き換えられた文字列</returns>
		string  replaced(wstr old_string, wstr new_string);

#if 0
		constexpr iterator			   begin() noexcept;
		constexpr const_iterator		 begin() const noexcept;
		constexpr iterator			   end() noexcept;
		constexpr const_iterator		 end() const noexcept;
		constexpr const_iterator		 cbegin() const noexcept;
		constexpr const_iterator		 cend() const noexcept;
		constexpr reverse_iterator	   rbegin() noexcept;
		constexpr const_reverse_iterator rbegin() const noexcept;
		constexpr reverse_iterator	   rend() noexcept;
		constexpr const_reverse_iterator rend() const noexcept;
		constexpr const_reverse_iterator crbegin() const noexcept;
		constexpr const_reverse_iterator crend() const noexcept;

		constexpr size_type		  size() const noexcept;
		constexpr size_type		  length() const noexcept;
		constexpr size_type		  max_size() const noexcept;
		constexpr void			   resize(size_type n, char_t c);
		constexpr void			   resize(size_type n);
		constexpr size_type		  capacity() const noexcept;
		constexpr void			   reserve(size_type res_arg);
		constexpr void			   shrink_to_fit();
		constexpr void			   clear() noexcept;
		[[nodiscard]] constexpr bool empty() const noexcept;

		constexpr const_reference operator[](size_type pos) const;
		constexpr reference	   operator[](size_type pos);
		constexpr const_reference at(size_type pos) const;
		constexpr reference	   at(size_type pos);
		constexpr const char_t&   front() const;
		constexpr char_t&		 front();
		constexpr const char_t&   back() const;
		constexpr char_t&		 back();

		constexpr string&  operator+=(const string& str);
		constexpr string&  operator+=(const char_t* str);
		constexpr string&  operator+=(const char_t str);
		constexpr string&  operator+=(std::initializer_list<char_t> il);
		template<class T>
		constexpr string&  operator+=(const T& t);
		constexpr string&  append(const string& str);
		constexpr string&  append(const string& str, size_type pos, size_type n = npos);
		constexpr string&  append(const char_t* s, size_type n);
		constexpr string&  append(const char_t* s);
		constexpr string&  append(size_type n, char_t c);
		template<class InputIterator>
		constexpr string&  append(InputIterator first, InputIterator last);
		constexpr string&  append(std::initializer_list<char_t> il);
		template<class T>  
		constexpr string&  append(const T& t, size_type pos, size_type n = npos);
		constexpr void	 push_back(char_t c);
		constexpr string&  assign(const string& str);
		constexpr string&  assign(string&& str);
		constexpr string&  assign(const string& str, size_type pos, size_type n = npos);
		constexpr string&  assign(const char_t* s, size_type n);
		constexpr string&  assign(const char_t* s);
		constexpr string&  assign(size_type n, char_t c);
		template<class InputIterator>
		constexpr string&  assign(InputIterator first, InputIterator last);
		constexpr string&  assign(std::initializer_list<char_t> il);
		template<class T>
		constexpr string&  assign(const T& t);
		template<class T>
		constexpr string&  assign(const T& t, size_type pos, size_type n = npos);
		constexpr string&  insert(size_type pos1, const string& str);
		constexpr string&  insert(size_type pos1, const string& str, size_type pos2, size_type n = npos);
		constexpr string&  insert(size_type pos, const char_t* s, size_type n);
		constexpr string&  insert(size_type pos, const char_t* s);
		constexpr string&  insert(size_type pos, size_type n, char_t c);
		constexpr string&  insert(const_iterator p, char_t c);
		constexpr string&  insert(const_iterator p, size_type n, char_t c);
		template<class InputIterator>
		constexpr string&  insert(const_iterator p, InputIterator first, InputIterator last);
		constexpr string&  insert(const_iterator p, initializer_list<char_t>);
		constexpr string&  insert(size_type pos1, const T&  t);
		template<class T>
		constexpr string&  insert(size_type pos1, const T&  t, size_type pos2, size_type n = npos);
		constexpr string&  erase(size_type = 0, size_type n = npos);
		constexpr iterator erase(const_iterator p);
		constexpr iterator erase(const_iterator first, const_iterator last);
		constexpr void	 pop_back();
		constexpr string&  replace(size_type pos1, size_type n1, const string& str);
		constexpr string&  replace(size_type pos1, size_type n1, const string& str, size_type pos2, size_type n2 = npos);
		constexpr string&  replace(size_type pos, size_type n1, const char_t* s, size_type n2);
		constexpr string&  replace(size_type pos, size_type n1, const char_t* s);
		constexpr string&  replace(size_type pos, size_type n1, size_type n2, char_t c);
		constexpr string&  replace(const_iterator i1, const_iterator i2, const string& str);
		constexpr string&  replace(const_iterator i1, const_iterator i2, const char_t* s, size_type n);
		constexpr string&  replace(const_iterator i1, const_iterator i2, const char_t* s);
		constexpr string&  replace(const_iterator i1, const_iterator i2, size_type n, char_t c);
		template<class InputIterator>
		consteval string&  replace(const_iterator i1, const_iterator i2, InputIterator j1, InputIterator j2);
		consteval string&  replace(const_iterator i1, const_iterator i2, std::initializer_list<char_t> il);
		template<class T>
		constexpr string&  replace(size_type pos1, size_type n, const T& t);
		template<class T>
		constexpr string&  replace(size_type pos1, size_type n, const T& t, size_type pos2, size_type n2 = npos);
		template<class T>
		constexpr string&  replace(const_iterator i1, const_iterator i2, const T& t);
		constexpr void	 swap(string& str) noexcept;

		constexpr char_t*		c_str() const noexcept;
		constexpr const char_t*  data() const noexcept;
		constexpr char_t*		data() noexcept;
		constexpr				operator string_view_type() const noexcept;
		constexpr allocator_type get_allocator() const noexcept;
		constexpr size_type	  copy(char_t* s, size_type n, size_type pos = 0);
		constexpr size_type	  find(const string& str, size_type pos = 0) const noexcept;
		constexpr size_type	  find(const char_t* s, size_type pos, size_type n) const;
		constexpr size_type	  find(const char_t* s, size_type pos = 0) const;
		constexpr size_type	  find(char_t c, size_type pos = 0) const;
		template<class T>
		constexpr size_type	  find(const T& t, size_type pos = 0) const noexcept;
		constexpr size_type	  rfind(const string& str, size_type pos = npos) const noexcept;
		constexpr size_type	  rfind(const char_t* s, size_type pos, size_type n) const;
		constexpr size_type	  rfind(const char_t* s, size_type pos = npos) const;
		constexpr size_type	  rfind(char_t c, size_type pos = npos) const;
		template<class T>
		constexpr size_type	  rfind(const T& t, size_type pos = npos) const noexcept;
		constexpr size_type	  find_first_of(const string& str, size_type pos = 0) const noexcept;
		constexpr size_type	  find_first_of(const char_t* s, size_type pos, size_type n) const;
		constexpr size_type	  find_first_of(const char_t* s, size_type pos = 0) const;
		constexpr size_type	  find_first_of(char_t c, size_type pos = 0) const;
		template<class T>
		constexpr size_type	  find_first_of(const T& t, size_type pos = 0) const noexcept;
		constexpr size_type	  find_last_of(const string& str, size_type pos = npos) const noexcept;
		constexpr size_type	  find_last_of(const char_t* s, size_type pos, size_type n) const;
		constexpr size_type	  find_last_of(const char_t* s, size_type pos = npos) const;
		constexpr size_type	  find_last_of(char_t c, size_type pos = npos) const;
		template<class T>		 
		constexpr size_type	  find_last_of(const T& t, size_type pos = npos) const noexcept;
		constexpr size_type	  find_first_not_of(const string& str, size_type pos = 0) const noexcept;
		constexpr size_type	  find_first_not_of(const char_t* s, size_type pos, size_type n) const;
		constexpr size_type	  find_first_not_of(const char_t* s, size_type pos = 0) const;
		constexpr size_type	  find_first_not_of(char_t c, size_type pos = 0) const;
		template<class T>		
		constexpr size_type	  find_first_not_of(const T& t, size_type pos = 0) const noexcept;
		constexpr size_type	  find_last_not_of(const string& str, size_type pos = npos) const noexcept;
		constexpr size_type	  find_last_not_of(const char_t* s, size_type pos, size_type n) const;
		constexpr size_type	  find_last_not_of(const char_t* s, size_type pos = npos) const;
		constexpr size_type	  find_last_not_of(char_t c, size_type pos = npos) const;
		template<class T>		
		constexpr size_type	  find_last_not_of(const T& t, size_type pos = npos) const noexcept;
		constexpr string		 substr(size_type pos = 0, size_type n = npos) const;
		constexpr int			compare(const string& str) const noexcept;
		constexpr int			compare(size_type pos1, size_type n1, const string& str) const;
		constexpr int			compare(size_type pos1, size_type n1, const string& str, size_type pos2, size_type n2) const ;
		constexpr int			compare(const char_t* s) const;
		constexpr int			compare(size_type pos1, size_type n1, const char_t* s) const;
		constexpr int			compare(size_type pos1, size_type n1, const char_t* s, size_type n2) const;
		template<class T>
		constexpr int			compare(const T& t) const noexcept;
		template<class T>
		constexpr int			compare(size_type pos1, size_type n1, const T& t) const noexcept;
		template<class T>
		constexpr int			compare(size_type pos1, size_type n1, const T& t, size_type pos2, size_type n2) const noexcept;
		constexpr bool		   starts_with(string_view_type x) const noexcept;
		constexpr bool		   starts_with(char_t x) const noexcept;
		constexpr bool		   starts_with(const char_t* x) const;
		constexpr bool		   ends_with(string_view_type x) const noexcept;
		constexpr bool		   ends_with(char_t x) const noexcept;
		constexpr bool		   ends_with(const char_t* x) const;
		constexpr bool		   contains(string_view_type x) const noexcept;
		constexpr bool		   contains(char_t x) const noexcept;
		constexpr bool		   contains(const char_t* x) const;
#endif
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
template<>
struct formatter<suika::string>: formatter<suika::string::string_type, suika::string::string_type::value_type> {
	auto format(suika::string str, wformat_context& ctx) const {
		return formatter<suika::string::string_type, suika::string::string_type::value_type>::format(str.to_wstring(), ctx);
	}
};

	template<>
	struct hash<suika::string> {
	public:
		size_t operator()(const suika::string& data)const {
			return hash<suika::string::string_type>()(data.to_wstring());
		}
	};
}

#include "detail/string.ipp"

#endif