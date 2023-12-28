// -----------------------------------------------------------
// 
// color.
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

#include "range.h"
#include "def.h"
#include "base.h"

namespace suika {
	struct hsv;
	struct color_f;

	/// <summary>
	/// RGBカラーを扱うクラス
	/// </summary>
	struct color : public detail::ibase {
		/// <summary>
		/// RGBAの要素[0-255]
		/// </summary>
		ubyte r, g, b, a;

		/// <summary>
		/// デフォルトコンストラクタ　デフォルトでは黒色
		/// </summary>
		constexpr color() :
			r(0),
			g(0),
			b(0),
			a(255) {
		}

		/// <summary>
		/// RGBAを指定して色を作成
		/// </summary>
		/// <param name="_r">赤[0-255]</param>
		/// <param name="_g">緑[0-255]</param>
		/// <param name="_b">青[0-255]</param>
		/// <param name="_a">α値[0-255]</param>
		constexpr color(const ubyte _r, const ubyte _g, const ubyte _b, const ubyte _a = 255) :
			r(_r),
			g(_g),
			b(_b),
			a(_a) {
		}

		/// <summary>
		/// ほかの色から作成
		/// </summary>
		/// <param name="color">ほかの色</param>
		/// <param name="_a">α値[0-255]</param>
		constexpr color(const color& color, ubyte _a) :
			r(color.r),
			g(color.g),
			b(color.b),
			a(_a) {
		}

		/// <summary>
		/// 小数表記に変換
		/// </summary>
		color_f to_color_f() const;

		/// <summary>
		/// HSVカラーへの変換
		/// </summary>
		hsv to_hsv() const;

		/// <summary>
		/// 色を変換
		/// </summary>
		/// <returns>数値化された色</returns>
		unsigned int to_int() const;

		/// <summary>
		/// RGBA情報
		/// </summary>
		/// <returns>RGBAの文字列における情報</returns>
		string to_string() const;

		/// <summary>
		/// 色が同じであるか
		/// </summary>
		/// <param name="c">比較する色</param>
		/// <returns>等しいか</returns>
		constexpr bool operator==(const color& c) const {
			return r == c.r && b == c.b && g == c.g && a == c.a;
		}

		/// <summary>
		/// 小数表記に変換
		/// </summary>
		operator color_f() const;
	};


	/// <summary>
	/// RGBカラーを扱うクラス
	/// </summary>
	struct color_f : public detail::ibase {
		/// <summary>
		/// RGBAの要素[0-255]
		/// </summary>
		float r, g, b, a;

		/// <summary>
		/// デフォルトコンストラクタ　デフォルトでは黒色
		/// </summary>
		constexpr color_f() :
			r(0),
			g(0),
			b(0),
			a(1.0) {
		}

		/// <summary>
		/// RGBAを指定して色を作成
		/// </summary>
		/// <param name="_r">赤[0-1.0]</param>
		/// <param name="_g">緑[0-1.0]</param>
		/// <param name="_b">青[0-1.0]</param>
		/// <param name="_a">α値[0-1.0]</param>
		constexpr color_f(const float _r, const float _g, const float _b, const float _a = 255) :
			r(_r),
			g(_g),
			b(_b),
			a(_a) {
		}

		/// <summary>
		/// ほかの色から作成
		/// </summary>
		/// <param name="color">ほかの色</param>
		/// <param name="_a">α値[0-1.0]</param>
		constexpr color_f(const color_f& color, float _a) :
			r(color.r),
			g(color.g),
			b(color.b),
			a(_a) {
		}

		/// <summary>
		/// HSVカラーへの変換
		/// </summary>
		hsv to_hsv() const;

		/// <summary>
		/// 整数表記に変換
		/// </summary>
		color to_color() const;

		/// <summary>
		/// 色を変換
		/// </summary>
		/// <returns>数値化された色</returns>
		unsigned int to_int() const;

		/// <summary>
		/// RGBA情報
		/// </summary>
		/// <returns>RGBAの文字列における情報</returns>
		string to_string() const;

		/// <summary>
		/// 色が同じであるか
		/// </summary>
		/// <param name="c">比較する色</param>
		/// <returns>等しいか</returns>
		constexpr bool operator==(const color_f& c) const {
			return r == c.r && b == c.b && g == c.g && a == c.a;
		}
	};


	/// <summary>
	/// HSVカラーを扱う
	/// </summary>
	struct hsv : public detail::ibase {
		/// <summary>
		/// 色相[0-360]
		/// </summary>
		int h;

		/// <summary>
		/// 彩度[0.0-1.0]
		/// </summary>
		double s;

		/// <summary>
		/// 明度[0.0-1.0]
		/// </summary>
		double v;

		/// <summary>
		/// α値[0-255]
		/// </summary>
		ubyte a;


		/// <summary>
		/// デフォルトコンストラクタ　デフォルトでは黒
		/// </summary>
		constexpr hsv() :
			h(0),
			s(0),
			v(0),
			a(255) {
		};

		/// <summary>
		/// HSVAを指定して色を作成
		/// </summary>
		/// <param name="h">色相[0-360]</param>
		/// <param name="s">彩度[0.0-1.0]</param>
		/// <param name="v">明度[0.0-1.0]</param>
		/// <param name="a">α値[0-255]</param>
		constexpr hsv(int h, range<0.0, 1.0> s, range<0.0, 1.0> v, ubyte a = 255) :
			h(h % 360),
			s(s.get()),
			v(v.get()),
			a(a) {
		}

		/// <summary>
		/// ほかの色から作成
		/// </summary>
		/// <param name="color">ほかの色</param>
		/// <param name="a">α値[0-255]α値[0-255]</param>
		constexpr hsv(const hsv& color, ubyte a) :
			h(color.h),
			s(color.s),
			v(color.v),
			a(a) {
		}

		/// <summary>
		/// RGBカラーへの変換
		/// </summary>
		color to_color() const;

		/// <summary>
		/// 色を変換
		/// </summary>
		/// <returns>数値化された色</returns>
		unsigned int to_int() const;

		/// <summary>
		/// HSVA情報
		/// </summary>
		/// <returns>HSVAの文字列における情報</returns>
		string to_string() const;

		/// <summary>
		/// 色が同じであるか
		/// </summary>
		/// <param name="c">比較する色</param>
		/// <returns>等しいか</returns>
		constexpr bool operator==(const hsv& c) const {
			return h == c.h && s == c.s && v == c.v && a == c.a;
		}
	};
}
