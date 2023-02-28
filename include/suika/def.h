/**
* @file def.h
* @brief 定数などの定義
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_DEF
#define _SK_DEF
#include <string>
#include <numbers>
#include <cstdint>
#define define constexpr auto
#define DXENGINE suika

namespace suika {
#pragma region
	/// <summary>
	/// ライブラリのバージョン
	/// </summary>
	define VERSION = 0x20004;
	/// <summary>
	/// ライブラリのバージョン(文字列)
	/// </summary>
	define VERSION_S = "0.00.01";
	define VERSION_WS = L"0.00.01";

	define VERSION_TEXT = "0.00α1";
	define VERSION_WTEXT = L"0.00α1";
#pragma endregion
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
#pragma region constant
	/// <summary>
	/// 円周率π
	/// </summary>
	define PI = std::numbers::pi;
	/// <summary>
	/// 円周率π(long double)
	/// </summary>
	define PI_LD = std::numbers::pi_v<long double>;
	/// <summary>
	/// 円周率π(float)
	/// </summary>
	define PI_F = std::numbers::pi_v<float>;
	/// <summary>
	/// 2倍円周率2π
	/// </summary>
	define PI_2 = std::numbers::pi * 2.0;
	/// <summary>
	/// 2倍円周率2π(long double)
	/// </summary>
	define PI_2LD = std::numbers::pi_v<long double> * 2.0L;
	/// <summary>
	/// 2倍円周率2π(float)
	/// </summary>
	define PI_2F = std::numbers::pi_v<float> * 2.0f;
	/// <summary>
	/// 1/2倍円周率π/2
	/// </summary>
	define PI_HALF = std::numbers::pi / 2.0;
	/// <summary>
	/// 1/2倍円周率π/2(long double)
	/// </summary>
	define PI_HALF_LD = std::numbers::pi_v<long double> / 2.0L;
	/// <summary>
	/// 1/2倍円周率π/2(float)
	/// </summary>
	define PI_HALF_F = std::numbers::pi_v<float> / 2.0f;
#pragma endregion
#pragma region suffix
	/// <summary>
	/// SI単位系接尾語
	/// </summary>
	namespace suffix {
		/// <summary>
		/// 10^(-24)
		/// </summary>
		define YOCTO = 1e-24;
		/// <summary>
		/// 10^(-24) (float)
		/// </summary>
		define YOCTO_F = (float)YOCTO;

		/// <summary>
		/// 10^(-21)
		/// </summary>
		define ZEPTO = 1e-21;
		/// <summary>
		/// 10^(-21) (float)
		/// </summary>
		define ZEPTO_F = (float)ZEPTO;

		/// <summary>
		/// 10^(-18)
		/// </summary>
		define ATTO = 1e-18;
		/// <summary>
		/// 10^(-18) (float)
		/// </summary>
		define ATTO_F = (float)ATTO;

		/// <summary>
		/// 10^(-15)
		/// </summary>
		define FEMTO = 1e-15;
		/// <summary>
		/// 10^(-15) (float)
		/// </summary>
		define FEMTO_F = (float)FEMTO;

		/// <summary>
		/// 10^(-12)
		/// </summary>
		define PICO = 1e-12;
		/// <summary>
		/// 10^(-12) (float)
		/// </summary>
		define PICO_F = (float)PICO;

		/// <summary>
		/// 10^(-9)
		/// </summary>
		define NANO = 1e-9;
		/// <summary>
		/// 10^(-9) (float)
		/// </summary>
		define NANO_F = (float)NANO;

		/// <summary>
		/// 10^(-6)
		/// </summary>
		define MICRO = 1e-6;
		/// <summary>
		/// 10^(-6) (float)
		/// </summary>
		define MICRO_F = (float)MICRO;

		/// <summary>
		/// 10^(-3)
		/// </summary>
		define MILLI = 1e-3;
		/// <summary>
		/// 10^(-3) (float)
		/// </summary>
		define MILLI_F = (float)MILLI;

		/// <summary>
		/// 10^(-2)
		/// </summary>
		define CENTI = 1e-2;
		/// <summary>
		/// 10^(-2) (float)
		/// </summary>
		define CENTI_F = (float)CENTI;

		/// <summary>
		/// 10^(-1)
		/// </summary>
		define DECI = 1e-1;
		/// <summary>
		/// 10^(-1) (float)
		/// </summary>
		define DECI_F = (float)DECI;

		/// <summary>
		/// 10^1
		/// </summary>
		define DECA = 1e1;
		/// <summary>
		/// 10^1 (float)
		/// </summary>
		define DECA_F = (float)DECA;
		/// <summary>
		/// 10^1 (ulong)
		/// </summary>
		define DECA_UL = (ulong)DECA;

		/// <summary>
		/// 10^2
		/// </summary>
		define HECTO = 1e2;
		/// <summary>
		/// 10^2 (float)
		/// </summary>
		define HECTO_F = (float)HECTO;
		/// <summary>
		/// 10^2 (ulong)
		/// </summary>
		define HECTO_UL = (ulong)HECTO;

		/// <summary>
		/// 10^3
		/// </summary>
		define KILO = 1e3;
		/// <summary>
		/// 10^3 (float)
		/// </summary>
		define KILO_F = (float)KILO;
		/// <summary>
		/// 10^3 (ulong)
		/// </summary>
		define KILO_UL = (ulong)KILO;

		/// <summary>
		/// 10^6
		/// </summary>
		define MEGA = 1e6;
		/// <summary>
		/// 10^6 (float)
		/// </summary>
		define MEGA_F = (float)MEGA;
		/// <summary>
		/// 10^6 (ulong)
		/// </summary>
		define MEGA_UL = (ulong)MEGA;

		/// <summary>
		/// 10^9
		/// </summary>
		define GIGA = 1e9;
		/// <summary>
		/// 10^9 (float)
		/// </summary>
		define GIGA_F = (float)GIGA;
		/// <summary>
		/// 10^9 (ulong)
		/// </summary>
		define GIGA_UL = (ulong)GIGA;

		/// <summary>
		/// 10^12
		/// </summary>
		define TERA = 1e12;
		/// <summary>
		/// 10^12 (float)
		/// </summary>
		define TERA_F = (float)TERA;

		/// <summary>
		/// 10^15
		/// </summary>
		define PETA = 1e15;
		/// <summary>
		/// 10^15 (float)
		/// </summary>
		define PETA_F = (float)PETA;

		/// <summary>
		/// 10^18
		/// </summary>
		define EXA = 1e18;
		/// <summary>
		/// 10^18 (float)
		/// </summary>
		define EXA_F = (float)EXA;

		/// <summary>
		/// 10^21
		/// </summary>
		define ZETTA = 1e21;
		/// <summary>
		/// 10^21 (float)
		/// </summary>
		define ZETTA_F = (float)ZETTA;

		/// <summary>
		/// 10^24
		/// </summary>
		define YOTTA = 1e24;
		/// <summary>
		/// 10^24 (float)
		/// </summary>
		define YOTTA_F = (float)YOTTA;
	} // namespace suffix
#pragma endregion
} // namespace suika
#endif