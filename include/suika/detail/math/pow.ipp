#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_POW_IPP
#define _DX_MATH_POW_IPP
#include <concepts>

namespace {
	template<std::floating_point T, std::integral I>
	constexpr inline T ipow(T x, I n) {
		return n == I { 1 } ? x :
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
#endif