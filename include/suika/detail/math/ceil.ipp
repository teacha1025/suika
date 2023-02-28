#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_CEIL_IPP
#define _DX_MATH_CEIL_IPP
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
		constexpr inline T ceil(T x) {
			if (x < 0) {
				return static_cast<T>((int64)x);
			}
			else {
				return x > (int64)x ? (T)((int64)x + 1L) : x;
			}
		}
		template<std::integral T>
		constexpr inline T ceil(T x) {
			return x;
		}
	}
}
#endif