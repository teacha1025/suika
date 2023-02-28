#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_ROUND_IPP
#define _DX_MATH_ROUND_IPP
#include <concepts>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace {

}
namespace suika {
	namespace math {
		template<std::floating_point T>
		constexpr inline T round(T x) {
			return static_cast<T>((int64)(x+T(x>T(0)?T(0.5):T(-0.5))));
		}
		template<std::integral T>
		constexpr inline T round(T x) {
			return x;
		}
	} // namespace math
} // namespace suika
#endif