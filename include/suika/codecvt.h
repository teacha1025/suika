/**
* @file codecvt.h
* @brief 文字列関係
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_CODECVT
#define _SK_CODECVT
#include <string>

namespace suika {
	/// <summary>
	/// 文字列をワイド文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	std::wstring to_wstring(const std::u8string_view& src);
	/// <summary>
	/// 文字列をワイド文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	std::wstring to_wstring(const std::u16string_view& src);
	/// <summary>
	/// 文字列をワイド文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	std::wstring to_wstring(const std::u32string_view& src);
	/// <summary>
	/// 文字列をワイド文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	std::wstring to_wstring(const std::string_view& src);

	/// <summary>
	/// UTF8文字列を文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF8文字列</param>
	/// <returns>変換された文字列</returns>
	std::string to_string(const std::u8string_view& src);
	/// <summary>
	/// UTF16文字列を文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF16文字列</param>
	/// <returns>変換された文字列</returns>
	std::string to_string(const std::u16string_view& src);
	/// <summary>
	/// UTF32文字列を文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF32文字列</param>
	/// <returns>変換された文字列</returns>
	std::string to_string(const std::u32string_view& src);
	/// <summary>
	/// ワイド文字列を文字列に変換する
	/// </summary>
	/// <param name="src">元のワイド文字列</param>
	/// <returns>変換された文字列</returns>
	std::string to_string(const std::wstring_view& src);

	/// <summary>
	/// UTF16文字列をUTF8文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF16文字列</param>
	/// <returns>変換されたUTF8文字列</returns>
	std::u8string to_u8string(const std::u16string_view& src);
	/// <summary>
	/// UTF32文字列をUTF8文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF32文字列</param>
	/// <returns>変換されたUTF8文字列</returns>
	std::u8string to_u8string(const std::u32string_view& src);
	/// <summary>
	/// ワイド文字列をUTF8文字列に変換する
	/// </summary>
	/// <param name="src">元のワイド文字列</param>
	/// <returns>変換されたUTF8文字列</returns>
	std::u8string to_u8string(const std::string_view& src);
	/// <summary>
	/// UTF8文字列をUTF8文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF8文字列</param>
	/// <returns>変換されたUTF8文字列</returns>
	std::u8string to_u8string(const std::wstring_view& src);

	/// <summary>
	/// UTF8文字列をUTF16文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF8文字列</param>
	/// <returns>変換されたUTF16文字列</returns>
	std::u16string to_u16string(const std::u8string_view& src);
	/// <summary>
	/// UTF32文字列をUTF16文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF32文字列</param>
	/// <returns>変換されたUTF16文字列</returns>
	std::u16string to_u16string(const std::u32string_view& src);
	/// <summary>
	/// 文字列をUTF16文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたUTF16文字列</returns>
	std::u16string to_u16string(const std::string_view& src);
	/// <summary>
	/// ワイド文字列をUTF16文字列に変換する
	/// </summary>
	/// <param name="src">元のワイド文字列</param>
	/// <returns>変換されたUTF16文字列</returns>
	std::u16string to_u16string(const std::wstring_view& src);

	/// <summary>
	/// UTF8文字列をUTF32文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF8文字列</param>
	/// <returns>変換されたUTF32文字列</returns>
	std::u32string to_u32string(const std::u8string_view& src);
	/// <summary>
	/// UTF16文字列をUTF32文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF16文字列</param>
	/// <returns>変換されたUTF32文字列</returns>
	std::u32string to_u32string(const std::u16string_view& src);
	/// <summary>
	/// 文字列をUTF32文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換されたUTF32文字列</returns>
	std::u32string to_u32string(const std::string_view& src);
	/// <summary>
	/// ワイド文字列をUTF32文字列に変換する
	/// </summary>
	/// <param name="src">元のワイド文字列</param>
	/// <returns>変換されたUTF32文字列</returns>
	std::u32string to_u32string(const std::wstring_view& src);

	/// <summary>
	/// 文字列を文字列に変換する
	/// </summary>
	/// <param name="src">元の文字列</param>
	/// <returns>変換された文字列</returns>
	std::string to_string(const std::string_view& src);
	/// <summary>
	/// 文字列をワイド文字列に変換する
	/// </summary>
	/// <param name="src">元のワイド文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	std::wstring to_wstring(const std::wstring_view& src);
	/// <summary>
	/// UTF8文字列をUTF8文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF8文字列</param>
	/// <returns>変換されたUTF8文字列</returns>
	std::u8string to_u8string(const std::u8string_view& src);
	/// <summary>
	/// UTF16文字列をUTF16文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF16文字列</param>
	/// <returns>変換されたUTF16文字列</returns>
	std::u16string to_u16string(const std::u16string_view& src);
	/// <summary>
	/// UTF32文字列をUTF32文字列に変換する
	/// </summary>
	/// <param name="src">元のUTF32文字列</param>
	/// <returns>変換されたUTF32文字列</returns>
	std::u32string to_u32string(const std::u32string_view& src);
} // namespace suika
#endif