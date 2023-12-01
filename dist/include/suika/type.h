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
#pragma region type
	/// <summary>
	/// 8bit�����^
	/// </summary>
	using int8 = int8_t;
	/// <summary>
	/// 16bit�����^
	/// </summary>
	using int16 = int16_t;
	/// <summary>
	/// 32bit�����^
	/// </summary>
	using int32 = int32_t;
	/// <summary>
	/// 64bit�����^
	/// </summary>
	using int64 = int64_t;
	/// <summary>
	/// 8bit�����Ȃ������^
	/// </summary>
	using uint8 = uint8_t;
	/// <summary>
	/// 16bit�����Ȃ������^
	/// </summary>
	using uint16 = uint16_t;
	/// <summary>
	/// 32bit�����Ȃ������^
	/// </summary>
	using uint32 = uint32_t;
	/// <summary>
	/// 64bit�����Ȃ������^
	/// </summary>
	using uint64 = uint64_t;

	/// <summary>
	/// 1Byte�����^
	/// </summary>
	using byte = int8;
	/// <summary>
	/// 1Byte�����Ȃ������^
	/// </summary>
	using ubyte = uint8;

	/// <summary>
	/// long long�����^(64bit)
	/// </summary>
	using longlong = int64;

	/// <summary>
	/// �����Ȃ������^(32bit)
	/// </summary>
	using uint = uint32;
	/// <summary>
	/// �����Ȃ�long�����^(32bit)
	/// </summary>
	using ulong = uint32;
	/// <summary>
	/// �����Ȃ�long long�����^(64bit)
	/// </summary>
	using ulonglong = uint64;
	/// <summary>
	/// long double�^(MSVC�̏ꍇ��double�Ɠ���)
	/// </summary>
	using ldouble = long double;

	/// <summary>
	/// UTF-8�Ή�char�^
	/// </summary>
	using char8 = char8_t;
	/// <summary>
	/// UTF-16�Ή�char�^
	/// </summary>
	using char16 = char16_t;
	/// <summary>
	/// UTF-32�Ή�char�^
	/// </summary>
	using char32 = char32_t;
#pragma endregion
}