#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_EXP_IPP
#define _DX_MATH_EXP_IPP
#include <cmath>
#include <bit>
#include <concepts>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace {
	template<typename T>
	constexpr inline bool feq(T a, T b) {
		return suika::math::abs(a - b) <= std::numeric_limits<T>::epsilon();
	}
	template<typename T>
	constexpr inline T exp_impl(T x, T sum, T n, int i, T t) {
		auto d = t / n;
		return feq(sum, sum + d) ? sum : exp_impl(x, sum + d, n * i, i + 1, t * x);
	}
}

namespace suika {
	namespace math {
		template<std::floating_point T>
		constexpr inline T exp(T x) {
			if (x == T { 0 }) {
				return T { 1 };
			}
			if (x == T{ 1 }) {
				return std::numbers::e_v<T>;
			}
			if (x == T { -1 }) {
				return T(1.0) / std::numbers::e_v<T>;
			}
			if (x == -std::numeric_limits<T>::infinity()) {
				return T { 0 };
			}
			if (x == std::numeric_limits<T>::infinity()) {
				return std::numeric_limits<T>::infinity();
			}
			auto n = math::abs(x);
			auto a  = (long long)n;
			auto b  = n - a;
			auto ea = (a == 0 ? 1.0L : exp(a));
			auto eb = (b == 0 ? 1.0L : exp_impl(static_cast<long double>(b), 1.0L, 1.0L, 2, static_cast<long double>(b)));
			if (x < 0) {
				
				return static_cast<T>(1.0L / ea * 1.0L / eb);
			}
			else {
				return static_cast<T>(ea * eb);
			}
		}

		template<std::integral T>
		constexpr inline double exp(T x) {
			if (x == T { 0 }) {
				return T { 1 };
			}
			if (x == T { 1 }) {
				return std::numbers::e_v<double>;
			}
			if (x == T { -1 }) {
				return 1.0 / std::numbers::e_v<double>;
			}
			if (x == std::numeric_limits<T>::min()) {
				return T { 0 };
			}
			if (x == std::numeric_limits<T>::max()) {
				return std::numeric_limits<double>::infinity();
			}
			if (x < 0) {
				return static_cast<double>(1.0L / exp_impl(static_cast<long double>(-x), 1.0L, 1.0L, 2, static_cast<long double>(-x)));
			}
			else {
				return static_cast<double>(exp_impl(static_cast<long double>(x), 1.0L, 1.0L, 2, static_cast<long double>(x)));
			}
		}
	} // namespace math
} // namespace suika
#endif