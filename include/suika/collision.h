// -----------------------------------------------------------
// 
// shape collision
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

#include "rect.h"
#include "circle.h"
#include "line.h"
#include "point.h"

namespace suika {
	namespace detail {
		bool collision(const point<double>& a, const circle& b);
		bool collision(const point<double>& a, const line& b);
		bool collision(const point<double>& a, const rect& b);
	}
	/// <summary>
	/// 2次元図形同士の当たり判定
	/// </summary>
	namespace collision_2d {
		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		template<concepts::numbers T>
		bool collision(const point<T>& a, const point<T>& b) {
			return a == b;
		}

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		template<concepts::numbers T>
		bool collision(const point<T>& a, const circle& b) {
			return detail::collision(a, b);
		}

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		template<concepts::numbers T>
		bool collision(const point<T>& a, const line& b) {
			return detail::collision(a, b);
		}

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		template<concepts::numbers T>
		bool collision(const point<T>& a, const rect& b) {
			return detail::collision(a, b);
		}

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		bool collision(const circle& a, const circle& b);

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		bool collision(const circle& a, const line& b);

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		bool collision(const circle& a, const rect& b);

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		bool collision(const line& a, const line& b);

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		bool collision(const line& a, const rect& b);

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		bool collision(const rect& a, const rect& b);

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		template<concepts::numbers T>
		bool collision(const circle& a, const point<T>& b) {
			return collision(b, a);
		}

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		template<concepts::numbers T>
		bool collision(const line& a, const point<T>& b) {
			return collision(b, a);
		}

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		template<concepts::numbers T>
		bool collision(const rect& a, const point<T>& b) {
			return collision(b, a);
		}

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		bool collision(const line& a, const circle& b);

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		bool collision(const rect& a, const circle& b);

		/// <summary>
		/// 当たり判定を取得
		/// </summary>
		/// <param name="a">図形A</param>
		/// <param name="b">図形B</param>
		/// <returns>2つの図形A,Bが接触しているか</returns>
		bool collision(const rect& a, const line& b);
	}
}
