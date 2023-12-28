/** @example{lineno} font.hpp
 * 文字列描画のサンプル
*/

// -----------------------------------------------------------
// 
// font draw.
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

#include "canvas.h"
#include "palette.h"
#include "def.h"
#include "blend.h"
#include "base.h"
#include "rect.h"

namespace suika {
	/// <summary>
	/// フォントの配置
	/// </summary>
	enum class font_alignment {
		//! 左端揃え
		left = 0,
		//! 右端揃え
		right = 1,
		//! 中央揃え
		center = 2,
		//! 両端揃え
		justified = 3
	};

	/// <summary>
	/// フォントの幅
	/// </summary>
	enum class font_stretch {
		//! 未定義
		undefined = 0,
		//! 超極細
		ultra_condensed = 1,
		//! 極細
		extra_condensed = 2,
		//! 細
		condensed = 3,
		//! 半細
		semi_condensed = 4,
		//! 標準
		normal = 5,
		//! 半太
		semi_expanded = 6,
		//! 太
		expanded = 7,
		//! 極太
		extra_expanded = 8,
		//! 超極太
		ultra_expanded = 9,
	};

	/// <summary>
	/// フォントの斜体
	/// </summary>
	enum class font_style {
		//! 標準
		normal = 0,
		//! 斜体
		oblique = 1,
		//! フォント標準の斜体
		italic = 2
	};

	/// <summary>
	/// フォントの太さ
	/// </summary>
	enum class font_weight {
		//! 超極細
		thin = 100,
		//! 極細
		extra_light = 200,
		//! 細
		light = 300,
		//! 半細
		semi_light = 350,
		//! 標準
		normal = 400,
		//! 半太
		semi_bold = 600,
		//! 太
		bold = 700,
		//! 極太
		extra_bold = 800,
		//! 超極太
		heavy = 900,
		//! 最太
		extra_heavy = 950
	};

	/// <summary>
	/// フォント描画に関するクラス
	/// </summary>
	class font : public detail::ibase {
	public:
		
	private:
		color_f _color;
		string _font;
		float _size;
		font_alignment _alignment;
		string _locale;
		font_stretch _stretch;
		font_style _style;
		font_weight _weight;

		uint32 _edge_width;
		color_f _edge_color;
		bool _edge_enabled;

		using position_type = float;
		//原点からの移動量
		vector3<position_type> _transition;

		//オブジェクトの描画、回転の中心
		vector3<position_type> _center;

		//回転量
		vector3<position_type> _rotation;

		//拡大率
		vector3<double> _extend;

		//ブレンド
		blend _blend;

		string _text;

		void set(canvas::canvas_id id) const;

		canvas::canvas_id _cid;

		string create_key() const;
	public:
		/// <summary>
		/// デフォルトのフォントを作成
		/// </summary>
		font() {
			_color = palette::black;
			_size = 16;
			_alignment = font_alignment::left;
			_font = "メイリオ";
			_locale = "";
			_stretch = font_stretch::normal;
			_style = font_style::normal;
			_weight = font_weight::normal;
			_text = "";
			_cid = window::canvas()->id;
			_blend = blend::none;

			_edge_color = palette::black;
			_edge_width = 0;
			_edge_enabled = false;
		}

		/// <summary>
		/// フォントを作成する
		/// </summary>
		/// <param name="font_name">フォント名(e.g.メイリオ)</param>
		/// <param name="size">フォントサイズ</param>
		/// <param name="edge">フォントのエッジ設定</param>
		/// <param name="edge_width">フォントのエッジ幅(edge==falseなら無視される)</param>
		/// <param name="w">フォントの太さ</param>
		/// <param name="s">フォントの斜体設定</param>
		/// <param name="a">フォントの配置</param>
		/// <param name="st">フォントの幅</param>
		font(const string& font_name, float size = 16.0f, bool edge = false, int32 edge_width =1u, font_weight w = font_weight::normal, font_style s = font_style::normal, font_alignment a = font_alignment::left, font_stretch st = font_stretch::normal) {
			_color = palette::black;
			_size = size;
			_alignment = a;
			_font = font_name;
			_locale = "";
			_stretch = st;
			_style = s;
			_weight = w;
			_text = "";
			_cid = window::canvas()->id;
			_blend = blend::none;

			_edge_color = palette::black;
			_edge_width = edge_width;
			_edge_enabled = edge;

			if (edge) {
				if (edge_width <= 0) {
					_edge_enabled = false;
				}
				else if (edge_width > (_size / 3.0f)) {
					_edge_width = (uint32)(_size / 3.0f);
				}
				else {
					_edge_width = (uint32)edge_width;
				}
			}
		}

		/// <summary>
		/// テキストを描画する
		/// </summary>
		virtual void draw() const;

		/// <summary>
		/// 描画する内容を設定
		/// </summary>
		/// <param name="text">テキスト</param>
		virtual font text(const string& text)&& {
			_text = text;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 描画する内容を設定
		/// </summary>
		/// <param name="text">テキスト</param>
		virtual font& text(const string& text)& {
			_text = text;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 座標を設定
		/// </summary>
		/// <param name="position">設定する座標</param>
		virtual font at(const vector3<position_type>& position)&& {
			_transition = position;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 座標を設定
		/// </summary>
		/// <param name="position">設定する座標</param>
		virtual font& at(const vector3<position_type>& position)& {
			_transition = position;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 座標を設定
		/// </summary>
		/// <param name="position">設定する座標</param>
		virtual font at(const point<position_type>& position)&& {
			_transition = vector3<position_type>{ position.x, position.y, 0.0 };
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 座標を設定
		/// </summary>
		/// <param name="position">設定する座標</param>
		virtual font& at(const point<position_type>& position)& {
			_transition = vector3<position_type>{ position.x, position.y, 0.0 };
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// オブジェクトの中心を設定
		/// </summary>
		/// <param name="center">設定する中心座標</param>
		virtual font centered(const vector3<position_type>& center)&& {
			_center = center;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// オブジェクトの中心を設定
		/// </summary>
		/// <param name="center">設定する中心座標</param>
		virtual font& centered(const vector3<position_type>& center)& {
			_center = center;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// オブジェクトの中心を設定
		/// </summary>
		/// <param name="center">設定する中心座標</param>
		virtual font centered(const point<position_type>& center)&& {
			_center = vector3<position_type>{ center.x, center.y, 0.0 };
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// オブジェクトの中心を設定
		/// </summary>
		/// <param name="center">設定する中心座標</param>
		virtual font& centered(const point<position_type>& center)& {
			_center = vector3<position_type>{ center.x, center.y, 0.0 };
			return dynamic_cast<font&>(*this);
		}

		/// <summary>
		/// フォントの変更
		/// </summary>
		/// <param name="font_name">フォント名</param>
		virtual font font_name(const string& font_name)&& {
			_font = font_name;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// フォントの変更
		/// </summary>
		/// <param name="font_name">フォント名</param>
		virtual font& font_name(const string& font_name)& {
			_font = font_name;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// フォント幅
		/// </summary>
		/// <param name="stretch">幅</param>
		virtual font stretch(font_stretch stretch)&& {
			_stretch = stretch;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// フォント幅
		/// </summary>
		/// <param name="stretch">幅</param>
		virtual font& stretch(font_stretch stretch)& {
			_stretch = stretch;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// フォントのスタイル
		/// </summary>
		/// <param name="style">スタイル</param>
		virtual font style(font_style style)&& {
			_style = style;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// フォントのスタイル
		/// </summary>
		/// <param name="style">スタイル</param>
		virtual font& style(font_style style)& {
			_style = style;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// フォントの太さ
		/// </summary>
		/// <param name="weight">太さ</param>				
		virtual font weight(font_weight weight)&& {
			_weight = weight;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// フォントの太さ
		/// </summary>
		/// <param name="weight">太さ</param>
		virtual font& weight(font_weight weight)& {
			_weight = weight;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// フォントの配置
		/// </summary>
		/// <param name="alignment">配置</param>
		virtual font alignment(font_alignment alignment)&& {
			_alignment = alignment;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// フォントの配置
		/// </summary>
		/// <param name="alignment">配置</param>
		virtual font& alignment(font_alignment alignment)& {
			_alignment = alignment;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 縁取りの設定
		/// </summary>
		/// <param name="enabled">縁取りをするか</param>
		/// <param name="width">縁の太さ</param>
		/// <remarks>widthが0以下の場合は縁取りはされません</remarks>
		/// <remarks>縁の太さがフォントの太さの1/3以下となります。</remarks>
		virtual font edged(bool enabled, int32 width = 0)&& {
			_edge_enabled = enabled;
			if (enabled) {
				if (width <= 0) {
					_edge_enabled = false;
				}
				else if (width > (_size / 3.0f)) {
					_edge_width = (uint32)(_size / 3.0f);
				}
				else {
					_edge_width = (uint32)width;
				}
			}
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 縁取りの設定
		/// </summary>
		/// <param name="enabled">縁取りをするか</param>
		/// <param name="width">縁の太さ</param>
		/// <remarks>widthが0以下の場合は縁取りはされません</remarks>
		/// <remarks>縁の太さがフォントの太さの1/3以下となります。</remarks>
		virtual font& edged(bool enabled, int32 width = 0)& {
			_edge_enabled = enabled;
			if (enabled) {
				if (width <= 0) {
					_edge_enabled = false;
				}
				else if (width > (_size / 3.0f)) {
					_edge_width = (uint32)(_size / 3.0f);
				}
				else {
					_edge_width = (uint32)width;
				}
			}
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 回転量の設定
		/// </summary>
		/// <param name="rotation">設定する各軸の回転量</param>
		virtual font rotated(const vector3<position_type>& rotation)&& {
			_rotation = rotation;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 回転量の設定
		/// </summary>
		/// <param name="rotation">設定する各軸の回転量</param>
		virtual font& rotated(const vector3<position_type>& rotation)& {
			_rotation = rotation;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 回転量の設定
		/// </summary>
		/// <param name="rotation">設定する回転量</param>
		virtual font rotated(const position_type& rotation)&& {
			_rotation.z = rotation;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 回転量の設定
		/// </summary>
		/// <param name="rotation">設定する回転量</param>
		virtual font& rotated(const position_type& rotation)& {
			_rotation.z = rotation;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual font extended(const vector3<double>& rate)&& {
			_extend = rate;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual font& extended(const vector3<double>& rate)& {
			_extend = rate;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual font extended(const point<double>& rate)&& {
			_extend = { rate.x, rate.y, 1 };
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual font& extended(const point<double>& rate)& {
			_extend = { rate.x, rate.y, 1 };
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual font extended(double rate)&& {
			_extend = { rate, rate, rate };
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual font& extended(double rate)& {
			_extend = { rate, rate, rate };
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// ブレンドの設定
		/// </summary>
		/// <param name="type">ブレンドの種類</param>
		virtual font blended(blend type)&& {
			_blend = type;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// ブレンドの設定
		/// </summary>
		/// <param name="type">ブレンドの種類</param>
		virtual font& blended(blend type)& {
			_blend = type;
			return static_cast<font&>(*this);
		}

		//取得系

		/// <summary>
		/// オブジェクトの原点からの移動量を取得
		/// </summary>
		/// <returns>xyz空間の移動量</returns>
		virtual vector3<position_type> position_xyz() const {
			return _transition;
		}

		/// <summary>
		/// オブジェクトの原点からの移動量を取得
		/// </summary>
		/// <returns>xy平面の移動量</returns>
		virtual point<position_type> position() const {
			return point<position_type> {
				static_cast<position_type>(_transition.x),
					static_cast<position_type>(_transition.y)
			};
		}

		/// <summary>
		/// 拡大率の取得
		/// </summary>
		/// <returns>xyz方向の拡大率</returns>
		virtual vector3<position_type> extend_xyz() const {
			return _extend;
		}

		/// <summary>
		/// 拡大率の取得
		/// </summary>
		/// <returns>xy方向への拡大率</returns>
		virtual point<position_type> extend() const {
			return point<position_type> {
				static_cast<position_type>(_extend.x),
					static_cast<position_type>(_extend.y)
			};
		}

		/// <summary>
		/// 回転量の取得
		/// </summary>
		/// <returns>xyz軸の回転量</returns>
		virtual vector3<position_type> rotate_xyz() const {
			return _rotation;
		}

		/// <summary>
		/// 回転量の取得
		/// </summary>
		/// <returns>xy軸の回転量</returns>
		virtual point<position_type> rotate() const {
			return point<position_type> {
				static_cast<position_type>(_rotation.x),
					static_cast<position_type>(_rotation.y)
			};
		}

		/// <summary>
		/// 中心座標の取得
		/// </summary>
		/// <returns>xyz空間の中心座標</returns>
		virtual vector3<position_type> center_xyz() const {
			return _center;
		}

		/// <summary>
		/// 中心座標の取得
		/// </summary>
		/// <returns>xy空間の中心座標</returns>
		virtual point<position_type> center() const {
			return point<position_type> {
				static_cast<position_type>(_center.x),
					static_cast<position_type>(_center.y)
			};
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		virtual font colored(const color_f& color)&& {
			this->_color = color;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		virtual font& colored(const color_f& color)& {
			this->_color = color;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		/// <param name="a">透明度</param>
		virtual font colored(const color_f& color, float a)&& {
			this->_color = color_f(color, a);
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		/// <param name="a">透明度</param>
		virtual font& colored(const color_f& color, float a)& {
			this->_color = color_f(color, a);
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		/// <param name="edge">エッジの色</param>
		virtual font colored(const color_f& color, const color_f& edge)&& {
			this->_color = color;
			this->_edge_color = edge;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		/// <param name="edge">エッジの色</param>
		virtual font& colored(const color_f& color, const color_f& edge)& {
			this->_color = color;
			this->_edge_color = edge;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		/// <param name="edge">エッジの色</param>
		/// <param name="a">透明度</param>
		virtual font colored(const color_f& color, const color_f& edge, float a)&& {
			this->_color = color_f(color, a);
			this->_edge_color = color_f(edge, a);
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		/// <param name="edge">エッジの色</param>
		/// <param name="a">透明度</param>
		virtual font& colored(const color_f& color, const color_f& edge, float a)& {
			this->_color = color_f(color, a);
			this->_edge_color = color_f(edge, a);
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// フォントの大きさを変える
		/// </summary>
		/// <param name="size">変更後の大きさ</param>
		virtual font resized(float size)&& {
			this->_size = size;
			return static_cast<font&&>(std::move(*this));
		}

		/// <summary>
		/// フォントの大きさを変える
		/// </summary>
		/// <param name="size">変更後の大きさ</param>
		virtual font& resized(float size)& {
			this->_size = size;
			return static_cast<font&>(*this);
		}

		/// <summary>
		/// 矩形のサイズを取得
		/// </summary>
		/// <returns>矩形のサイズ</returns>
		virtual suika::rect rect() const;
		/// <summary>
		/// フォントの色を取得
		/// </summary>
		/// <returns>フォントの色</returns>
		
		virtual color_f color() const {
			return this->_color;
		}
	};
} // namespace suika
