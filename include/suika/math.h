// -----------------------------------------------------------
// 
// constexpr math function
// 
// Copyright 2023 teacha1025
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// -----------------------------------------------------------

#pragma once

#include <concepts>

#include "concepts.h"

namespace suika {
	/// @brief 数学関係
	namespace math {
		/// @brief 絶対値を取得
		/// @tparam T 数値型
		/// @param x 入力値
		/// @return |x|
		template<concepts::numbers T>
		constexpr T abs(T x);

		/// @brief e^xを取得
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return e^x
		template<std::floating_point T>
		constexpr T exp(T x);
		/// @brief e^xを取得
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return e^x
		template<std::integral T>
		constexpr double exp(T x);

		/// @brief xの自然対数を取得
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return ln x
		template<std::floating_point T>
		constexpr T log(T x);
		/// @brief xの自然対数を取得
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return ln x
		template<std::integral T>
		constexpr double log(T x);

		/// @brief 底がnであるxの対数を取得
		/// @tparam T 実数値型
		/// @tparam N 整数値型
		/// @param x 入力値
		/// @param n 底
		/// @return log(n)x
		template<std::floating_point T, concepts::numbers N>
		constexpr T log_n(T x, N n);
		/// @brief 底がnであるxの対数を取得
		/// @tparam T 整数値型
		/// @tparam N 実数値型
		/// @param x 入力値
		/// @param n 底
		/// @return log(n)x
		template<std::integral T, concepts::numbers N>
		constexpr double log_n(T x, N n);

		/// @brief xのn乗を取得
		/// @tparam T 実数型
		/// @tparam I 整数型
		/// @param x 入力値
		/// @param y 乗数値
		/// @return x^n
		template<std::floating_point T, std::integral I>
		constexpr T pow(T x, I y);
		/// @brief xのn乗を取得
		/// @tparam T 実数型
		/// @param x 入力値
		/// @param y 乗数値
		/// @return x^n
		template<std::floating_point T>
		constexpr T pow(T x, T y);
		/// @brief xのn乗を取得
		/// @tparam T 整数型
		/// @param x 入力値
		/// @param y 乗数値
		/// @return x^n
		template<std::integral T>
		constexpr double pow(T x, T y);

		/// @brief 入力値の2乗を取得
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return x^2
		template<std::floating_point T>
		constexpr T sqrt(T x);
		/// @brief 入力値の2乗を取得
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return x^2
		template<std::integral T>
		constexpr double sqrt(T x);

		/// @brief xの正弦を取得
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return sin(x)
		template<std::floating_point T>
		constexpr T sin(T x);
		/// @brief xの正弦を取得
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return sin(x)
		template<std::integral T>
		constexpr double sin(T x);

		/// @brief xの余弦を取得
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return cos(x)
		template<std::floating_point T>
		constexpr T cos(T x);
		/// @brief xの余弦を取得
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return cos(x)
		template<std::integral T>
		constexpr double cos(T x);

		/// @brief xの正接を取得
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return tan(x)
		template<std::floating_point T>
		constexpr T tan(T x);
		/// @brief xの正接を取得
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return tan(x)
		template<std::integral T>
		constexpr double tan(T x);

		/// @brief 天井関数
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return 切り上げられた数
		template<std::floating_point T>
		constexpr T ceil(T x);
		/// @brief 天井関数
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return 切り上げられた数
		template<std::integral T>
		constexpr double ceil(T x);
		/// @brief 床関数
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return 切り捨てられた数
		template<std::floating_point T>
		constexpr T floor(T x);
		/// @brief 床関数
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return 切り捨てられた数
		template<std::integral T>
		constexpr double floor(T x);
		/// @brief 四捨五入関数
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return 四捨五入された数
		template<std::floating_point T>
		constexpr T round(T x);
		/// @brief 四捨五入関数
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return 四捨五入された数
		template<std::integral T>
		constexpr double round(T x);
		/// @brief 0方向まるめ関数
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return 0方向に丸められた数
		template<std::floating_point T>
		constexpr T trunc(T x);
		/// @brief 0方向まるめ関数
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return 0方向に丸められた数
		template<std::integral T>
		constexpr double trunc(T x);
		/// @brief 剰余関数
		/// @tparam T 実数値型
		/// @param x 被除数
		/// @param y 除数
		/// @return x % y
		template<std::floating_point T>
		constexpr T fmod(T x, T y);

		/// @brief 剰余関数
		/// @tparam T 整数値型
		/// @param x 被除数
		/// @param y 除数
		/// @return x % y
		template<std::integral S>
		constexpr S fmod(S x, S y);

		/// @brief sinの逆関数
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return sin^-1(x)
		template<std::floating_point T>
		constexpr T asin(T x);
		/// @brief sinの逆関数
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return sin^-1(x)
		template<std::integral T>
		constexpr double asin(T x);

		/// @brief cosの逆関数
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return cos^-1(x)
		template<std::floating_point T>
		constexpr T acos(T x);
		/// @brief cosの逆関数
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return cos^-1(x)
		template<std::integral T>
		constexpr double acos(T x);

		/// @brief tanの逆関数
		/// @tparam T 実数値型
		/// @param x 入力値
		/// @return tan^-1(x)
		template<std::floating_point T>
		constexpr T atan(T x);
		/// @brief tanの逆関数
		/// @tparam T 整数値型
		/// @param x 入力値
		/// @return tan^-1(x)
		template<std::integral T>
		constexpr double atan(T x);

		/// @brief 度数法から弧度法に変換
		/// @tparam T 数値型
		/// @param x 角度(°)
		/// @return 角度(ラジアン)
		template<concepts::numbers T>
		constexpr double radian(T x);
		/// @brief 弧度法から度数法に変換
		/// @tparam T 数値型
		/// @param x 角度(ラジアン)
		/// @return 角度(°)
		template<concepts::numbers T>
		constexpr double degree(T x);

	} // namespace math
} // namespace suika

#include "detail/math/abs.ipp"
#include "detail/math/exp.ipp"
#include "detail/math/log.ipp"
#include "detail/math/pow.ipp"
#include "detail/math/sqrt.ipp"
#include "detail/math/sin_con_tan.ipp"
#include "detail/math/ceil.ipp"
#include "detail/math/floor.ipp"
#include "detail/math/round.ipp"
#include "detail/math/trunc.ipp"
#include "detail/math/fmod.ipp"
#include "detail/math/asin_acos_atan.ipp"
#include "detail/math/rad_deg.ipp"
