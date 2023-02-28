#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_SQRT_IPP
#define _DX_MATH_SQRT_IPP
#include <cmath>
#include <concepts>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace {
	/*template<typename T>
	constexpr inline bool feq(T a, T b) {
		return suika::math::abs(a - b) <= std::numeric_limits<T>::epsilon();
	}*/
	template<typename T>
	constexpr inline T sqrt_impl(T x, T g) {
		return feq(g, (g + x / g) / T(2)) ? g : sqrt_impl(x, (g + x / g) / T(2));
	}
} // namespace

namespace suika {
	namespace math {
		template<std::floating_point T>
		constexpr inline T sqrt(T x) {
			return x == 0 ? 0 : (x > 0 ? sqrt_impl(x, x) : throw _FE_INVALID);
		}

		template<std::integral T>
		constexpr inline double sqrt(T x) {
			return sqrt<double>(static_cast<double>(x));
		}
	}
} // namespace suika
#endif