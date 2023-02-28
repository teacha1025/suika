#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_FLOOR_IPP
#define _DX_MATH_FLOOR_IPP
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
		constexpr inline T floor(T x) {
			if (x < 0) {
				return x < (int64)x ? (T)((int64)x - 1LL) : (T)(static_cast<int64>(x));
			}
			else {
				return static_cast<T>((int64)x);
			}
		}
		template<std::integral T>
		constexpr inline T floor(T x) {
			return x;
		}
	} // namespace math
} // namespace suika
#endif