// -----------------------------------------------------------
// 
// math function:pow
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
	template<std::floating_point T, std::integral I>
	constexpr inline T ipow(T x, I n) {
		return n == I { 1 } ? x :
			   n == I { 0 } ? T { 1 } :
			   n > T { 1 }  ? ((n & 1) ? x * ipow(x, n - 1) : ipow(x, n / 2) * ipow(x, n / 2)) :
							  T { 1 } / ipow(x, -n);
	}
} // namespace

namespace suika {
	namespace math {
		template<std::floating_point T, std::integral I>
		constexpr inline T pow(T x, I n) {
			return ipow(x, n);
		}

		template<std::floating_point T>
		constexpr inline T pow(T x, T y) {
			return (y - (long long)(y)) == T(0) ? ipow(x, (long long)y) : exp(log(x) * y);
		}

		template<std::integral T>
		constexpr inline double	pow(T x, T y) {
			return ipow(static_cast<double>(x), y);
		}
	} // namespace math
} // namespace suika