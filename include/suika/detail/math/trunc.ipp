#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_TRUNC_IPP
#define _DX_MATH_TRUNC_IPP
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
		constexpr inline T trunc(T x) {
			return (T)(static_cast<int64>(x));
		}
		template<std::integral T>
		constexpr inline T trunc(T x) {
			return x;
		}
	} // namespace math
} // namespace suika
#endif