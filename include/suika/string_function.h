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

#pragma once

#include <string>
#include <vector>
#include "def.h"

namespace suika {
	/// <summary>
	/// 文字列を特定の文字で分割
	/// </summary>
	/// <param name="s">元のUTF8文字列</param>
	/// <param name="split_char">UTF8区切り文字</param>
	/// <param name="is_contain_lastempty">文字列の末尾が区切り文字だった際に、最後に空白を挿入するか</param>
	/// <returns>区切られたUTF8文字列の配列</returns>
	std::vector<std::u8string> split(const std::u8string& s, char8 split_char, bool is_contain_lastempty = false);

	/// <summary>
	/// UTF16文字列を特定の文字で分割
	/// </summary>
	/// <param name="s">元のUTF16文字列</param>
	/// <param name="split_char">UTF16区切り文字</param>
	/// <param name="is_contain_lastempty">文字列の末尾が区切り文字だった際に、最後に空白を挿入するか</param>
	/// <returns>区切られたUTF16文字列の配列</returns>
	std::vector<std::u16string> split(const std::u16string& s, char16 split_char, bool is_contain_lastempty = false);

	/// <summary>
	/// UTF32文字列を特定の文字で分割
	/// </summary>
	/// <param name="s">元のUTF32文字列</param>
	/// <param name="split_char">区切りUTF32文字</param>
	/// <param name="is_contain_lastempty">文字列の末尾が区切り文字だった際に、最後に空白を挿入するか</param>
	/// <returns>区切られたUTF32文字列の配列</returns>
	std::vector<std::u32string> split(const std::u32string& s, char32 split_char, bool is_contain_lastempty = false);

	/// <summary>
	/// 文字列を特定の文字で分割
	/// </summary>
	/// <param name="s">元の文字列</param>
	/// <param name="split_char">区切り文字</param>
	/// <param name="is_contain_lastempty">文字列の末尾が区切り文字だった際に、最後に空白を挿入するか</param>
	/// <returns>区切られた文字列の配列</returns>
	std::vector<std::string> split(const std::string& s, char split_char, bool is_contain_lastempty = false);

	/// <summary>
	/// ワイド文字列を特定の文字で分割
	/// </summary>
	/// <param name="s">元のワイド文字列</param>
	/// <param name="split_char">区切りワイド文字</param>
	/// <param name="is_contain_lastempty">文字列の末尾が区切り文字だった際に、最後に空白を挿入するか</param>
	/// <returns>区切られた文字列の配列</returns>
	std::vector<std::wstring> split(const std::wstring& s, wchar_t split_char, bool is_contain_lastempty = false);

	/// <summary>
	/// UTF8文字列中の特定の文字列を置き換える
	/// </summary>
	/// <param name="source">元のUTF8文字列</param>
	/// <param name="old_val">置き換えるUTF8文字列</param>
	/// <param name="new_val">置き換える対象</param>
	/// <returns>置き換えられたUTF8文字列</returns>
	std::u8string replace_string(std::u8string source, const std::u8string& old_val, const std::u8string& new_val);

	/// <summary>
	/// UTF16文字列中の特定の文字列を置き換える
	/// </summary>
	/// <param name="source">元のUTF16UTF16文字列</param>
	/// <param name="old_val">置き換えるUTF16文字列</param>
	/// <param name="new_val">置き換える対象</param>
	/// <returns>置き換えられたUTF16文字列</returns>
	std::u16string replace_string(std::u16string source, const std::u16string& old_val, const std::u16string& new_val);

	/// <summary>
	/// UTF32文字列中の特定の文字列を置き換える
	/// </summary>
	/// <param name="source">元のUTF32文字列</param>
	/// <param name="old_val">置き換えるUTF32文字列</param>
	/// <param name="new_val">置き換える対象</param>
	/// <returns>置き換えられた文字列</returns>
	std::u32string replace_string(std::u32string source, const std::u32string& old_val, const std::u32string& new_val);

	/// <summary>
	/// 文字列中の特定の文字列を置き換える
	/// </summary>
	/// <param name="source">元の文字列</param>
	/// <param name="old_val">置き換える文字列</param>
	/// <param name="new_val">置き換える対象</param>
	/// <returns>置き換えられた文字列</returns>
	std::string replace_string(std::string source, const std::string& old_val, const std::string& new_val);

	/// <summary>
	/// ワイド文字列中の特定の文字列を置き換える
	/// </summary>
	/// <param name="source">元のワイド文字列</param>
	/// <param name="old_val">置き換えるワイド文字列</param>
	/// <param name="new_val">置き換える対象</param>
	/// <returns>置き換えられた文字列</returns>
	std::wstring replace_string(std::wstring source, const std::wstring& old_val, const std::wstring& new_val);
} // namespace suika
