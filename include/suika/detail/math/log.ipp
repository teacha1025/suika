#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_MATH_LOG_IPP
#define _DX_MATH_LOG_IPP
#include <bit>
#include <cmath>
#include <concepts>
#include "../../concepts.h"

namespace {
	template<std::floating_point T>
	constexpr inline T e = std::numbers::e_v<T>;
	
	template<typename T>
	constexpr inline T log_iter(T x, T y) {
		return y + T { 2 } * (x - suika::math::exp(y)) / (x + suika::math::exp(y));
	}
	template<typename T>
	constexpr inline T log_impl(T x, T y) {
		return feq(y, log_iter(x, y)) ? y : log_impl(x, log_iter(x, y));
	}
	
	template<typename T>
	constexpr inline T logGT(T x) {
		return x > T { 0.25 } ? log_impl(x, T { 0 }) :
		                        logGT<T>(x * e<T> * e<T> * e<T> * e<T> * e<T>) - T { 5 };
	}
	template<typename T>
	constexpr inline T logLT(T x) {
		return x < T { 1024 } ? log_impl(x, T { 0 }) :
		                        logLT<T>(x / (e<T> * e<T> * e<T> * e<T> * e<T>)) + T { 5 };
	}
} // namespace

namespace suika {
	namespace math {
		template<std::floating_point T>
		constexpr inline T log(T x) {
			if (x < T{ 0 }) {
				throw _FE_INVALID;
			}
			if (x == T{ 0 }) {
				throw _FE_DIVBYZERO;
			}
			if (x == T { 1 }) {
				return T { 0 };
			}
			if (x == std::numbers::e_v<T>) {
				return T { 1.0 };
			}
			if (x == std::numeric_limits<T>::infinity()) {
				return std::numeric_limits<T>::infinity();
			}

			return x >= T{ 1024 } ? logLT(x) : logGT(x);
		}

		template<std::integral T>
		constexpr inline double log(T x) {
			if (x < T{ 0 }) {
				throw _FE_INVALID;
			}
			if (x == T{ 0 }) {
				throw _FE_DIVBYZERO;
			}
			if (x == T{ 1 }) {
				return 0.0;
			}
			if (x == std::numeric_limits<T>::max()) {
				return std::numeric_limits<T>::max();
			}

			return x >= 1024.0 ? logLT(static_cast<double>(x)) : logGT(static_cast<double>(x));
		}

		template<std::floating_point T, concepts::numbers N>
		constexpr inline T log_n(T x, N n) {
			return log(x) / log(n);
		}
		template<std::integral T, concepts::numbers N>
		constexpr inline double log_n(T x, N n) {
			return log(x) / log(n);
		}
	} // namespace math
} // namespace suika
#endif