// -----------------------------------------------------------
// 
// matrix
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
#define CODECVT_CONSTEXPR 
#define CODECVT_USE_STRING_VIEW 1
#if !CODECVT_USE_STRING_VIEW
#define ARG_CODECVT_U8 const char8_t*
#define ARG_CODECVT_U16 const char16_t*
#define ARG_CODECVT_U32 const char32_t*
#define ARG_CODECVT_STR const char*
#define ARG_CODECVT_WSTR const wchar_t*
#else
#define ARG_CODECVT_U8  std::u8string_view
#define ARG_CODECVT_U16  std::u16string_view
#define ARG_CODECVT_U32  std::u32string_view
#define ARG_CODECVT_STR  std::string_view
#define ARG_CODECVT_WSTR  std::wstring_view
#endif
namespace suika {
	/// <summary>
	/// 文字列をワイド文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	CODECVT_CONSTEXPR std::wstring to_wstring(ARG_CODECVT_U8 src);

	/// <summary>
	/// 文字列をワイド文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	CODECVT_CONSTEXPR std::wstring to_wstring(ARG_CODECVT_U16 src);

	/// <summary>
	/// 文字列をワイド文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	CODECVT_CONSTEXPR std::wstring to_wstring(ARG_CODECVT_U32 src);

	/// <summary>
	/// 文字列をワイド文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	CODECVT_CONSTEXPR std::wstring to_wstring(ARG_CODECVT_STR src);


	/// <summary>
	/// UTF8文字列を文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF8文字列</param>
	/// <returns>変換された文字列</returns>
	CODECVT_CONSTEXPR std::string to_string(ARG_CODECVT_U8 src);

	/// <summary>
	/// UTF16文字列を文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF16文字列</param>
	/// <returns>変換された文字列</returns>
	CODECVT_CONSTEXPR std::string to_string(ARG_CODECVT_U16 src);

	/// <summary>
	/// UTF32文字列を文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF32文字列</param>
	/// <returns>変換された文字列</returns>
	CODECVT_CONSTEXPR std::string to_string(ARG_CODECVT_U32 src);

	/// <summary>
	/// ワイド文字列を文字列に変換する
	/// </summary>
	/// <param name="src">元のワイド文字列</param>
	/// <returns>変換された文字列</returns>
	CODECVT_CONSTEXPR std::string to_string(ARG_CODECVT_WSTR src);


	/// <summary>
	/// UTF16文字列をUTF8文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF16文字列</param>
	/// <returns>変換されたUTF8文字列</returns>
	CODECVT_CONSTEXPR std::u8string to_u8string(ARG_CODECVT_U16 src);

	/// <summary>
	/// UTF32文字列をUTF8文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF32文字列</param>
	/// <returns>変換されたUTF8文字列</returns>
	CODECVT_CONSTEXPR std::u8string to_u8string(ARG_CODECVT_U32 src);

	/// <summary>
	/// ワイド文字列をUTF8文字列に変換する
	/// </summary>
	/// <param name="src">元のワイド文字列</param>
	/// <returns>変換されたUTF8文字列</returns>
	CODECVT_CONSTEXPR std::u8string to_u8string(ARG_CODECVT_STR src);

	/// <summary>
	/// UTF8文字列をUTF8文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF8文字列</param>
	/// <returns>変換されたUTF8文字列</returns>
	CODECVT_CONSTEXPR std::u8string to_u8string(ARG_CODECVT_WSTR src);


	/// <summary>
	/// UTF8文字列をUTF16文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF8文字列</param>
	/// <returns>変換されたUTF16文字列</returns>
	CODECVT_CONSTEXPR std::u16string to_u16string(ARG_CODECVT_U8 src);

	/// <summary>
	/// UTF32文字列をUTF16文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF32文字列</param>
	/// <returns>変換されたUTF16文字列</returns>
	CODECVT_CONSTEXPR std::u16string to_u16string(ARG_CODECVT_U32 src);

	/// <summary>
	/// 文字列をUTF16文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたUTF16文字列</returns>
	CODECVT_CONSTEXPR std::u16string to_u16string(ARG_CODECVT_STR src);

	/// <summary>
	/// ワイド文字列をUTF16文字列に変換する
	/// </summary>
	/// <param name="src">元のワイド文字列</param>
	/// <returns>変換されたUTF16文字列</returns>
	CODECVT_CONSTEXPR std::u16string to_u16string(ARG_CODECVT_WSTR src);


	/// <summary>
	/// UTF8文字列をUTF32文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF8文字列</param>
	/// <returns>変換されたUTF32文字列</returns>
	CODECVT_CONSTEXPR std::u32string to_u32string(ARG_CODECVT_U8 src);

	/// <summary>
	/// UTF16文字列をUTF32文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF16文字列</param>
	/// <returns>変換されたUTF32文字列</returns>
	CODECVT_CONSTEXPR std::u32string to_u32string(ARG_CODECVT_U16 src);

	/// <summary>
	/// 文字列をUTF32文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたUTF32文字列</returns>
	CODECVT_CONSTEXPR std::u32string to_u32string(ARG_CODECVT_STR src);

	/// <summary>
	/// ワイド文字列をUTF32文字列に変換する
	/// </summary>
	/// <param name="src">元のワイド文字列</param>
	/// <returns>変換されたUTF32文字列</returns>
	CODECVT_CONSTEXPR std::u32string to_u32string(ARG_CODECVT_WSTR src);


	/// <summary>
	/// 文字列を文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換された文字列</returns>
	CODECVT_CONSTEXPR std::string to_string(ARG_CODECVT_STR src);

	/// <summary>
	/// 文字列をワイド文字列に変換する
	/// </summary>
	/// <param name="src">元のワイド文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	CODECVT_CONSTEXPR std::wstring to_wstring(ARG_CODECVT_WSTR src);

	/// <summary>
	/// UTF8文字列をUTF8文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF8文字列</param>
	/// <returns>変換されたUTF8文字列</returns>
	CODECVT_CONSTEXPR std::u8string to_u8string(ARG_CODECVT_U8 src);

	/// <summary>
	/// UTF16文字列をUTF16文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF16文字列</param>
	/// <returns>変換されたUTF16文字列</returns>
	CODECVT_CONSTEXPR std::u16string to_u16string(ARG_CODECVT_U16 src);

	/// <summary>
	/// UTF32文字列をUTF32文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF32文字列</param>
	/// <returns>変換されたUTF32文字列</returns>
	CODECVT_CONSTEXPR std::u32string to_u32string(ARG_CODECVT_U32 src);
} // namespace suika
