//// -----------------------------------------------------------
// 
// type definition
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

#include <cstdint>

namespace suika {
	class string;
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

	using path_type = string;
#pragma endregion
}
