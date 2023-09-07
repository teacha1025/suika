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

		point<uint> size() const {
			return { n,m };
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
		template<concepts::numbers T>
		vector2<T> mul(matrix<T> m, vector2<T> v) {

		}
	}
}