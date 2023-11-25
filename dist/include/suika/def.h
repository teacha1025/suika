// -----------------------------------------------------------
// 
// constant value definition
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
#include <numbers>
#include <cstdint>

#include "type.h"

#define define constexpr auto
#define DXENGINE suika
#define NODISCARD [[nodiscard]]

namespace suika {
#pragma region
#define MAJOR_VERSION 0
#define MINOR_VERSION 0
#define PATCH_VERSION 3
#define VERSION_SIGN ""

#define VER_HELPER(suf,M,m,p,s) suf""#M"."#m"."#p s
#define VERSION_STRING(suf,M,m,p,s) VER_HELPER(suf,M,m,p,s)

	/// <summary>
	/// ライブラリのバージョン
	/// </summary>
	define VERSION = MAJOR_VERSION * 100 + MINOR_VERSION * 10 + PATCH_VERSION;
	/// <summary>
	/// ライブラリのバージョン(文字列)
	/// </summary>
	define VERSION_S = VERSION_STRING(,MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, VERSION_SIGN);
	/// <summary>
	/// ライブラリのバージョン(ワイド文字列)
	/// </summary>
	define VERSION_WS = VERSION_STRING(L,MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, VERSION_SIGN);
	/// <summary>
	/// ライブラリのバージョン(UTF8文字列)
	/// </summary>
	define VERSION_UTF8 = VERSION_STRING(u8, MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, VERSION_SIGN);
	/// <summary>
	/// ライブラリのバージョン(UTF16文字列)
	/// </summary>
	define VERSION_UTF16 = VERSION_STRING(u, MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, VERSION_SIGN);
	/// <summary>
	/// ライブラリのバージョン(UTF32文字列)
	/// </summary>
	define VERSION_UTF32 = VERSION_STRING(U, MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, VERSION_SIGN);

#undef MAJOR_VERSION
#undef MINOR_VERSION
#undef PATCH_VERSION
#undef VERSION_SIGN
#undef VER_HELPER
#undef VERSION_STRING

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