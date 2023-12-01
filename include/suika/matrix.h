// -----------------------------------------------------------
// 
// matrix
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

#include <vector>

#include "def.h"
#include "type.h"
#include "concepts.h"
#include "point.h"

namespace suika {
	template<concepts::numbers T>
	struct matrix;

	template<concepts::numbers T>
	struct matrix2x2 {
	private:
		T vec[2][2];

	public:
		matrix2x2() {
			vec[0][0] = vec[0][1] = vec[1][0] = vec[1][1] = static_cast<T>(0);
		}

		matrix2x2(const std::vector<T>& ary) {
			if (ary.size() != 4) {
				throw;
			}
			vec[0][0] = ary[0];
			vec[0][1] = ary[1];
			vec[1][0] = ary[2];
			vec[1][1] = ary[3];
		}

		matrix2x2(float v[2][2]) {
			std::memcpy(vec, v, sizeof(float) * 4);
		}

		const T& at(uint n, uint m) const {
			return vec[n][m];
		}

		T& at(uint n, uint m) {
			return vec[n][m];
		}

		template<concepts::numbers t>
		operator matrix<t>() const {
			matrix<t> ret(2, 2);
			ret.at(0, 0) = vec[0][0];
			ret.at(0, 1) = vec[0][1];
			ret.at(1, 0) = vec[1][0];
			ret.at(1, 1) = vec[1][1];
			return ret;
		}

		template<concepts::numbers t>
		operator matrix2x2<t>() const {
			matrix2x2<t> ret;
			ret.vec[0][0] = vec[0][0];
			ret.vec[0][1] = vec[0][1];
			ret.vec[1][0] = vec[1][0];
			ret.vec[1][1] = vec[1][1];
			return ret;
		}
	};

	template<concepts::numbers T>
	struct matrix4x4 {
	private:
		T vec[4][4];

	public:
		matrix4x4() {
			std::fill(&vec[0][0], &vec[3][3], static_cast<T>(0));
		}

		matrix4x4(const std::vector<T>& ary) {
			if (ary.size() != 16) {
				throw;
			}
			for (uint y = 0; y < 4; y++) {
				for (uint x = 0; x < 4; x++) {
					vec[y][x] = ary[x + 4 * y];
				}
			}
		}

		matrix4x4(float v[4][4]) {
			std::memcpy(vec, v, sizeof(float) * 16);
		}

		const T& at(uint n, uint m) const {
			return vec[n][m];
		}

		T& at(uint n, uint m) {
			return vec[n][m];
		}

		template<concepts::numbers t>
		operator matrix<t>() const {
			matrix<t> ret(4, 4);
			for (uint y = 0; y < 4; y++) {
				for (uint x = 0; x < 4; x++) {
					ret.at(y, x) = vec[y][x];
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		operator matrix4x4<t>() const {
			matrix4x4<t> ret;
			for (uint y = 0; y < 4; y++) {
				for (uint x = 0; x < 4; x++) {
					ret.vec[y][x] = vec[y][x];
				}
			}
			return ret;
		}
	};

	/// <summary>
	/// n行m列の行列を表すクラス	
	/// </summary>
	/// <typeparam name="T">行列の数値型</typeparam>
	template<concepts::numbers T = float>
	struct matrix {
	private:
		using row = std::vector<T>;
		using col = row;
		using mat = std::vector<row>;

		mat vec;

		//n行,m列
		uint n = 1, m = 1;
	public:
		/// <summary>
		/// 1x1の行列を生成する
		/// </summary>
		matrix() {
			resize(1, 1, 0);
		}

		/// <summary>
		/// nxnの行列を生成する
		/// </summary>
		/// <param name="n">行および列数</param>
		/// <param name="fill">初期化値</param>
		matrix(uint n, T fill = 0) {
			resize(n, n, fill);
		}

		/// <summary>
		/// nxmの行列を生成する
		/// </summary>
		/// <param name="n">行数</param>
		/// <param name="m">列数</param>
		/// <param name="fill">初期化値</param>
		matrix(uint n, uint m, T fill = 0) {
			resize(n, m, fill);
		}

		/// <summary>
		/// 2次元配列から行列を生成する
		/// </summary>
		/// <param name="mt">2次元配列</param>
		matrix(const mat& mt) {
			vec = mt;
			n = mt.size();
			m = mt[0].size();
		}

		/// <summary>
		/// nxmの行列を配列から生成する
		/// </summary>
		/// <param name="n">行数</param>
		/// <param name="m">列数</param>
		/// <param name="ary">配列</param>
		/// <param name="fill">初期化値</param>
		matrix(uint n, uint m, const std::vector<T>& ary, T fill = 0) {
			if (ary.size() != n * m) {
				throw;
			}
			resize(n, m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					vec[y][x] = ary[x + m * y];
				}
			}
		}

		/// <summary>
		/// 行列をnxmの行列に初期化する
		/// </summary>
		/// <param name="n">行数</param>
		/// <param name="m">列数</param>
		/// <param name="fill">初期化値</param>
		void resize(uint n, uint m, T fill = 0) {
			this->n = n;
			this->m = m;

			vec.resize(n);
			for (auto& r : vec) {
				r.resize(m);
				std::fill(r.begin(), r.end(), fill);
			}
		}

		/// <summary>
		/// n,mの値を取得する
		/// </summary>
		/// <param name="n">行番号</param>
		/// <param name="m">列番号</param>
		/// <returns>n,mの値</returns>
		const T& at(uint n, uint m) const {
			return vec[n][m];
		}

		/// <summary>
		/// n,mの参照を取得する
		/// </summary>
		/// <param name="n">行番号</param>
		/// <param name="m">列番号</param>
		/// <returns>n,mの参照</returns>
		T& at(uint n, uint m) {
			return vec[n][m];
		}

		/// <summary>
		/// n行m列の行列の行数を取得する
		/// </summary>
		/// <returns>{m,n}</returns>
		point<uint> size() const {
			return { m,n };
		}

		/// <summary>
		/// 任意の数値型の行列にキャストする
		/// </summary>
		/// <typeparam name="t"></typeparam>
		template<concepts::numbers t>
		operator matrix<t>() const {
			matrix<t> ret(n, m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					ret.at(y, x) = static_cast<t>(vec[y][x]);
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		operator matrix4x4<t>() const {
			if (n != 4 || m != 4) {
				throw;
			}
			matrix4x4<t> ret;
			for (uint y = 0; y < 4; y++) {
				for (uint x = 0; x < 4; x++) {
					ret.at(y, x) = static_cast<t>(vec[y][x]);
				}
			}
			return ret;
		}

		bool operator == (const matrix& mt) const {
			if (n != mt.n || m != mt.m) {
				return false;
			}
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					if (vec[y][x] != mt.at(y, x)) {
						return false;
					}
				}
			}
			return true;
		}

		matrix operator +() const {
			return *this;
		}

		matrix operator -() const {
			matrix ret(n, m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					ret.at(y, x) = -at(y, x);
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		auto operator + (const matrix<t>& mt) const {
			if (n != mt.n || m != mt.m) {
				throw;
			}
			matrix<decltype(vec[0][0] + mt.at(0, 0))> ret(n, m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					ret.at(y, x) = at(y, x) + mt.at(y, x);
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		auto operator - (const matrix<t>& mt) const {
			if (n != mt.n || m != mt.m) {
				throw;
			}
			matrix<decltype(vec[0][0] - mt.at(0, 0))> ret(n, m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					ret.at(y, x) = at(y, x) - mt.at(y, x);
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		auto operator * (const matrix<t>& mt) const {
			if (m != mt.n) {
				throw;
			}
			matrix<decltype(vec[0][0] * mt.at(0, 0))> ret(n, mt.m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < mt.m; x++) {
					T sum = 0;
					for (uint i = 0; i < m; i++) {
						sum += at(y, i) * mt.at(i, x);
					}
					ret.at(y, x) = sum;
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		auto operator + (t v) const {
			matrix<decltype(vec[0][0] + v)> ret(n, m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					ret.at(y, x) = at(y, x) + v;
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		auto operator - (t v) const {
			matrix<decltype(vec[0][0] - v)> ret(n, m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					ret.at(y, x) = at(y, x) - v;
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		auto operator * (t v) const {
			matrix<decltype(vec[0][0] * v)> ret(n, m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					ret.at(y, x) = at(y, x) * v;
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		auto operator *(const vector2<t>& v) {
			if (m != 2) {
				throw;
			}
			vector2<decltype(vec[0][0] * v.x)> ret;
			ret.x = at(0, 0) * v.x + at(0, 1) * v.y;
			ret.y = at(1, 0) * v.x + at(1, 1) * v.y;
			return ret;
		}

		template<concepts::numbers t>
		auto operator *(const vector3<t>& v) {
			if (m != 3) {
				throw;
			}
			vector3<decltype(vec[0][0] * v.x)> ret;
			ret.x = at(0, 0) * v.x + at(0, 1) * v.y + at(0, 2) * v.z;
			ret.y = at(1, 0) * v.x + at(1, 1) * v.y + at(1, 2) * v.z;
			ret.z = at(2, 0) * v.x + at(2, 1) * v.y + at(2, 2) * v.z;
			return ret;
		}

		template<concepts::numbers t>
		auto operator / (t v) const {
			matrix<decltype(vec[0][0] / v.x)> ret(n, m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					ret.at(y, x) = at(y, x) / v;
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		matrix& operator += (const matrix<t>& mt) {
			if (n != mt.n || m != mt.m) {
				throw;
			}
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					at(y, x) += mt.at(y, x);
				}
			}
			return *this;
		}

		template<concepts::numbers t>
		matrix& operator -= (const matrix<t>& mt) {
			if (n != mt.n || m != mt.m) {
				throw;
			}
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < m; x++) {
					vec[y][x] += mt.vec[y][x];
				}
			}
			return *this;
		}

		template<concepts::numbers t>
		matrix& operator *= (const matrix<t>& mt) {
			if (m != mt.n) {
				throw;
			}
			matrix ret(n, mt.m);
			for (uint y = 0; y < n; y++) {
				for (uint x = 0; x < mt.m; x++) {
					T sum = 0;
					for (uint i = 0; i < m; i++) {
						sum += at(y, i) * mt.at(i, x);
					}
					ret.at(y, x) = sum;
				}
			}
			*this = ret;
			return *this;
		}
	};

	template<concepts::numbers T, concepts::numbers t>
	auto operator +(t v, const matrix<T>& mt) {
		uint n = mt.size().y, m = mt.size().x;
		matrix<decltype(v + mt.at(0, 0))>  ret(n, m);
		for (uint y = 0; y < n; y++) {
			for (uint x = 0; x < m; x++) {
				ret.at(y, x) = v + mt.at(y, x);
			}
		}
		return ret;
	}

	template<concepts::numbers T, concepts::numbers t>
	auto operator -(t v, const matrix<T>& mt) {
		uint n = mt.size().y, m = mt.size().x;
		matrix<decltype(v - mt.at(0, 0))>  ret(n, m);
		for (uint y = 0; y < n; y++) {
			for (uint x = 0; x < m; x++) {
				ret.at(y, x) = v - mt.at(y, x);
			}
		}
		return ret;
	}

	template<concepts::numbers T, concepts::numbers t>
	auto operator *(t v, const matrix<T>& mt) {
		uint n = mt.size().y, m = mt.size().x;
		matrix<decltype(v* mt.at(0, 0))> ret(n, m);
		for (uint y = 0; y < n; y++) {
			for (uint x = 0; x < m; x++) {
				ret.at(y, x) = v * mt.at(y, x);
			}
		}
		return ret;
	}

	template<concepts::numbers T, concepts::numbers t>
	auto operator /(t v, const matrix<T>& mt) {
		uint n = mt.size().y, m = mt.size().x;
		matrix<decltype(v / mt.at(0, 0))> ret(n, m);
		for (uint y = 0; y < n; y++) {
			for (uint x = 0; x < m; x++) {
				ret.at(y, x) = v / mt.at(y, x);
			}
		}
		return ret;
	}

	template<concepts::numbers T, concepts::numbers t>
	auto operator *(const matrix<T>& m, const vector2<t>& v) {
		if (m.size().x != 2) {
			throw;
		}
		vector2<decltype(m.at(0, 0)* v.x)> ret;
		ret.x = m.at(0, 0) * v.x + m.at(0, 1) * v.y;
		ret.y = m.at(1, 0) * v.x + m.at(1, 1) * v.y;
		return ret;
	}

	template<concepts::numbers T, concepts::numbers t>
	auto operator *(const matrix<T>& m, const vector3<t>& v) {
		if (m.size().x != 3) {
			throw;
		}
		vector3<decltype(m.at(0, 0)* v.x)> ret;
		ret.x = m.at(0, 0) * v.x + m.at(0, 1) * v.y + m.at(0, 2) * v.z;
		ret.y = m.at(1, 0) * v.x + m.at(1, 1) * v.y + m.at(1, 2) * v.z;
		ret.z = m.at(2, 0) * v.x + m.at(2, 1) * v.y + m.at(2, 2) * v.z;
		return ret;
	}

	template<concepts::numbers T, concepts::numbers t>
	auto operator *(const matrix<T>& m, const vector4<t>& v) {
		if (m.size().x != 4) {
			throw;
		}
		vector4<decltype(m.at(0, 0)* v.x)> ret;
		ret.x = m.at(0, 0) * v.x + m.at(0, 1) * v.y + m.at(0, 2) * v.w + m.at(0, 3) * v.w;
		ret.y = m.at(1, 0) * v.x + m.at(1, 1) * v.y + m.at(1, 2) * v.z + m.at(1, 3) * v.w;
		ret.z = m.at(2, 0) * v.x + m.at(2, 1) * v.y + m.at(2, 2) * v.z + m.at(2, 3) * v.w;
		ret.w = m.at(3, 0) * v.x + m.at(3, 1) * v.y + m.at(3, 2) * v.z + m.at(3, 3) * v.w;
		return ret;
	}

	namespace vector {
		/// <summary>
		/// 行列と2次元ベクトルとの積算
		/// </summary>
		/// <param name="m">2列の行列</param>
		/// <param name="v">2次元ベクトル</param>
		/// <returns>m*v</returns>
		/// <remarks>行列の列数は2である必要がある</remarks>
		template<concepts::numbers T, concepts::numbers t>
		auto mul(const matrix<T>& m, const vector2<t>& v) {
			return m * v;
		}

		/// <summary>
		/// 行列と3次元ベクトルとの積算
		/// </summary>
		/// <param name="m">3列の行列</param>
		/// <param name="v">3次元ベクトル</param>
		/// <returns>m*v</returns>
		/// <remarks>行列の列数は3である必要がある</remarks>
		template<concepts::numbers T, concepts::numbers t>
		auto mul(const matrix<T>& m, const vector3<t>& v) {
			return m * v;
		}

		/// <summary>
		/// 行列と4次元ベクトルとの積算
		/// </summary>
		/// <param name="m">4列の行列</param>
		/// <param name="v">4次元ベクトル</param>
		/// <returns>m*v</returns>
		/// <remarks>行列の列数は4である必要がある</remarks>
		template<concepts::numbers T, concepts::numbers t>
		auto mul(const matrix<T>& m, const vector4<t>& v) {
			return m * v;
		}

		/// <summary>
		/// 行列同士の積算
		/// </summary>
		/// <param name="m1">左辺値</param>
		/// <param name="m2">右辺値</param>
		/// <returns>m1*m2</returns>
		template<concepts::numbers T>
		auto mul(const matrix<T>& m1, const matrix<T>& m2) {
			return m1 * m2;
		}

		/// <summary>
		/// ベクトルを行列に変換する
		/// </summary>
		/// <param name="v">2次元ベクトル</param>
		/// <returns>1x2行列</returns>
		template<concepts::numbers T>
		matrix<T> to_matrix(const vector2<T>& v) {
			matrix<T> ret(1, 2);
			ret.at(0, 0) = v.x;
			ret.at(0, 1) = v.y;
			return ret;
		}

		/// <summary>
		/// ベクトルを行列に変換する
		/// </summary>
		/// <param name="v">3次元ベクトル</param>
		/// <returns>1x3行列</returns>
		template<concepts::numbers T>
		matrix<T> to_matrix(const vector3<T>& v) {
			matrix<T> ret(1, 3);
			ret.at(0, 0) = v.x;
			ret.at(0, 1) = v.y;
			ret.at(0, 2) = v.z;
			return ret;
		}

		/// <summary>
		/// ベクトルを行列に変換する
		/// </summary>
		/// <param name="v">4次元ベクトル</param>
		/// <returns>1x4行列</returns>
		template<concepts::numbers T>
		matrix<T> to_matrix(const vector4<T>& v) {
			matrix<T> ret(1, 4);
			ret.at(0, 0) = v.x;
			ret.at(0, 1) = v.y;
			ret.at(0, 2) = v.z;
			ret.at(0, 3) = v.w;
			return ret;
		}

		/// <summary>
		/// 行列をベクトルに変換する
		/// </summary>
		/// <param name="mt">1x2または2x1の行列</param>
		/// <returns>2次元ベクトル</returns>
		template<concepts::numbers T>
		vector2<T> to_vector2(const matrix<T>& mt) {
			uint n = mt.size().y;
			uint m = mt.size().x;
			if ((n == 1 && m == 2)) {
				return vector2<T>(mt.vec[0][0], mt.vec[0][1]);
			}
			if ((n == 2 && m == 1)) {
				return vector2<T>(mt.vec[0][0], mt.vec[1][0]);
			}
			else {
				throw;
			}
		}

		/// <summary>
		/// 行列をベクトルに変換する
		/// </summary>
		/// <param name="mt">1x3または3x1の行列</param>
		/// <returns>3次元ベクトル</returns>
		template<concepts::numbers T>
		vector3<T> to_vector3(const matrix<T>& mt) {
			uint n = mt.size().y;
			uint m = mt.size().x;
			if ((n == 1 && m == 3)) {
				return vector3<T>(mt.vec[0][0], mt.vec[0][1], mt.vec[0][2]);
			}
			if ((n == 3 && m == 1)) {
				return vector3<T>(mt.vec[0][0], mt.vec[1][0], mt.vec[2][0]);
			}
			else {
				throw;
			}
		}

		/// <summary>
		/// 行列をベクトルに変換する
		/// </summary>
		/// <param name="mt">1x4または4x1の行列</param>
		/// <returns>4次元ベクトル</returns>
		template<concepts::numbers T>
		vector4<T> to_vector4(const matrix<T>& mt) {
			uint n = mt.size().y;
			uint m = mt.size().x;
			if ((n == 1 && m == 4)) {
				return vector4<T>(mt.vec[0][0], mt.vec[0][1], mt.vec[0][2], mt.vec[0][3]);
			}
			if ((n == 4 && m == 1)) {
				return vector4<T>(mt.vec[0][0], mt.vec[1][0], mt.vec[2][0], mt.vec[3][0]);
			}
			else {
				throw;
			}
		}

		/// <summary>
		/// 行列の転置
		/// </summary>
		/// <param name="mt">元の行列</param>
		/// <returns>mt^T</returns>
		template<concepts::numbers T>
		matrix<T> transpose(const matrix<T>& mt) {
			matrix<T> ret;
			ret.resize(mt.size().x, mt.size().y);
			for (uint y = 0; y < mt.size().y; y++) {
				for (uint x = 0; x < mt.size().x; x++) {
					ret.at(x, y) = mt.at(y, x);
				}
			}
			return ret;
		}

		/// <summary>
		/// nxnの対角行列を生成する
		/// </summary>
		/// <param name="n">行列の大きさ</param>
		/// <param name="fill">対角成分の値</param>
		/// <returns>nxnの対角行列</returns>
		template<concepts::numbers T>
		matrix<T> identity(uint n, T fill = 1) {
			matrix<T> ret(n, n);
			for (uint i = 0; i < n; i++) {
				ret.at(i, i) = fill;
			}
			return ret;
		}

		/// <summary>
		/// 行列式の計算
		/// </summary>
		/// <param name="mt">入力の行列</param>
		/// <returns>det(mt)</returns>
		template<concepts::numbers T>
		double determinant(const matrix<T>& mt) {
			if (mt.size().x != mt.size().y) {
				throw;
			}
			uint n = mt.size().x;
			if (n == 1) {
				return mt.at(0, 0);
			}
			else if (n == 2) {
				return mt.at(0, 0) * mt.at(1, 1) - mt.at(0, 1) * mt.at(1, 0);
			}
			else if (n == 3) {
				return mt.at(0, 0) * mt.at(1, 1) * mt.at(2, 2) + mt.at(0, 1) * mt.at(1, 2) * mt.at(2, 0) + mt.at(0, 2) * mt.at(1, 0) * mt.at(2, 1)
					- mt.at(0, 0) * mt.at(1, 2) * mt.at(2, 1) - mt.at(0, 1) * mt.at(1, 0) * mt.at(2, 2) - mt.at(0, 2) * mt.at(1, 1) * mt.at(2, 0);
			}
			else {
				double det = 1, buf;
				matrix<double> tmp = mt;

				for (uint i = 0; i < n; i++) {
					for (uint j = 0; j < n; j++) {
						if (i < j) {
							if (!tmp.at(i, i)) {
								double max = 0;
								int max_i = i;
								for (uint k = i + 1; k < n; k++) {
									if (max < tmp.at(k, i)) {
										max = tmp.at(k, i);
										max_i = k;
									}
								}
								if (max == 0) {
									throw;
								}
								for (uint k = 0; k < n; k++) {
									std::swap(tmp.at(i, k), tmp.at(max_i, k));
								}
								det *= -1;
							}
							buf = tmp.at(j, i) / tmp.at(i, i);
							for (uint k = 0; k < n; k++) {
								tmp.at(j, k) -= tmp.at(i, k) * buf;
							}
						}
					}
				}

				for (uint i = 0; i < n; i++) {
					det *= tmp.at(i, i);
				}

				return det;
			}
		}

		/// <summary>
		/// 逆行列の計算
		/// </summary>
		/// <param name="mt">入力の行列</param>
		/// <returns>mt^-1</returns>
		template<concepts::numbers T>
		matrix<T> inverse(const matrix<T>& mt) {
			if (mt.size().x != mt.size().y) {
				throw;
			}
			uint n = mt.size().x;


			if (n == 1) {
				if (!mt.at(0, 0)) {
					throw;
				}
				return 1.0 / mt;
			}
			else if (n == 2) {
				matrix<T> ret(2, 2, { mt.at(1, 1),-mt.at(0, 1),-mt.at(1, 0),mt.at(0, 0) });
				if (auto t = mt.at(0, 0) * mt.at(1, 1) - mt.at(0, 1) * mt.at(1, 0); !t) {
					throw;
				}
				return ret;
			}

			matrix<double> ret(n, n);
			matrix<double> tmp = mt;

			auto swap = [&](uint y1, uint y2) {
				for (uint x = 0; x < n; x++) {
					std::swap(tmp.at(y1, x), tmp.at(y2, x));
					std::swap(ret.at(y1, x), ret.at(y2, x));
				}
				};

			ret = identity<double>(n);

			for (uint i = 0; i < n; i++) {
				double buf = tmp.at(i, i);
				if (buf == 0) {
					double max = 0;
					int max_i = i;
					for (uint j = i + 1; j < n; j++) {
						if (max < tmp.at(j, i)) {
							max = tmp.at(j, i);
							max_i = j;
						}
					}
					if (max == 0) {
						throw;
					}
					swap(i, max_i);
					buf = tmp.at(i, i);
				}
				for (uint j = 0; j < n; j++) {
					tmp.at(i, j) /= buf;
					ret.at(i, j) /= buf;
				}
				for (uint j = 0; j < n; j++) {
					if (i != j) {
						buf = tmp.at(j, i);
						for (uint k = 0; k < n; k++) {
							tmp.at(j, k) -= tmp.at(i, k) * buf;
							ret.at(j, k) -= ret.at(i, k) * buf;
						}
					}
				}
			}
			return ret;
		}

		/// <summary>
		/// ロール方向に回転
		/// </summary>
		/// <param name="roll">角度</param>
		/// <returns>回転行列</returns>
		template<concepts::numbers T>
		matrix<T> rotation_roll(double roll) {
			std::vector<double> v(16);
			v[0] = std::cos(roll);
			v[1] = -std::sin(roll);
			v[4] = std::sin(roll);
			v[5] = std::cos(roll);
			v[10] = 1;
			v[15] = 1;
			return matrix<T>(4, 4, v);
		}

		/// <summary>
		/// ピッチ方向に回転
		/// </summary>
		/// <param name="pitch">角度</param>
		/// <returns>回転行列</returns>
		template<concepts::numbers T>
		matrix<T> rotation_pitch(double pitch) {
			std::vector<double> v(16);
			v[0] = 1;
			v[5] = std::cos(pitch);
			v[6] = -std::sin(pitch);
			v[9] = std::sin(pitch);
			v[10] = std::cos(pitch);
			v[15] = 1;
			return matrix<T>(4, 4, v);
		}

		/// <summary>
		/// ヨー方向に回転
		/// </summary>
		/// <param name="yaw">角度</param>
		/// <returns>回転行列</returns>
		template<concepts::numbers T>
		matrix<T> rotation_yaw(double yaw) {
			std::vector<double> v(16);
			v[0] = std::cos(yaw);
			v[2] = std::sin(yaw);
			v[5] = 1;
			v[8] = -std::sin(yaw);
			v[10] = std::cos(yaw);
			v[15] = 1;
			return matrix<T>(4, 4, v);
		}

		/// <summary>
		/// 回転座標を返す
		/// </summary>
		/// <param name="roll">ロール角</param>
		/// <param name="pitch">ピッチ角</param>
		/// <param name="yaw">ヨー角</param>
		/// <returns>回転行列</returns>
		template<concepts::numbers T>
		matrix<T> rotation(double roll, double pitch, double yaw) {
			return rotation_roll<double>(roll) * rotation_yaw<double>(yaw) * rotation_pitch<double>(pitch);
		}

		/// <summary>
		/// 拡大縮小行列を返す
		/// </summary>
		/// <param name="x">x方向の拡大率</param>
		/// <param name="y">y方向の拡大率</param>
		/// <param name="z">z方向の拡大率</param>
		/// <returns>拡大縮小行列</returns>
		template<concepts::numbers T>
		matrix<T> scalling(T x, T y, T z) {
			return matrix<T>(4, 4, {
				x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, 1
				});
		}

		/// <summary>
		/// 平行移動行列を返す
		/// </summary>
		/// <param name="x">x方向の移動量</param>
		/// <param name="y">y方向の移動量</param>
		/// <param name="z">z方向の移動量</param>
		/// <returns>平行移動行列</returns>
		template<concepts::numbers T>
		matrix<T> translation(T x, T y, T z) {
			return matrix<T>(4, 4, {
					1, 0, 0, x,
					0, 1, 0, y,
					0, 0, 1, z,
					0, 0, 0, 1
				});
		}
		
		/// <summary>
		/// 剪断行列を返す
		/// </summary>
		/// <param name="Hxy">xy平面でのx方向への係数</param>
		/// <param name="Hyx">xy平面でのy方向への係数</param>
		/// <param name="Hxz">xz平面でのx方向への係数</param>
		/// <param name="Hzx">xz平面でのz方向への係数</param>
		/// <param name="Hyz">yz平面でのy方向への係数</param>
		/// <param name="Hzy">yz平面でのz方向への係数</param>
		/// <returns></returns>
		template<concepts::numbers T>
		matrix<T> shear(T Hxy, T Hyx, T Hxz, T Hzx, T Hyz, T Hzy) {
			return matrix<T>(4, 4, {
					1, Hyx, Hzx, 0,
					Hxy, 1, Hzy, 0,
					Hxz, Hyz, 1, 0,
					0, 0, 0, 1
				});
		}

		/// <summary>
		/// アフィン変換
		/// </summary>
		/// <param name="origine">回転の原点</param>
		/// <param name="transition">平行移動量</param>
		/// <param name="rot">軸回りの回転量</param>
		/// <param name="scale">拡大率</param>
		/// <returns>アフィン変換行列</returns>
		template< concepts::numbers T>
		matrix<T> affine_transformation(const vector3<T>& origine, const vector3<T>& transition, const vector3<T>& rot, const vector3<T>& scale) {
			double sp = std::sin(rot.x), sy = std::sin(rot.y), sr = std::sin(rot.z);
			double cp = std::cos(rot.x), cy = std::cos(rot.y), cr = std::cos(rot.z);
			matrix<T> ret(4,4,0);
			ret.at(0, 0) = (T)(scale.x * (cy * cr));
			ret.at(0,1)=(T)(scale.y* (sp * sy * cr - cp * sr));
			ret.at(0,2)=(T)(scale.z* (cp * sy * cr + sp * sr));
			ret.at(0,3)=(T)(-scale.z*origine.z*(cp*cr*sy+sp*sr)-scale.y*origine.y*(sp*cr*sy-cp*sr)-scale.x*origine.x*cr*cy+transition.x);
		
			ret.at(1,0)=(T)(scale.x* (cy * sr));
			ret.at(1,1)=(T)(scale.y* (sp * sy * sr + cp * cr));
			ret.at(1,2)=(T)(scale.z* (cp * sy * sr - sp * cr));
			ret.at(1,3)=(T)(-scale.z*origine.z*(cp*sr*sy-sp*cr)-scale.y*origine.y*(sp*sr*sy+cp*cr)-scale.x*origine.x*sr*cy+transition.y);

			ret.at(2,0)=(T)(-scale.x* sy);
			ret.at(2,1)=(T)(scale.y* (sp * cy));
			ret.at(2,2)=(T)(scale.z* (cp * cy));
			ret.at(2,3)=(T)(scale.z*origine.z*(cp*cy)-scale.y*origine.y*(sp*cy)-scale.x*origine.x*sy+transition.z);

			ret.at(3,0)=(T)(0);
			ret.at(3,1)=(T)(0);
			ret.at(3,2)=(T)(0);
			ret.at(3,3)=(T)(1);
		
			return ret;
		}
	}
}