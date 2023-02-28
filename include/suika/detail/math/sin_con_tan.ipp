#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_SINCOSTAN_IPP
#define _DX_MATH_SINCOSTAN_IPP
//#include <bit>
//#include <cmath>
#include <concepts>

#include "../../concepts.h"

namespace {
	/*template<typename T>
	constexpr inline bool feq(T a, T b) {
		return suika::math::abs(a - b) <= std::numeric_limits<T>::epsilon();
	}*/
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
#endif