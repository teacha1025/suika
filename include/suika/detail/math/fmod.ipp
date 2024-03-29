// -----------------------------------------------------------
// 
// math function:fmod
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

#include <concepts>

namespace {
	
} // namespace

namespace suika {
	namespace math {
		template<std::floating_point T>
		constexpr inline T fmod(T x, T y) {
			long double lx = x, ly = y;
			return x == T(0) ? 0 : static_cast<T>(lx - (int64)(lx / ly) * ly);
		}

		template<std::integral T>
		constexpr inline T fmod(T x, T y) {
			return x % y;
		}
	} // namespace math
} // namespace suika