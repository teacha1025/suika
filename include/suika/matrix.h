#pragma once
#include <vector>
#include "def.h"
#include "type.h"
#include "concepts.h"
#include "point.h"

namespace suika {
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
		matrix(){
			resize(1, 1, 0);
		}

		matrix(uint n, T fill = 0) {
			resize(n, n, fill);
		}

		matrix(uint n, uint m, T fill = 0) {
			resize(n, m, fill);
		}

		matrix(const mat& mt) {
			vec = mt;
			n = mt.size();
			m = mt[0].size();
		}

		matrix(uint n, uint m, const std::vector<T>& ary, T fill = 0) {
			if(ary.size()!=n*m){
				throw;
			}
			resize(n, m);
			for (uint y = 0; y < m; y++) {
				for (uint x = 0; x < n; x++) {
					vec[y][x] = ary[y * n + x];
				}
			}
		}

		void resize(uint n, uint m, T fill = 0) {
			this->n = n;
			this->m = m;

			vec.resize(n);
			for (auto& r : vec) {
				r.resize(m);
				std::fill(r.begin(), r.end(), fill);
			}
		}

		const T& at(uint n, uint m) const {
			return vec[n][m];
		}

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

		bool operator == (const matrix& mt) const {
			if (n != mt.n || m != mt.m) {
				return false;
			}
			for (uint y = 0; y < m; y++) {
				for (uint x = 0; x < n; x++) {
					if (vec[y][x] != mt.vec[y][x]) {
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
			for (uint y = 0; y < m; y++) {
				for (uint x = 0; x < n; x++) {
					ret.vec[y][x] = -vec[y][x];
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		matrix operator + (matrix<t> mt) const {
			if (n != mt.n || m != mt.m) {
				throw;
			}
			matrix ret(n, m);
			for (uint y = 0; y < m; y++) {
				for (uint x = 0; x < n; x++) {
					ret.vec[y][x] = vec[y][x] + mt.vec[y][x];
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		matrix operator - (matrix<t> mt) const {
			if (n != mt.n || m != mt.m) {
				throw;
			}
			matrix ret(n, m);
			for (uint y = 0; y < m; y++) {
				for (uint x = 0; x < n; x++) {
					ret.vec[y][x] = vec[y][x] - mt.vec[y][x];
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		matrix operator + (t v) const {
			matrix ret(n, m);
			for (uint y = 0; y < m; y++) {
				for (uint x = 0; x < n; x++) {
					ret.vec[y][x] = vec[y][x] + v;
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		matrix operator - (t v) const {
			matrix ret(n, m);
			for (uint y = 0; y < m; y++) {
				for (uint x = 0; x < n; x++) {
					ret.vec[y][x] = vec[y][x] - v;
				}
			}
			return ret;
		}

		template<concepts::numbers t>
		matrix& operator += (matrix<t> mt) {
			if (n != mt.n || m != mt.m) {
				throw;
			}
			for (uint y = 0; y < m; y++) {
				for (uint x = 0; x < n; x++) {
					vec[y][x] += mt.vec[y][x];
				}
			}
			return *this;
		}

		template<concepts::numbers t>
		matrix& operator -= (matrix<t> mt) {
			if (n != mt.n || m != mt.m) {
				throw;
			}
			for (uint y = 0; y < m; y++) {
				for (uint x = 0; x < n; x++) {
					vec[y][x] += mt.vec[y][x];
				}
			}
			return *this;
		}
	};

	namespace vector {
		/// <summary>
		/// 行列と2次元ベクトルとの積算
		/// </summary>
		/// <param name="m">2列の行列</param>
		/// <param name="v">2次元ベクトル</param>
		/// <returns>m*v</returns>
		/// <remarks>行列の列数は2である必要がある</remarks>
		template<concepts::numbers T>
		vector2<T> mul(matrix<T> m, vector2<T> v) {
			if (m.size().x != 2) {
				throw;
			}
			vector2<T> ret;
			ret.x = m.at(0,0) * v.x + m.at(0,1) * v.y;
			ret.y = m.at(1,0) * v.x + m.at(1,1) * v.y;
			return ret;
		}

		template<concepts::numbers T>
		vector3<T> mul(matrix<T> m, vector3<T> v) {
			if (m.size().x != 3) {
				throw;
			}
			vector3<T> ret;
			ret.x = m.at(0,0) * v.x + m.at(0,1) * v.y + m.at(0,2) * v.z;
			ret.y = m.at(1,0) * v.x + m.at(1,1) * v.y + m.at(1,2) * v.z;
			ret.z = m.at(2,0) * v.x + m.at(2,1) * v.y + m.at(2,2) * v.z;
			return ret;
		}

		template<concepts::numbers T>
		matrix<T> mul(matrix<T> m1, matrix<T> m2) {
			if (m1.size().y != m2.size().x) {
				throw;
			}
			matrix<T> ret(m1.size().y, m2.size().x);
			for (uint y = 0; y < m1.size().y; y++) {
				for (uint x = 0; x < m2.size().x; x++) {
					T sum = 0;
					for (uint i = 0; i < m1.size().x; i++) {
						sum += m1.at(y, i) * m2.at(i, x);
					}
					ret.at(y, x) = sum;
				}
			}
			return ret;
		}

		template<concepts::numbers T>
		vector2<T> to_vector2(matrix<T> mt) {
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

		template<concepts::numbers T>
		vector3<T> to_vector3(matrix<T> mt) {
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
	}
}