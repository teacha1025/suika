// -----------------------------------------------------------
// 
// math function:sin,cos,tan
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

#include "../../concepts.h"

namespace {
	template<typename T>
	constexpr inline T trig_series(T x, T sum, T n, int i, int s, T t) {
		return feq(10000000 * sum, 10000000 * (sum + t * s / n)) ?
				   sum :
				   trig_series(x, sum + t * s / n, n * i * (T(i) + T(1)), i + 2, -s, t * x * x);
	}
} // namespace

namespace suika {
	namespace math {
		template<std::floating_point T>
		constexpr inline T sin(T x) {
			if (x == 0) {
				return T(0);
			}
			auto d = static_cast<ldouble>(x);
			return static_cast<T>(trig_series(d, d, 6.0L, 4, -1, d * d * d));
		}

		template<std::integral T>
		constexpr inline double sin(T x) {
			if (x == 0) {
				return 0.0;
			}
			auto d = static_cast<ldouble>(x);
			return static_cast<double>(trig_series(d, d, 6.0L, 4, -1, d * d * d));
		}

		template<std::floating_point T>
		constexpr inline T cos(T x) {
			auto d = static_cast<ldouble>(x);
			return static_cast<T>(trig_series(d, 1.0L, 2.0L, 3, -1, d * d));
		}

		template<std::integral T>
		constexpr inline double cos(T x) {
			auto d = static_cast<ldouble>(x);
			return trig_series(d, 1.0L, 6.0L, 3, -1, d * d);
		}

		template<std::floating_point T>
		constexpr inline T tan(T x) {
			auto d = static_cast<ldouble>(x);
			return cos(d) != 0.0L ? static_cast<T>(sin(d) / cos(d)) : throw _FE_INVALID;
		}

		template<std::integral T>
		constexpr inline double tan(T x) {
			auto d = static_cast<ldouble>(x);
			return cos(d) != 0.0L ? static_cast<double>(sin(d) / cos(d)) : throw _FE_INVALID;
		}
	}
}