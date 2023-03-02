#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_ASINACOSATAN_IPP
#define _DX_MATH_ASINACOSATAN_IPP
//#include <bit>
//#include <cmath>
#include <concepts>
#define DET
namespace {
	/*template<typename T>
	constexpr inline bool feq(T a, T b) {
		return suika::math::abs(a - b) <= std::numeric_limits<T>::epsilon();
	}*/
	template<typename T>
	constexpr inline T mac(T x, T sum, int i, suika::int8 n, T t) {
		return feq(T(0), (n * t / i)) ?
				   sum :
				   mac(x, sum + n * t / i, i + 2, n * -1, t * x * x);
	}

	template<typename T>
	constexpr inline T asin_series(T x, T sum, int n, T t) {
		return feq(sum, sum + t * static_cast<T>(n) / (n + 2)) ?
				   sum :
				   asin_series(x, sum + t * static_cast<T>(n) / (n + 2), n + 2,
							   t * x * x * static_cast<T>(n) / (n + 3));
	}
} // namespace

namespace suika {
	namespace math {
		template<std::floating_point T>
		constexpr inline T asin(T x) {
			auto d = static_cast<ldouble>(x);
			return x == T { -1 } ? static_cast<T>(-PI_HALF) :
				   x == T { 1 }  ? static_cast<T>(PI_HALF) :
				   x > T { -1 } && x < T { 1 } ? static_cast<T>(asin_series(d, d, 1, d * d * d / 2.0L)) : throw _FE_INVALID;
		}
		template<std::integral T>
		constexpr inline double asin(T x) {
			auto d = static_cast<ldouble>(x);
			return x == -1.0 ? -PI_HALF :
				   x == 1.0  ? PI_HALF :
				   x > -1.0 && x < 1.0 ? static_cast<double>(asin_series(d, d, 1, d * d * d / 2.0L)) : throw _FE_INVALID;
		}

		template<std::floating_point T>
		constexpr inline T acos(T x) {
			auto d = static_cast<ldouble>(x);
			return x == -1.0 ? static_cast<T>(PI) :
				   x == 1.0  ? T(0) :
				   x > -1.0 && x < 1.0 ? static_cast<double>(PI_HALF_LD - asin_series(d, d, 1, d * d * d / 2.0L)) : throw _FE_INVALID;
		}
		template<std::integral T>
		constexpr inline double acos(T x) {
			auto d = static_cast<ldouble>(x);
			return x == -1.0 ? -PI :
				   x == 1.0  ? 0 :
				   x > -1.0 && x < 1.0 ? static_cast<double>(PI_HALF_LD - asin_series(d, d, 1, d * d * d / 2.0L)) : throw _FE_INVALID;
		}

		template<std::floating_point T>
		constexpr inline T atan(T x) {
			return x == T(1)			 ? static_cast<T>(PI_HALF / 2.0) :
				   x == T(-1)			? static_cast<T>(-PI_HALF / 2.0) :
				   math::abs(x) < T(1.0) ? static_cast<T>(mac(static_cast<ldouble>(x), 0.0L, 1, 1, static_cast<ldouble>(x))) :
										   static_cast<T>(PI_HALF_LD - mac(static_cast<ldouble>(1.0L / x), 0.0L, 1, 1, static_cast<ldouble>(1.0L / x)));
		}
		template<std::integral T>
		constexpr inline double atan(T x) {
			return x == 1.0		   ? PI_HALF / 2.0 :
				   x == -1.0		  ? -PI_HALF / 2.0 :
				   math::abs(x) < 1.0 ? static_cast<double>(mac(static_cast<ldouble>(x), 0.0L, 1, 1, static_cast<ldouble>(x))) :
										static_cast<double>(PI_HALF_LD - mac(static_cast<ldouble>(1.0L / x), 0.0L, 1, 1, static_cast<ldouble>(1.0L / x)));
		}
	} // namespace math
} // namespace suika
#undef DET
#endif