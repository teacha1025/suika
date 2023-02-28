#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_FMOD_IPP
#define _DX_MATH_FMOD_IPP
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
#endif