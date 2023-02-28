﻿/**
* @file color.h
* @brief RGB,HSVカラー
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_COLOR
#define _SK_COLOR
#include "range.h"
#include "def.h"
#include "base.h"

namespace suika {
	struct hsv;

	/// <summary>
	/// RGBカラーを扱うクラス
	/// </summary>
	struct color: public detail::ibase {
		/// <summary>
		/// RGBAの要素[0-255]
		/// </summary>
		ubyte r, g, b, a;


		/// <summary>
		/// デフォルトコンストラクタ　デフォルトでは黒色
		/// </summary>
		constexpr color():
			r(0),
			g(0),
			b(0),
			a(255) {}

		/// <summary>
		/// RGBAを指定して色を作成
		/// </summary>
		/// <param name="_r">赤[0-255]</param>
		/// <param name="_g">緑[0-255]</param>
		/// <param name="_b">青[0-255]</param>
		/// <param name="_a">α値[0-255]</param>
		constexpr color(const ubyte _r, const ubyte _g, const ubyte _b, const ubyte _a = 255):
			r(_r),
			g(_g),
			b(_b),
			a(_a) {}

		/// <summary>
		/// ほかの色から作成
		/// </summary>
		/// <param name="color">ほかの色</param>
		/// <param name="_a">α値[0-255]</param>
		constexpr color(const color& color, ubyte _a):
			r(color.r),
			g(color.g),
			b(color.b),
			a(_a) {}

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
		virtual string to_string() const override;

		/// <summary>
		/// 色が同じであるか
		/// </summary>
		/// <param name="c">比較する色</param>
		/// <returns>等しいか</returns>
		constexpr bool operator==(const color& c) const {
			return r == c.r && b == c.b && g == c.g && a == c.a;
		}
	};

	/// <summary>
	/// HSVカラーを扱う
	/// </summary>
	struct hsv: public detail::ibase {
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
		constexpr hsv():
			h(0),
			s(0),
			v(0),
			a(255) {};

		/// <summary>
		/// HSVAを指定して色を作成
		/// </summary>
		/// <param name="h">色相[0-360]</param>
		/// <param name="s">彩度[0.0-1.0]</param>
		/// <param name="v">明度[0.0-1.0]</param>
		/// <param name="a">α値[0-255]</param>
		constexpr hsv(int h, range<0.0, 1.0> s, range<0.0, 1.0> v, ubyte a = 255):
			h(h % 360),
			s(s.get()),
			v(v.get()),
			a(a) {}

		/// <summary>
		/// ほかの色から作成
		/// </summary>
		/// <param name="color">ほかの色</param>
		/// <param name="a">α値[0-255]α値[0-255]</param>
		constexpr hsv(const hsv& color, ubyte a):
			h(color.h),
			s(color.s),
			v(color.v),
			a(a) {}

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
		virtual string to_string() const override;

		/// <summary>
		/// 色が同じであるか
		/// </summary>
		/// <param name="c">比較する色</param>
		/// <returns>等しいか</returns>
		constexpr bool operator==(const hsv& c) const {
			return h == c.h && s == c.s && v == c.v && a == c.a;
		}
	};
} // namespace suika
#endif