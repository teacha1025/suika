#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_ABS_IPP
#define _DX_MATH_ABS_IPP
#include "../../concepts.h"

namespace suika {
	namespace math {
		template<concepts::numbers T>
		constexpr inline T abs(T x) {
			return x > 0 ? x : -x;
		}
	} // namespace math
} // namespace suika
#endif