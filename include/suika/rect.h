#pragma once
#include "draw.h"
#include "vertex.h"
#include "palette.h"
#include "shader.h"

namespace suika {
	class rect : public detail::ishape<rect> {
	protected:
		point<float> _size = { 64,64 };
		color_f _color = palette::white;

		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// 矩形作成
		/// </summary>
		/// <param name="size">矩形のサイズ</param>
		rect(const point<float>& size) : _size(size) {
			_shaders = { .vs = SHAPE_VERTEX, .ps = SHAPE_PIXEL };
		}

		/// <summary>
		/// 矩形を描画する
		/// </summary>
		virtual void draw() override;

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		virtual rect colored(const color_f& color)&& {
			this->_color = color;
			return static_cast<rect&&>(std::move(*this));
		}
		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		virtual rect& colored(const color_f& color)& {
			this->_color = color;
			return static_cast<rect&>(*this);
		}
		/// <summary>
		/// 矩形の大きさを変える
		/// </summary>
		/// <param name="size">変更後の大きさ</param>
		virtual rect resized(const point<float>& size)&& {
			this->_size = size;
			return static_cast<rect&&>(std::move(*this));
		}
		/// <summary>
		/// 矩形の大きさを変える
		/// </summary>
		/// <param name="size">変更後の大きさ</param>
		virtual rect& resized(const point<float>& size)& {
			this->_size = size;
			return static_cast<rect&>(*this);
		}
		/// <summary>
		/// 矩形のサイズを取得
		/// </summary>
		/// <returns>矩形のサイズ</returns>
		virtual point<float> size() const {
			return this->_size;
		}
		/// <summary>
		/// 矩形の色を取得
		/// </summary>
		/// <returns>矩形の色</returns>
		virtual color_f color() const {
			return this->_color;
		}
		
	};
}