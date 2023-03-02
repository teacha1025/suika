/**
* @file vector.h
* @brief ベクトル関係
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_VECTOR
#define _SK_VECTOR
#include "math.h"
#include "def.h"
#include "point.h"

namespace suika {
	/// <summary>
	/// ベクトル演算及びベクトル関係の関数群
	/// </summary>
	namespace vector {
		/// <summary>
		/// ベクトルの大きさの二乗を取得
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">ベクトル</param>
		/// <returns>ベクトルの大きさの二乗</returns>
		template<concepts::numbers t>
		constexpr double size_square(const point<t>& p) {
			return p.x * p.x + p.y * p.y;
		}

		/// <summary>
		/// ベクトルの大きさの二乗を取得
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">ベクトル</param>
		/// <returns>ベクトルの大きさの二乗</returns>
		template<concepts::numbers t>
		constexpr double size_square(const vector3<t>& p) {
			return p.x * p.x + p.y * p.y + p.z * p.z;
		}

		/// <summary>
		/// ベクトルの大きさを取得
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">ベクトル</param>
		/// <returns>ベクトルの大きさ</returns>
		template<concepts::numbers t>
		constexpr double size(const point<t>& p) {
			return math::sqrt(size_square(p));
		}

		/// <summary>
		/// ベクトルの大きさを取得
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">ベクトル</param>
		/// <returns>ベクトルの大きさ</returns>
		template<concepts::numbers t>
		constexpr double size(const vector3<t>& p) {
			return math::sqrt(size_square(p));
		}

		/// <summary>
		/// ベクトルを回転させる
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">ベクトル</param>
		/// <param name="angle">回転の角度(rad)</param>
		/// <returns>angleだけ回転したベクトル</returns>
		template<concepts::numbers t>
		constexpr point<double> rotate(const point<t>& p, const double& angle) {
			double x, y;
			x = (p.x * math::cos(angle) - p.y * math::sin(angle));
			y = (p.x * math::sin(angle) + p.y * math::cos(angle));
			return { x, y };
		}

		/// <summary>
		/// ベクトルを回転させる
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">ベクトル</param>
		/// <param name="angle">回転の角度(rad)</param>
		/// <returns>angleだけ回転したベクトル</returns>
		template<concepts::numbers t>
		vector3<double> rotate(const vector3<t>& p, const vector3<double>& angle) {
			VECTOR_D v  = VGetD(p.x, p.y, p.z);
			MATRIX_D mx = MGetRotXD(angle.x);
			MATRIX_D my = MGetRotYD(angle.y);
			MATRIX_D mz = MGetRotZD(angle.z);
			v		   = VTransformD(v, MMultD(MMultD(mz, mx), my));
			return { v.x, v.y, v.z };
		}

		/// <summary>
		/// 回転中心を指定して座標を回転させる
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">座標</param>
		/// <param name="c">回転中心</param>
		/// <param name="angle">回転の角度(rad)</param>
		/// <returns>cを中心にangleだけ回転した座標</returns>
		template<concepts::numbers t>
		constexpr point<double> rotate_at(const point<t>& p, const point<t>& c, const double& angle) {
			return rotate(p - c, angle) + c;
		}

		/// <summary>
		/// 回転中心を指定して座標を回転させる
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">座標</param>
		/// <param name="c">回転中心</param>
		/// <param name="angle">回転の角度(rad)</param>
		/// <returns>cを中心にangleだけ回転した座標</returns>
		template<concepts::numbers t>
		point<double> rotate_at(const vector3<t>& p, const vector3<t>& c, const vector3<double>& angle) {
			return rotate(p - c, angle) + c;
		}

		/// <summary>
		/// ベクトルの大きさを変更
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">元のベクトル</param>
		/// <param name="length">設定する長さ</param>
		/// <returns>長さがlengthになったベクトルp</returns>
		template<concepts::numbers t>
		constexpr point<t> set_length(const point<t>& p, const double& length) {
			if (size(p) == 0) {
				return { 0, 0 };
			}
			auto v = p / size(p);
			return v * length;
		}

		/// <summary>
		/// ベクトルの大きさを変更
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">元のベクトル</param>
		/// <param name="length">設定する長さ</param>
		/// <returns>長さがlengthになったベクトルp</returns>
		template<concepts::numbers t>
		constexpr point<t> set_length(const vector3<t>& p, const double& length) {
			if (size(p) == 0) {
				return { 0, 0 };
			}
			auto v = p / size(p);
			return v * length;
		}

		/// <summary>
		/// ベクトルの外積を取得
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="v1">ベクトル1</param>
		/// <param name="v2">ベクトル2</param>
		/// <returns>v1 × v2</returns>
		template<concepts::numbers t>
		constexpr t cross(const point<t>& v1, const point<t>& v2) {
			return v1.x * v2.y - v1.y * v2.x;
		}

		/// <summary>
		/// ベクトルの外積を取得
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="v1">ベクトル1</param>
		/// <param name="v2">ベクトル2</param>
		/// <returns>v1 × v2</returns>
		template<concepts::numbers t>
		constexpr t cross(const vector3<t>& v1, const vector3<t>& v2) {
			return { v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v2.z * v1.x, v1.x * v2.y - v2.x * v1.y };
		}

		/// <summary>
		/// ベクトルの内積を取得
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="v1">ベクトル1</param>
		/// <param name="v2">ベクトル2</param>
		/// <returns>v1・v2</returns>
		template<concepts::numbers t>
		constexpr t dot(const point<t>& v1, const point<t>& v2) {
			return v1.x * v2.x + v1.y * v2.y;
		}

		/// <summary>
		/// ベクトルの内積を取得
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="v1">ベクトル1</param>
		/// <param name="v2">ベクトル2</param>
		/// <returns>v1・v2</returns>
		template<concepts::numbers t>
		constexpr t dot(const vector3<t>& v1, const vector3<t>& v2) {
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		/// <summary>
		/// ベクトルの角度を取得
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="v">ベクトル</param>
		/// <returns>vの角度</returns>
		template<concepts::numbers t>
		constexpr double angle(const point<t>& v) {
			if (v.x == 0) {
				return v.y >= 0 ? PI_HALF : -PI_HALF;
			}
			if (v.y == 0) {
				return v.x >= 0 ? 0 : PI;
			}
			return math::atan(v.y / v.x);
		}

		/// <summary>
		/// ベクトル同士の角度を取得
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="v1">ベクトル1</param>
		/// <param name="v2">ベクトル2</param>
		/// <returns>v1からv2への角度</returns>
		template<concepts::numbers t>
		constexpr double angle(const point<t>& v1, const point<t>& v2) {
			return angle(v2 - v1);
		}
	} // namespace vector
} // namespace suika
#endif