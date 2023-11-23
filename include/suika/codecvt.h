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
#undef CODECVT_CONSTEXPR 
#endif