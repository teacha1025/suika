#pragma once
#include <cstdint>
namespace suika {
#pragma region type
	/// <summary>
	/// 8bit整数型
	/// </summary>
	using int8 = int8_t;
	/// <summary>
	/// 16bit整数型
	/// </summary>
	using int16 = int16_t;
	/// <summary>
	/// 32bit整数型
	/// </summary>
	using int32 = int32_t;
	/// <summary>
	/// 64bit整数型
	/// </summary>
	using int64 = int64_t;
	/// <summary>
	/// 8bit符号なし整数型
	/// </summary>
	using uint8 = uint8_t;
	/// <summary>
	/// 16bit符号なし整数型
	/// </summary>
	using uint16 = uint16_t;
	/// <summary>
	/// 32bit符号なし整数型
	/// </summary>
	using uint32 = uint32_t;
	/// <summary>
	/// 64bit符号なし整数型
	/// </summary>
	using uint64 = uint64_t;

	/// <summary>
	/// 1Byte整数型
	/// </summary>
	using byte = int8;
	/// <summary>
	/// 1Byte符号なし整数型
	/// </summary>
	using ubyte = uint8;

	/// <summary>
	/// long long整数型(64bit)
	/// </summary>
	using longlong = int64;

	/// <summary>
	/// 符号なし整数型(32bit)
	/// </summary>
	using uint = uint32;
	/// <summary>
	/// 符号なしlong整数型(32bit)
	/// </summary>
	using ulong = uint32;
	/// <summary>
	/// 符号なしlong long整数型(64bit)
	/// </summary>
	using ulonglong = uint64;
	/// <summary>
	/// long double型(MSVCの場合はdoubleと同等)
	/// </summary>
	using ldouble = long double;

	/// <summary>
	/// UTF-8対応char型
	/// </summary>
	using char8 = char8_t;
	/// <summary>
	/// UTF-16対応char型
	/// </summary>
	using char16 = char16_t;
	/// <summary>
	/// UTF-32対応char型
	/// </summary>
	using char32 = char32_t;
#pragma endregion
}