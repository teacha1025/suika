// -----------------------------------------------------------
// 
// math function:exp
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

#include <cmath>
#include <bit>
#include <concepts>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace {
	template<typename T>
	constexpr inline bool feq(T a, T b) {
		return suika::math::abs(a - b) <= std::numeric_limits<T>::epsilon();
	}

	template<typename T>
	constexpr inline T exp_impl(T x, T sum, T n, int i, T t) {
		auto d = t / n;
		return feq(sum, sum + d) ? sum : exp_impl(x, sum + d, n * i, i + 1, t * x);
	}
}

namespace suika {
	namespace math {
		template<std::floating_point T>
		constexpr inline T exp(T x) {
			if (x == T { 0 }) {
				return T { 1 };
			}
			if (x == T{ 1 }) {
				return std::numbers::e_v<T>;
			}
			if (x == T { -1 }) {
				return T(1.0) / std::numbers::e_v<T>;
			}
			if (x == -std::numeric_limits<T>::infinity()) {
				return T { 0 };
			}
			if (x == std::numeric_limits<T>::infinity()) {
				return std::numeric_limits<T>::infinity();
			}
			auto n = math::abs(x);
			auto a  = (long long)n;
			auto b  = n - a;
			auto ea = (a == 0 ? 1.0L : exp(a));
			auto eb = (b == 0 ? 1.0L : exp_impl(static_cast<long double>(b), 1.0L, 1.0L, 2, static_cast<long double>(b)));
			if (x < 0) {
				
				return static_cast<T>(1.0L / ea * 1.0L / eb);
			}
			else {
				return static_cast<T>(ea * eb);
			}
		}

		template<std::integral T>
		constexpr inline double exp(T x) {
			if (x == T { 0 }) {
				return T { 1 };
			}
			if (x == T { 1 }) {
				return std::numbers::e_v<double>;
			}
			if (x == T { -1 }) {
				return 1.0 / std::numbers::e_v<double>;
			}
			if (x == std::numeric_limits<T>::min()) {
				return T { 0 };
			}
			if (x == std::numeric_limits<T>::max()) {
				return std::numeric_limits<double>::infinity();
			}
			if (x < 0) {
				return static_cast<double>(1.0L / exp_impl(static_cast<long double>(-x), 1.0L, 1.0L, 2, static_cast<long double>(-x)));
			}
			else {
				return static_cast<double>(exp_impl(static_cast<long double>(x), 1.0L, 1.0L, 2, static_cast<long double>(x)));
			}
		}
	} // namespace math
} // namespace suika