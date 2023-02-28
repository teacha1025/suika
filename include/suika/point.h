/**
* @file point.h
* @brief ベクトル、極座標
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_POINT
#define _SK_POINT
#include <string>
#include <format>
#include <concepts>
#include "base.h"
#include "def.h"
#include "concepts.h"
#include "math.h"

#define SCAST(T,v) static_cast<T>((v))


/// @brief suika名前空間
namespace suika {
	template<concepts::numbers S, concepts::numbers T>
	class polar2;

	/// @brief 2次元空間の位置ベクトル
	/// @tparam T 数値の型
	template<concepts::numbers T>
	class vector2 final: public detail::ibase {
	public:
		using value_type = T;
		T x = 0, y = 0;

		/// <summary>
		/// ベクトルの成分を文字列として取得
		/// </summary>
		/// <returns>"[x,y]"</returns>
		virtual string to_string() const override {
			return "[" + std::to_string(x) + "," + std::to_string(y) + "]";
		}

		/// <summary>
		/// ゼロベクトル
		/// </summary>
		constexpr vector2() = default;

		/// <summary>
		/// 縦、横の値からベクトルを作成
		/// </summary>
		/// <param name="_x">x方向の値</param>
		/// <param name="_y">y方向の値</param>
		constexpr vector2(T _x, T _y) noexcept:
			x(_x),
			y(_y) {}

		/// <summary>
		/// 異なる数値型からベクトルを作成
		/// </summary>
		/// <param name="_x">x方向の値</param>
		/// <param name="_y">y方向の値</param>
		template<concepts::numbers X, concepts::numbers Y>
		constexpr vector2(X _x, Y _y) noexcept:
			x(SCAST(T, _x)),
			y(SCAST(T, _y)) {}

		/// <summary>
		/// 異なる数値型のベクトルから作成
		/// </summary>
		/// <param name="p">別の位置ベクトル</param>
		template<concepts::numbers t>
		constexpr vector2(const vector2<t>& p) noexcept:
			x(SCAST(T, p.x)),
			y(SCAST(T, p.y)) {}

		constexpr vector2 operator+() const {
			return *this;
		}

		constexpr vector2 operator-() const {
			return { -x, -y };
		}

		constexpr vector2 operator+(const vector2& other) const {
			return { x + other.x, y + other.y };
		}

		constexpr vector2 operator-(const vector2& other) const {
			return { x - other.x, y - other.y };
		}

		constexpr vector2 operator*(const vector2& other) const {
			return { x * other.x, y * other.y };
		}

		constexpr vector2 operator/(const vector2& other) const {
			return { x / other.x, y / other.y };
		}

		constexpr vector2 operator%(const vector2& other) const {
			return { SCAST(T, math::fmod(x, other.x)), SCAST(T, math::fmod(y, other.y)) };
		}

		template<concepts::numbers t>
		constexpr auto operator+(const vector2<t>& other) const -> vector2<decltype(x + other.x)> {
			return { x + other.x, y + other.y };
		}

		template<concepts::numbers t>
		constexpr auto operator-(const vector2<t>& other) const -> vector2<decltype(x - other.x)> {
			return { x - other.x, y - other.y };
		}

		template<concepts::numbers t>
		constexpr auto operator*(const vector2<t>& other) const -> vector2<decltype(x * other.x)> {
			return { x * other.x, y * other.y };
		}

		template<concepts::numbers t>
		constexpr auto operator/(const vector2<t>& other) const -> vector2<decltype(x / other.x)> {
			return { x / other.x, y / other.y };
		}

		template<concepts::numbers t>
		constexpr auto operator%(const vector2<t>& other) const -> vector2<decltype(math::fmod(x, other.x))> {
			return { math::fmod(x, other.x), math::fmod(y, other.y) };
		}

		constexpr vector2& operator+=(const vector2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		constexpr vector2& operator-=(const vector2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		constexpr vector2& operator*=(const vector2& other) {
			x *= other.x;
			y *= other.y;
			return *this;
		}

		constexpr vector2& operator/=(const vector2& other) {
			x /= other.x;
			y /= other.y;
			return *this;
		}

		constexpr vector2& operator%=(const vector2& other) {
			x = SCAST(T, math::fmod(x, other.x));
			y = SCAST(T, math::fmod(y, other.y));
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector2& operator+=(const vector2<t>& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector2& operator-=(const vector2<t>& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector2& operator*=(const vector2<t>& other) {
			x *= other.x;
			y *= other.y;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector2& operator/=(const vector2<t>& other) {
			x /= other.x;
			y /= other.y;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector2& operator%=(const vector2<t>& other) {
			x = math::fmod(x, other.x);
			y = math::fmod(y, other.y);
			return *this;
		}

		template<concepts::numbers t>
		constexpr auto operator+(t s) const -> vector2<decltype(x + s)> {
			return { x + s, y + s };
		}

		template<concepts::numbers t>
		constexpr auto operator-(t s) const -> vector2<decltype(x - s)> {
			return { x - s, y - s };
		}

		template<concepts::numbers t>
		constexpr auto operator*(t s) const -> vector2<decltype(x * s)> {
			return { x * s, y * s };
		}

		template<concepts::numbers t>
		constexpr auto operator/(t s) const -> vector2<decltype(x / s)> {
			return { x / s, y / s };
		}

		template<concepts::numbers t>
		constexpr auto operator%(t s) const -> vector2<decltype(math::fmod(x, s))> {
			return { math::fmod(x, s), math::fmod(y, s) };
		}

		template<concepts::numbers t>
		constexpr vector2& operator+=(t s) {
			x += s;
			y += s;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector2& operator-=(t s) {
			x -= s;
			y -= s;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector2& operator*=(t s) {
			x *= s;
			y *= s;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector2& operator/=(t s) {
			x /= s;
			y /= s;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector2& operator%=(t s) {
			x = math::fmod(x, s);
			y = math::fmod(y, s);
			return *this;
		}

		constexpr vector2& operator++() {
			++x;
			++y;
			return *this;
		}

		constexpr vector2& operator--() {
			--x;
			--y;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector2& operator++() {
			x++;
			y++;
			return *this;
		}


		template<concepts::numbers t>
		constexpr vector2& operator--() {
			x--;
			y--;
			return *this;
		}

		constexpr bool operator==(const vector2& other) const {
			return (x == other.x) && (y == other.y);
		}

		constexpr bool operator!=(const vector2& other) const {
			return (x != other.x) || (y != other.y);
		}

		template<concepts::numbers t>
		constexpr bool operator==(const vector2<t>& other) const {
			return (x == other.x) && (y == other.y);
		}

		template<concepts::numbers t>
		constexpr bool operator!=(const vector2<t>& other) const {
			return (x != other.x) || (y != other.y);
		}

		template<concepts::numbers t>
		constexpr bool operator<(const vector2<t>& a) const {
			return x < a.x && y < a.y;
		}

		template<concepts::numbers t>
		constexpr bool operator>(const vector2<t>& a) const {
			return x > a.x && y > a.y;
		}

		template<concepts::numbers t>
		constexpr bool operator<=(const vector2<t>& a) const {
			return x <= a.x && y <= a.y;
		}

		template<concepts::numbers t>
		constexpr bool operator>=(const vector2<t>& a) const {
			return x >= a.x && y >= a.y;
		}

		/// <summary>
		/// 極座標へ変換
		/// </summary>
		/// <returns>2次元の極座標</returns>
		constexpr polar2<T, double> to_polar() const {
			double theta = 0;
			if (y == 0) {
				theta = x >= 0 ? 0 : PI;
			}
			else if (x == 0) {
				theta = y >= 0 ? PI_HALF : PI * 1.5;
			}
			else {
				theta = math::atan(y / x);
				if (x < 0)
					theta += (y < 0 ? -1 : 1) * PI;
				if (theta < 0)
					theta += 2.0 * PI;
			}

			T r = sqrt(x * x + y * y);
			return polar2<T, double> { r, theta };
		}
	};
	/// @brief 2次元空間の位置ベクトル
	/// @tparam T 数値の型
	template<concepts::numbers T>
	using point = vector2<T>;

	/// @brief 3次元空間の位置ベクトル
	/// @tparam T 数値の型
	template<concepts::numbers T>
	class vector3 final: public detail::ibase {
	public:
		using value_type = T;
		T x = 0, y = 0, z = 0;
		/// <summary>
		/// ベクトルの成分を文字列として取得
		/// </summary>
		/// <returns>"[x,y,z]"</returns>
		virtual string to_string() const override {
			return "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
		}
		/// <summary>
		/// ゼロベクトル
		/// </summary>
		constexpr vector3() = default;
		/// <summary>
		/// 縦、横、奥行の値からベクトルを作成
		/// </summary>
		/// <param name="_x">x方向の値</param>
		/// <param name="_y">y方向の値</param>
		/// <param name="_z">y方向の値</param>
		constexpr vector3(T _x, T _y, T _z) noexcept:
			x(_x),
			y(_y),
			z(_z) {}
		/// <summary>
		/// 異なる数値型からベクトルを作成
		/// </summary>
		/// <param name="_x">x方向の値</param>
		/// <param name="_y">y方向の値</param>
		/// <param name="_z">z方向の値</param>
		template<concepts::numbers X, concepts::numbers Y>
		constexpr vector3(X _x, Y _y, T _z) noexcept:
			x(SCAST(T, _x)),
			y(SCAST(T, _y)),
			z(SCAST(T, _z)) {}
		/// <summary>
		/// 異なる数値型のベクトルから作成
		/// </summary>
		/// <param name="p">別の位置ベクトル</param>
		template<concepts::numbers t>
		constexpr vector3(const vector3<t>& p) noexcept:
			x(SCAST(T, p.x)),
			y(SCAST(T, p.y)),
			z(SCAST(T, p.z)) {}

		constexpr vector3 operator+() const {
			return *this;
		}

		constexpr vector3 operator-() const {
			return { -x, -y, -z };
		}

		constexpr vector3 operator+(const vector3& other) const {
			return { x + other.x, y + other.y, z + other.z };
		}

		constexpr vector3 operator-(const vector3& other) const {
			return { x - other.x, y - other.y, z - other.z };
		}

		constexpr vector3 operator*(const vector3& other) const {
			return { x * other.x, y * other.y, z * other.z };
		}

		constexpr vector3 operator/(const vector3& other) const {
			return { x / other.x, y / other.y, z / other.z };
		}

		constexpr vector3 operator%(const vector3& other) const {
			return { SCAST(T, math::fmod(x, other.x)), SCAST(T, math::fmod(y, other.y)), SCAST(T, math::fmod(z, other.z)) };
		}

		template<concepts::numbers t>
		constexpr auto operator+(const vector3<t>& other) const -> vector3<decltype(x + other.x)> {
			return { x + other.x, y + other.y, z + other.z };
		}

		template<concepts::numbers t>
		constexpr auto operator-(const vector3<t>& other) const -> vector3<decltype(x - other.x)> {
			return { x - other.x, y - other.y, z - other.z };
		}

		template<concepts::numbers t>
		constexpr auto operator*(const vector3<t>& other) const -> vector3<decltype(x * other.x)> {
			return { x * other.x, y * other.y, z * other.z };
		}

		template<concepts::numbers t>
		constexpr auto operator/(const vector3<t>& other) const -> vector3<decltype(x / other.x)> {
			return { x / other.x, y / other.y, z / other.z };
		}

		template<concepts::numbers t>
		constexpr auto operator%(const vector3<t>& other) const -> vector3<decltype(math::fmod(x, other.x))> {
			return { math::fmod(x, other.x), math::fmod(y, other.y), math::fmod(z, other.z) };
		}

		constexpr vector3& operator+=(const vector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		constexpr vector3& operator-=(const vector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		constexpr vector3& operator*=(const vector3& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		constexpr vector3& operator/=(const vector3& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		constexpr vector3& operator%=(const vector3& other) {
			x = fmod(x, other.x);
			y = fmod(y, other.y);
			z = fmod(z, other.z);
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator+=(const vector3<t>& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator-=(const vector3<t>& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator*=(const vector3<t>& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator/=(const vector3<t>& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator%=(const vector3<t>& other) {
			x = fmod(x, other.x);
			y = fmod(y, other.y);
			z = fmod(z, other.z);
			return *this;
		}

		template<concepts::numbers t>
		constexpr auto operator+(t s) const -> vector3<decltype(x + s)> {
			return { x + s, y + s, z + s };
		}

		template<concepts::numbers t>
		constexpr auto operator-(t s) const -> vector3<decltype(x - s)> {
			return { x - s, y - s, z - s };
		}

		template<concepts::numbers t>
		constexpr auto operator*(t s) const -> vector3<decltype(x * s)> {
			return { x * s, y * s, z * s };
		}

		template<concepts::numbers t>
		constexpr auto operator/(t s) const -> vector3<decltype(x / s)> {
			return { x / s, y / s, z / s };
		}

		template<concepts::numbers t>
		constexpr auto operator%(t s) const -> vector3<decltype(math::fmod(x, s))> {
			return { math::fmod(x, s), math::fmod(y, s), math::fmod(z, s) };
		}

		template<concepts::numbers t>
		constexpr vector3& operator+=(t s) {
			x += s;
			y += s;
			z += s;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator-=(t s) {
			x -= s;
			y -= s;
			z -= s;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator*=(t s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator/=(t s) {
			x /= s;
			y /= s;
			z /= s;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator%=(t s) {
			x = fmod(x, s);
			y = fmod(y, s);
			z = fmod(z, s);
			return *this;
		}

		constexpr vector3& operator++() {
			++x;
			++y;
			++z;
			return *this;
		}

		constexpr vector3& operator--() {
			--x;
			--y;
			--z;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator++(t) {
			x++;
			y++;
			z++;
			return *this;
		}

		template<concepts::numbers t>
		constexpr vector3& operator--(t) {
			x--;
			y--;
			z--;
			return *this;
		}

		constexpr bool operator==(const vector3& other) const {
			return (x == other.x) && (y == other.y) && (z == other.z);
		}

		constexpr bool operator!=(const vector3& other) const {
			return (x != other.x) || (y != other.y) || (z == other.z);
		}

		template<concepts::numbers t>
		constexpr bool operator==(const vector3<t>& other) const {
			return (x == other.x) && (y == other.y) && (z == other.z);
		}

		template<concepts::numbers t>
		constexpr bool operator!=(const vector3<t>& other) const {
			return (x != other.x) || (y != other.y || (z != other.z));
		}

		template<concepts::numbers t>
		constexpr bool operator<(const vector3<t>& a) const {
			return x < a.x && y < a.y && z < a.z;
		}

		template<concepts::numbers t>
		constexpr bool operator>(const vector3<t>& a) const {
			return x > a.x && y > a.y && z > a.z;
		}

		template<concepts::numbers t>
		constexpr bool operator<=(const vector3<t>& a) const {
			return x <= a.x && y <= a.y && z <= a.z;
		}

		template<concepts::numbers t>
		constexpr bool operator>=(const vector3<t>& a) const {
			return x >= a.x && y >= a.y && z >= a.z;
		}
	};

	/// <summary>
	/// 2次元空間の極座標
	/// </summary>
	/// <typeparam name="size">半径の数値型</typeparam>
	/// <typeparam name="angle">角度の数値型</typeparam>
	template<concepts::numbers size, concepts::numbers angle = double>
	class polar2 final: public detail::ibase {
	public:
		/// <summary>
		/// 半径
		/// </summary>
		size r;
		/// <summary>
		/// 角度(ラジアン)
		/// </summary>
		angle theta;

		/// <summary>
		/// 大きさ0の極座標
		/// </summary>
		constexpr polar2() = default;

		/// <summary>
		/// 半径、角度から極座標を取得
		/// </summary>
		/// <param name="_r">半径</param>
		/// <param name="_theta">角度</param>
		constexpr polar2(size _r, angle _theta) noexcept:
			r(_r),
			theta(_theta) {};

		/// <summary>
		/// 2次元位置ベクトルから極座標に変換
		/// </summary>
		/// <typeparam name="Size">半径の数値型</typeparam>
		/// <typeparam name="Angle">角度の数値型</typeparam>
		/// <param name="p">位置ベクトル</param>
		template<concepts::numbers Size, concepts::numbers Angle>
		constexpr polar2(const vector2<size>& p) {
			*this = p.to_polar();
		}

		/// <summary>
		/// 極座標の成分を文字列として取得
		/// </summary>
		/// <returns>[r,θ]</returns>
		virtual string to_string() const override {
			return std::format("[{}, {}]", r, theta);
		}

		constexpr polar2 operator+() const {
			return *this;
		}
		constexpr polar2 operator-() const {
			return { r, -theta };
		}

		constexpr polar2 operator+(const polar2& p) {
			return { math::sqrt(r * r + p.r * p.r + 2 * r * p.r * math::cos(theta - p.theta)), math::atan((r * math::sin(theta) + p.r * math::sin(p.theta)) / (r * math::cos(theta) + p.r * math::cos(p.theta))) };
		}
		constexpr polar2 operator-(const polar2& p) {
			return { math::sqrt(r * r + p.r * p.r - 2 * r * p.r * math::cos(theta - p.theta)), math::atan((r * math::sin(theta) - p.r * math::sin(p.theta)) / (r * math::cos(theta) - p.r * math::cos(p.theta))) };
		}
		constexpr polar2 operator*(const polar2& p) {
			return { r * p.r, theta + p.theta };
		}
		constexpr polar2 operator/(const polar2& p) {
			return { r / p.r, theta - p.theta };
		}

		constexpr polar2 operator+(size a) const {
			return { math::sqrt(r * r + a * a + 2 * r * a * math::cos(theta)), math::atan((r * math::sin(theta)) / (r * math::cos(theta) + a)) };
		}
		constexpr polar2 operator-(size a) const {
			return { math::sqrt(r * r + a * a - 2 * r * a * math::cos(theta)), math::atan((r * math::sin(theta)) / (r * math::cos(theta) - a)) };
		}
		constexpr polar2 operator*(size a) const {
			return { r * a, theta };
		}
		constexpr polar2 operator/(size a) const {
			return { r / a, theta };
		}

		constexpr polar2& operator+=(const polar2& p) {
			r     = math::sqrt(r * r + p.r * p.r + 2 * r * p.r * math::cos(theta - p.theta));
			theta = math::atan((r * math::sin(theta) + p.r * math::sin(p.theta)) / (r * math::cos(theta) + p.r * math::cos(p.theta)));
			return *this;
		}
		constexpr polar2& operator-=(const polar2& p) {
			r     = math::sqrt(r * r + p.r * p.r - 2 * r * p.r * math::cos(theta - p.theta));
			theta = math::atan((r * math::sin(theta) - p.r * math::sin(p.theta)) / (r * math::cos(theta) - p.r * math::cos(p.theta)));
			return *this;
		}
		constexpr polar2& operator*=(const polar2& p) {
			r *= p.r;
			theta += p.theta;
			return *this;
		}
		constexpr polar2& operator/=(const polar2& p) {
			r /= p.r;
			theta -= p.theta;
			return *this;
		}

		constexpr polar2& operator+=(size a) const {
			r     = math::sqrt(r * r + a * a + 2 * r * a * math::cos(theta));
			theta = math::atan((r * math::sin(theta)) / (r * math::cos(theta) + a));
			return *this;
		}
		constexpr polar2& operator-=(size a) const {
			r     = math::sqrt(r * r + a * a - 2 * r * a * math::cos(theta));
			theta = math::atan((r * math::sin(theta)) / (r * math::cos(theta) - a));
			return *this;
		}
		constexpr polar2& operator*=(size a) const {
			r *= a;
			return *this;
		}
		constexpr polar2& operator/=(size a) const {
			r /= a;
			return *this;
		}



		template<concepts::numbers t>
		constexpr auto operator+(const polar2<t>& p) const -> polar2<decltype(math::sqrt(r * p.r)), decltype(r * math::sin(theta) - p.r * math::sin(p.theta))> {
			return { math::sqrt(r * r + p.r * p.r + 2 * r * p.r * math::cos(theta - p.theta)), math::atan((r * math::sin(theta) + p.r * math::sin(p.theta)) / (r * math::cos(theta) + p.r * math::cos(p.theta))) };
		}

		template<concepts::numbers t>
		constexpr auto operator-(const polar2<t>& p) const -> polar2<decltype(math::sqrt(r * p.r)), decltype(r * math::sin(theta) - p.r * math::sin(p.theta))> {
			return { math::sqrt(r * r + p.r * p.r - 2 * r * p.r * math::cos(theta - p.theta)), math::atan((r * math::sin(theta) - p.r * math::sin(p.theta)) / (r * math::cos(theta) - p.r * math::cos(p.theta))) };
		}

		template<concepts::numbers t>
		constexpr auto operator*(const polar2<t>& p) const -> polar2<decltype(r * p.r), decltype(theta + p.theta)> {
			return { r * p.r, theta + p.theta };
		}

		template<concepts::numbers t>
		constexpr auto operator/(const polar2<t>& p) const -> polar2<decltype(r / p.r), decltype(theta - p.theta)> {
			return { r / p.r, theta - p.theta };
		}
		template<concepts::numbers t>
		constexpr polar2& operator+=(const polar2<t>& p) {
			r     = math::sqrt(r * r + p.r * p.r + 2 * r * p.r * math::cos(theta - p.theta));
			theta = math::atan((r * math::sin(theta) + p.r * math::sin(p.theta)) / (r * math::cos(theta) + p.r * math::cos(p.theta)));
			return *this;
		}
		template<concepts::numbers t>
		constexpr polar2& operator-=(const polar2<t>& p) {
			r     = math::sqrt(r * r + p.r * p.r - 2 * r * p.r * math::cos(theta - p.theta));
			theta = math::atan((r * math::sin(theta) - p.r * math::sin(p.theta)) / (r * math::cos(theta) - p.r * math::cos(p.theta)));
			return *this;
		}
		template<concepts::numbers t>
		constexpr polar2& operator*=(const polar2<t>& p) {
			r *= p.r;
			theta += p.theta;
			return *this;
		}
		template<concepts::numbers t>
		constexpr polar2& operator/=(const polar2<t>& p) {
			r /= p.r;
			theta -= p.theta;
			return *this;
		}
		template<concepts::numbers t>
		constexpr auto operator+(t a) const -> polar2<decltype(math::sqrt(r * a)), decltype(r * math::cos(theta) + a)> {
			return { math::sqrt(r * r + a * a + 2 * r * a * math::cos(theta)), math::atan((r * math::sin(theta)) / (r * math::cos(theta) + a)) };
		}
		template<concepts::numbers t>
		constexpr auto operator-(t a) const -> polar2<decltype(math::sqrt(r * a)), decltype(r * math::cos(theta) - a)> {
			return { math::sqrt(r * r + a * a - 2 * r * a * math::cos(theta)), math::atan((r * math::sin(theta)) / (r * math::cos(theta) - a)) };
		}
		template<concepts::numbers t>
		constexpr auto operator*(t a) -> polar2<decltype(r * a), angle> const {
			return { r * a, theta };
		}
		template<concepts::numbers t>
		constexpr auto operator/(t a) -> polar2<decltype(r / a), angle> const {
			return { r / a, theta };
		}
		template<concepts::numbers t>
		constexpr polar2& operator+=(t a) const {
			r     = math::sqrt(r * r + a * a + 2 * r * a * math::cos(theta));
			theta = math::atan((r * math::sin(theta)) / (r * math::cos(theta) + a));
			return *this;
		}
		template<concepts::numbers t>
		constexpr polar2& operator-=(t a) const {
			r     = math::sqrt(r * r + a * a - 2 * r * a * math::cos(theta));
			theta = math::atan((r * math::sin(theta)) / (r * math::cos(theta) - a));
			return *this;
		}
		template<concepts::numbers t>
		constexpr polar2& operator*=(t a) const {
			r *= a;
			return *this;
		}
		template<concepts::numbers t>
		constexpr polar2& operator/=(t a) const {
			r /= a;
			return *this;
		}

		/// <summary>
		/// 位置ベクトルに変換
		/// </summary>
		/// <returns>変換された位置ベクトル</returns>
		constexpr vector2<size> to_vector() const {
			return { r * cos(theta), r * sin(theta) };
		}
	};
} // namespace suika

template<suika::concepts::numbers T>
struct std::formatter<suika::vector2<T>>: std::formatter<suika::string::string_type> {
	auto format(suika::vector2<T> v, std::format_context& ctx) const {
		return std::formatter<suika::string::string_type>::format(v.to_string().to_string(), ctx);
	}
};

template<suika::concepts::numbers T>
struct std::formatter<suika::vector3<T>>: std::formatter<suika::string::string_type> {
	auto format(suika::vector3<T> v, std::format_context& ctx) const {
		return std::formatter<suika::string::string_type>::format(v.to_string().to_string(), ctx);
	}
};

template<suika::concepts::numbers T>
struct std::formatter<suika::polar2<T>>: std::formatter<suika::string::string_type> {
	auto format(suika::polar2<T> v, std::format_context& ctx) const {
		return std::formatter<suika::string::string_type>::format(v.to_string().to_string(), ctx);
	}
};
#undef SCAST
#endif