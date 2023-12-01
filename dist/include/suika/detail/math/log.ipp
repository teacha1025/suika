// -----------------------------------------------------------
// 
// math function:log
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
#include <bit>
#include <cmath>
#include <concepts>

#include "../../concepts.h"

namespace {
	template<std::floating_point T>
	constexpr inline T e = std::numbers::e_v<T>;
	
	template<typename T>
	constexpr inline T log_iter(T x, T y) {
		return y + T { 2 } * (x - suika::math::exp(y)) / (x + suika::math::exp(y));
	}

	template<typename T>
	constexpr inline T log_impl(T x, T y) {
		return feq(y, log_iter(x, y)) ? y : log_impl(x, log_iter(x, y));
	}
	
	template<typename T>
	constexpr inline T logGT(T x) {
		return x > T { 0.25 } ? log_impl(x, T { 0 }) :
								logGT<T>(x * e<T> * e<T> * e<T> * e<T> * e<T>) - T { 5 };
	}

	template<typename T>
	constexpr inline T logLT(T x) {
		return x < T { 1024 } ? log_impl(x, T { 0 }) :
								logLT<T>(x / (e<T> * e<T> * e<T> * e<T> * e<T>)) + T { 5 };
	}
} // namespace

namespace suika {
	namespace math {
		template<std::floating_point T>
		constexpr inline T log(T x) {
			if (x < T{ 0 }) {
				throw _FE_INVALID;
			}
			if (x == T{ 0 }) {
				throw _FE_DIVBYZERO;
			}
			if (x == T { 1 }) {
				return T { 0 };
			}
			if (x == std::numbers::e_v<T>) {
				return T { 1.0 };
			}
			if (x == std::numeric_limits<T>::infinity()) {
				return std::numeric_limits<T>::infinity();
			}
			return x >= T{ 1024 } ? logLT(x) : logGT(x);
		}

		template<std::integral T>
		constexpr inline double log(T x) {
			if (x < T{ 0 }) {
				throw _FE_INVALID;
			}
			if (x == T{ 0 }) {
				throw _FE_DIVBYZERO;
			}
			if (x == T{ 1 }) {
				return 0.0;
			}
			if (x == std::numeric_limits<T>::max()) {
				return std::numeric_limits<T>::max();
			}

			return x >= 1024.0 ? logLT(static_cast<double>(x)) : logGT(static_cast<double>(x));
		}

		template<std::floating_point T, concepts::numbers N>
		constexpr inline T log_n(T x, N n) {
			return log(x) / log(n);
		}

		template<std::integral T, concepts::numbers N>
		constexpr inline double log_n(T x, N n) {
			return log(x) / log(n);
		}
	} // namespace math
} // namespace suika