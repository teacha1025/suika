#pragma once
#include "palette.h"
#include "def.h"
#include "blend.h"
#include "base.h"
#include "rect.h"

namespace suika {
	enum class font_alignment {
		leading = 0,
		trailing = 1,
		center = 2,
		justified = 3
	};

	enum class font_stretch {
		undefined = 0,
		ultra_condensed = 1,
		extra_condensed = 2,
		condensed = 3,
		semi_condensed = 4,
		normal = 5,
		semi_expanded = 6,
		expanded = 7,
		extra_expanded = 8,
		ultra_expanded = 9
	};

	enum class font_style {
		normal = 0,
		oblique = 1,
		italic = 2
	};

	enum class font_weight {
		thin = 100,
		extra_light = 200,
		light = 300,
		semi_light = 350,
		normal = 400,
		semi_bold = 600,
		bold = 700,
		extra_bold = 800,
		black = 900,
		extra_black = 950
	};
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
	public:
		/// <summary>
		/// デフォルトのフォントを作成
		/// </summary>
		font() {
			_color = palette::black;
			_size = 16;
			_alignment = font_alignment::leading;
			_font = "メイリオ";
			_locale = "";
			_stretch = font_stretch::normal;
			_style = font_style::normal;
			_weight = font_weight::normal;
			_text = "";
			_cid = window::canvas()->id;
		}

		/// <summary>
		/// フォントを作成する
		/// </summary>
		/// <param name="font_name">フォント名(e.g.メイリオ)</param>
		/// <param name="size">フォントサイズ</param>
		/// <param name="w">フォントの太さ</param>
		/// <param name="s">フォントの斜体設定</param>
		/// <param name="a">フォントの配置</param>
		/// <param name="st">フォントストレッチ</param>
		font(const string& font_name, float size = 16.0f, font_weight w = font_weight::normal , font_style s = font_style::normal, font_alignment a = font_alignment::leading, font_stretch st = font_stretch::normal) {
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

		virtual font font_name(const string& font_name)&& {
			_font = font_name;
			return static_cast<font&&>(std::move(*this));
		}

		virtual font& font_name(const string& font_name)& {
			_font = font_name;
			return static_cast<font&>(*this);
		}

		virtual font stretch(font_stretch stretch)&& {
			_stretch = stretch;
			return static_cast<font&&>(std::move(*this));
		}


		virtual font& stretch(font_stretch stretch)& {
			_stretch = stretch;
			return static_cast<font&>(*this);
		}

		virtual font style(font_style style)&& {
			_style = style;
			return static_cast<font&&>(std::move(*this));
		}

		virtual font& style(font_style style)& {
			_style = style;
			return static_cast<font&>(*this);
		}

		virtual font weight(font_weight weight)&& {
			_weight = weight;
			return static_cast<font&&>(std::move(*this));
		}

		virtual font& weight(font_weight weight)& {
			_weight = weight;
			return static_cast<font&>(*this);
		}

		virtual font alignment(font_alignment alignment)&& {
			_alignment = alignment;
			return static_cast<font&&>(std::move(*this));
		}

		virtual font& alignment(font_alignment alignment)& {
			_alignment = alignment;
			return static_cast<font&>(*this);
		}


		/// <summary>
		/// 回転量の設定
		/// </summary>
		/// <param name="center">設定する各軸の回転量</param>
		virtual font rotated(const vector3<position_type>& rotation)&& {
			_rotation = rotation;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// 回転量の設定
		/// </summary>
		/// <param name="center">設定する各軸の回転量</param>
		virtual font& rotated(const vector3<position_type>& rotation)& {
			_rotation = rotation;
			return static_cast<font&>(*this);
		}
		/// <summary>
		/// 回転量の設定
		/// </summary>
		/// <param name="center">設定する回転量</param>
		virtual font rotated(const position_type& rotation)&& {
			_rotation.z = rotation;
			return static_cast<font&&>(std::move(*this));
		}
		/// <summary>
		/// 回転量の設定
		/// </summary>
		/// <param name="center">設定する回転量</param>
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