#pragma once
#include <cstdint>
namespace suika {
#pragma region type
	/// <summary>
	/// 8bit®”Œ^
	/// </summary>
	using int8 = int8_t;
	/// <summary>
	/// 16bit®”Œ^
	/// </summary>
	using int16 = int16_t;
	/// <summary>
	/// 32bit®”Œ^
	/// </summary>
	using int32 = int32_t;
	/// <summary>
	/// 64bit®”Œ^
	/// </summary>
	using int64 = int64_t;
	/// <summary>
	/// 8bit•„†‚È‚µ®”Œ^
	/// </summary>
	using uint8 = uint8_t;
	/// <summary>
	/// 16bit•„†‚È‚µ®”Œ^
	/// </summary>
	using uint16 = uint16_t;
	/// <summary>
	/// 32bit•„†‚È‚µ®”Œ^
	/// </summary>
	using uint32 = uint32_t;
	/// <summary>
	/// 64bit•„†‚È‚µ®”Œ^
	/// </summary>
	using uint64 = uint64_t;

	/// <summary>
	/// 1Byte®”Œ^
	/// </summary>
	using byte = int8;
	/// <summary>
	/// 1Byte•„†‚È‚µ®”Œ^
	/// </summary>
	using ubyte = uint8;

	/// <summary>
	/// long long®”Œ^(64bit)
	/// </summary>
	using longlong = int64;

	/// <summary>
	/// •„†‚È‚µ®”Œ^(32bit)
	/// </summary>
	using uint = uint32;
	/// <summary>
	/// •„†‚È‚µlong®”Œ^(32bit)
	/// </summary>
	using ulong = uint32;
	/// <summary>
	/// •„†‚È‚µlong long®”Œ^(64bit)
	/// </summary>
	using ulonglong = uint64;
	/// <summary>
	/// long doubleŒ^(MSVC‚Ìê‡‚Ídouble‚Æ“¯“™)
	/// </summary>
	using ldouble = long double;

	/// <summary>
	/// UTF-8‘Î‰charŒ^
	/// </summary>
	using char8 = char8_t;
	/// <summary>
	/// UTF-16‘Î‰charŒ^
	/// </summary>
	using char16 = char16_t;
	/// <summary>
	/// UTF-32‘Î‰charŒ^
	/// </summary>
	using char32 = char32_t;
#pragma endregion
}