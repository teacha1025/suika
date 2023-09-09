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
	struct matrix4x4 {
	private:
		T vec[4][4];

	public:
		matrix4x4() {
			std::fill(vec[0], vec[4], 0);
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
					ret.at(y, x) = vec[y][x];
				}
			}
			return ret;
		}
	};

	/// <summary>
	/// n�sm��̍s���\���N���X	
	/// </summary>
	/// <typeparam name="T">�s��̐��l�^</typeparam>
	template<concepts::numbers T = float>
	struct matrix {
	private:
		using row = std::vector<T>;
		using col = row;
		using mat = std::vector<row>;

		mat vec;

		//n�s,m��
		uint n = 1, m = 1;
	public:
		/// <summary>
		/// 1x1�̍s��𐶐�����
		/// </summary>
		matrix() {
			resize(1, 1, 0);
		}

		/// <summary>
		/// nxn�̍s��𐶐�����
		/// </summary>
		/// <param name="n">�s����ї�</param>
		/// <param name="fill">�������l</param>
		matrix(uint n, T fill = 0) {
			resize(n, n, fill);
		}

		/// <summary>
		/// nxm�̍s��𐶐�����
		/// </summary>
		/// <param name="n">�s��</param>
		/// <param name="m">��</param>
		/// <param name="fill">�������l</param>
		matrix(uint n, uint m, T fill = 0) {
			resize(n, m, fill);
		}

		/// <summary>
		/// 2�����z�񂩂�s��𐶐�����
		/// </summary>
		/// <param name="mt">2�����z��</param>
		matrix(const mat& mt) {
			vec = mt;
			n = mt.size();
			m = mt[0].size();
		}

		/// <summary>
		/// nxm�̍s���z�񂩂琶������
		/// </summary>
		/// <param name="n">�s��</param>
		/// <param name="m">��</param>
		/// <param name="ary">�z��</param>
		/// <param name="fill">�������l</param>
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
		/// �s���nxm�̍s��ɏ���������
		/// </summary>
		/// <param name="n">�s��</param>
		/// <param name="m">��</param>
		/// <param name="fill">�������l</param>
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
		/// n,m�̒l���擾����
		/// </summary>
		/// <param name="n">�s�ԍ�</param>
		/// <param name="m">��ԍ�</param>
		/// <returns>n,m�̒l</returns>
		const T& at(uint n, uint m) const {
			return vec[n][m];
		}

		/// <summary>
		/// n,m�̎Q�Ƃ��擾����
		/// </summary>
		/// <param name="n">�s�ԍ�</param>
		/// <param name="m">��ԍ�</param>
		/// <returns>n,m�̎Q��</returns>
		T& at(uint n, uint m) {
			return vec[n][m];
		}

		/// <summary>
		/// n�sm��̍s��̍s�����擾����
		/// </summary>
		/// <returns>{m,n}</returns>
		point<uint> size() const {
			return { m,n };
		}

		/// <summary>
		/// �C�ӂ̐��l�^�̍s��ɃL���X�g����
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

	namespace vector {
		/// <summary>
		/// �s���2�����x�N�g���Ƃ̐ώZ
		/// </summary>
		/// <param name="m">2��̍s��</param>
		/// <param name="v">2�����x�N�g��</param>
		/// <returns>m*v</returns>
		/// <remarks>�s��̗񐔂�2�ł���K�v������</remarks>
		template<concepts::numbers T, concepts::numbers t>
		vector2<t> mul(const matrix<T>& m, const vector2<t>& v) {
			return m * v;
		}

		/// <summary>
		/// �s���3�����x�N�g���Ƃ̐ώZ
		/// </summary>
		/// <param name="m">3��̍s��</param>
		/// <param name="v">3�����x�N�g��</param>
		/// <returns>m*v</returns>
		/// <remarks>�s��̗񐔂�3�ł���K�v������</remarks>
		template<concepts::numbers T, concepts::numbers t>
		auto mul(const matrix<T>& m, const vector3<t>& v) {
			return m * v;
		}

		/// <summary>
		/// �s�񓯎m�̐ώZ
		/// </summary>
		/// <param name="m1">���Ӓl</param>
		/// <param name="m2">�E�Ӓl</param>
		/// <returns>m1*m2</returns>
		template<concepts::numbers T>
		auto mul(const matrix<T>& m1, const matrix<T>& m2) {
			return m1 * m2;
		}

		/// <summary>
		/// �x�N�g�����s��ɕϊ�����
		/// </summary>
		/// <param name="v">2�����x�N�g��</param>
		/// <returns>1x2�s��</returns>
		template<concepts::numbers T>
		matrix<T> to_matrix(const vector2<T>& v) {
			matrix<T> ret(1, 2);
			ret.at(0, 0) = v.x;
			ret.at(0, 1) = v.y;
			return ret;
		}

		/// <summary>
		/// �x�N�g�����s��ɕϊ�����
		/// </summary>
		/// <param name="v">3�����x�N�g��</param>
		/// <returns>1x3�s��</returns>
		template<concepts::numbers T>
		matrix<T> to_matrix(const vector3<T>& v) {
			matrix<T> ret(1, 3);
			ret.at(0, 0) = v.x;
			ret.at(0, 1) = v.y;
			ret.at(0, 2) = v.z;
			return ret;
		}

		/// <summary>
		/// �s����x�N�g���ɕϊ�����
		/// </summary>
		/// <param name="mt">1x2�܂���2x1�̍s��</param>
		/// <returns>2�����x�N�g��</returns>
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
		/// �s����x�N�g���ɕϊ�����
		/// </summary>
		/// <param name="mt">1x3�܂���3x1�̍s��</param>
		/// <returns>3�����x�N�g��</returns>
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
		/// �s��̓]�u
		/// </summary>
		/// <param name="mt">���̍s��</param>
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
		/// nxn�̑Ίp�s��𐶐�����
		/// </summary>
		/// <param name="n">�s��̑傫��</param>
		/// <param name="fill">�Ίp�����̒l</param>
		/// <returns>nxn�̑Ίp�s��</returns>
		template<concepts::numbers T>
		matrix<T> identity(uint n, T fill = 1) {
			matrix<T> ret(n, n);
			for (uint i = 0; i < n; i++) {
				ret.at(i, i) = fill;
			}
			return ret;
		}

		/// <summary>
		/// �s�񎮂̌v�Z
		/// </summary>
		/// <param name="mt">���͂̍s��</param>
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
		/// �t�s��̌v�Z
		/// </summary>
		/// <param name="mt">���͂̍s��</param>
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

		template<concepts::numbers T>
		matrix<T> rotation(double roll, double pitch, double yaw) {
			double sr = std::sin(roll), cr = std::cos(roll);
			double sp = std::sin(pitch), cp = std::cos(pitch);
			double sy = std::sin(yaw), cy = std::cos(yaw);

			return matrix<double>(4, 4, {
				cy * cp, cy * sp * sr - sy * cr, cy * sp * cr + sy * sr, 0,
				sy * cp, sy * sp * sr + cy * cr, sy * sp * cr - cy * sr, 0,
				-sp, cp * sr, cp * cr, 0,
				0, 0, 0, 1
				});
		}

		template<concepts::numbers T>
		matrix<T> scale(T x, T y, T z) {
			return matrix<T>(4, 4, {
				x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, 1
				});
		}

		template<concepts::numbers T>
		matrix<T> translate(T x, T y, T z) {
			return matrix<T>(4, 4, {
					1, 0, 0, x,
					0, 1, 0, y,
					0, 0, 1, z,
					0, 0, 0, 1
				});
		}
	}
}