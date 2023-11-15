#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_RAD_DEG_IPP
#define _DX_MATH_RAD_DEG_IPP
#include <concepts>
#include "../../def.h"
#include "../../concepts.h"

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
		template<concepts::numbers T>
		constexpr double radian(T x) {
			return x * PI / 180.0;
		}
		template<concepts::numbers T>
		constexpr double degree(T x) {
			return x * 180.0 / PI;
		}
	} // namespace math
} // namespace suika
#endif