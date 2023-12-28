// -----------------------------------------------------------
// 
// range
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

#include <string>
#include <format>
#include <algorithm>
#include "def.h"
#include "concepts.h"
#include "base.h"

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
namespace suika {
	/// <summary>
	/// 固定された範囲内の値を持つクラス
	/// </summary>
	/// <typeparam name="minimum">最小値</typeparam>
	/// <typeparam name="maximum">最大値</typeparam>
	template<auto minimum, decltype(minimum) maximum>
	struct range : public detail::ibase{
	private:
		using type = decltype(minimum);
		type val;

	public:
		/// <summary>
		/// 範囲の作成
		/// </summary>
		constexpr range():
			val(minimum) {}

		/// <summary>
		/// 初期値を設定して範囲の作成
		/// </summary>
		/// <param name="v">初期値</param>
		constexpr range(type v):
			val(std::clamp(v, minimum, maximum)) {}

		/// <summary>
		/// 値を取得
		/// </summary>
		/// <returns>範囲内に丸められた値</returns>
		constexpr type get() const {
			return std::clamp(val, minimum, maximum);
		}

		range operator=(type v) && {
			val = std::clamp(v, minimum, maximum);
			return std::move(*this);
		}

		range& operator=(type v) & {
			val = std::clamp(v, minimum, maximum);
			return *this;
		}

		range operator+=(type v) && {
			val += v;
			val = std::clamp(val, minimum, maximum);
			return std::move(*this);
		}

		range& operator+=(type v) & {
			val += v;
			val = std::clamp(val, minimum, maximum);
			return *this;
		}

		range operator-=(type v) && {
			val -= v;
			val = std::clamp(val, minimum, maximum);
			return std::move(*this);
		}

		range& operator-=(type v) & {
			val -= v;
			val = std::clamp(val, minimum, maximum);
			return *this;
		}

		range operator*=(type v) && {
			val *= v;
			val = std::clamp(val, minimum, maximum);
			return std::move(*this);
		}

		range& operator*=(type v) & {
			val *= v;
			val = std::clamp(val, minimum, maximum);
			return *this;
		}

		range operator/=(type v) && {
			val /= v;
			val = std::clamp(val, minimum, maximum);
			return std::move(*this);
		}

		range& operator/=(type v) & {
			val /= v;
			val = std::clamp(val, minimum, maximum);
			return *this;
		}

		range operator%=(type v) && {
			val = fmod(val, v);
			val = std::clamp(val, minimum, maximum);
			return std::move(*this);
		}

		range& operator%=(type v) & {
			val = fmod(val, v);
			val = std::clamp(val, minimum, maximum);
			return *this;
		}

		operator type() const {
			return get();
		}

		/// <summary>
		/// 最大値を取得
		/// </summary>
		/// <returns>範囲の最大値</returns>
		constexpr type max() const {
			return maximum;
		}

		/// <summary>
		/// 最小値を取得
		/// </summary>
		/// <returns>範囲の最小値</returns>
		constexpr type min() const {
			return minimum;
		}

		/// <summary>
		/// 範囲の情報を文字列にして返す
		/// </summary>
		/// <returns>最大値、最小値、現在値</returns>
		string to_string() const {
			return std::format("min:{},max:{},value:{}", minimum, maximum, val);
		}

	};

	/// <summary>
	/// 可変の範囲内の値を持つするクラス
	/// </summary>
	/// <typeparam name="T">値の型</typeparam>
	template<concepts::numbers T>
	class vrange : public detail::ibase{
	private:
		T minimum, maximum;
		T val;

	public:
		/// <summary>
		/// 最小値0、最大値1、初期値0の範囲の作成
		/// </summary>
		constexpr vrange():
			minimum(0),
			maximum(1),
			val(0) {}

		/// <summary>
		/// 最大値を指定して最小値0、初期値0の範囲の作成
		/// </summary>
		/// <param name="max">最大値</param>
		constexpr vrange(T max):
			minimum(0),
			maximum(max),
			val(0) {}

		/// <summary>
		/// 最小値、最大値を指定して初期値を最小値として範囲の作成
		/// </summary>
		/// <param name="min">最小値</param>
		/// <param name="max">最大値</param>
		constexpr vrange(T min, T max):
			minimum(min),
			maximum(max),
			val(min) {}

		/// <summary>
		/// 最小値、最大値、初期値を指定して範囲の作成
		/// </summary>
		/// <param name="min">最小値</param>
		/// <param name="max">最大値</param>
		/// <param name="val">初期値</param>
		constexpr vrange(T min, T max, T val):
			minimum(min),
			maximum(max),
			val(val) {}

		/// <summary>
		/// 値を取得
		/// </summary>
		/// <returns>範囲内に丸められた値</returns>
		constexpr T get() const {
			return std::clamp(val, minimum, maximum);
		}

		vrange operator=(T v) && {
			val = std::clamp(v, minimum, maximum);
			return std::move(*this);
		}

		vrange& operator=(T v) & {
			val = std::clamp(v, minimum, maximum);
			return *this;
		}

		vrange operator+=(T v) && {
			val += v;
			val = std::clamp(val, minimum, maximum);
			return std::move(*this);
		}

		vrange& operator+=(T v) & {
			val += v;
			val = std::clamp(val, minimum, maximum);
			return *this;
		}

		vrange operator-=(T v) && {
			val -= v;
			val = std::clamp(val, minimum, maximum);
			return std::move(*this);
		}

		vrange& operator-=(T v) & {
			val -= v;
			val = std::clamp(val, minimum, maximum);
			return *this;
		}

		vrange operator*=(T v) && {
			val *= v;
			val = std::clamp(val, minimum, maximum);
			return std::move(*this);
		}

		vrange& operator*=(T v) & {
			val *= v;
			val = std::clamp(val, minimum, maximum);
			return *this;
		}

		vrange operator/=(T v) && {
			val /= v;
			val = std::clamp(val, minimum, maximum);
			return std::move(*this);
		}

		vrange& operator/=(T v) & {
			val /= v;
			val = std::clamp(val, minimum, maximum);
			return *this;
		}

		vrange operator%=(T v) && {
			val = fmod(val, v);
			val = std::clamp(val, minimum, maximum);
			return std::move(*this);
		}

		vrange& operator%=(T v) & {
			val = fmod(val, v);
			val = std::clamp(val, minimum, maximum);
			return *this;
		}

		operator T() const {
			return get();
		}

		/// <summary>
		/// 最大値を取得
		/// </summary>
		/// <returns>範囲の最大値</returns>
		constexpr T max() const {
			return maximum;
		}

		/// <summary>
		/// 最小値を取得
		/// </summary>
		/// <returns>範囲の最小値</returns>
		constexpr T min() const {
			return minimum;
		}

		/// <summary>
		/// 最大値を設定
		/// </summary>
		/// <param name="max">範囲の最大値</param>
		constexpr void max(T max) {
			maximum = max;
		}

		/// <summary>
		/// 最小値を設定
		/// </summary>
		/// <param name="min">範囲の最小値</param>
		constexpr void min(T min) {
			minimum = min;
		}

		std::string to_string() {
			return std::to_string(val);
		}

		/// <summary>
		/// 範囲の情報を文字列にして返す
		/// </summary>
		/// <returns>最大値、最小値、現在値</returns>
		virtual string to_string() const override {
			return std::format("min:{},max:{},value:{}", minimum, maximum, val);
		}
	};
} // namespace suika
