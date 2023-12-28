// -----------------------------------------------------------
// 
// rect
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
#include "draw.h"
#include "vertex.h"
#include "palette.h"
#include "shader.h"
#include "line.h"
#include "matrix.h"

namespace suika {
	/// <summary>
	/// 矩形クラス
	/// </summary>
	class rect : public detail::ishape<rect> {
	protected:
		point<float> _size = { 64,64 };
		color_f _color = palette::white;

		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;

		float3 _ext_cnt = { 1,1,1 };
	public:
		rect() { 
			_shaders = { .vs = SHAPE_VERTEX, .ps = SHAPE_PIXEL };
		}

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
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual rect extended(const vector3<double>& rate)&& override{
			_extend = rate;
			_ext_cnt = float3{ 1/(float(_extend.x)), 1/(float(_extend.y)), 1/(float(_extend.z)) };
			return static_cast<rect&&>(std::move(*this));
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual rect& extended(const vector3<double>& rate)& override {
			_extend = rate;
			_ext_cnt = float3{ 1 / (float(_extend.x)), 1 / (float(_extend.y)), 1 / (float(_extend.z)) };
			return static_cast<rect&>(*this);
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual rect extended(const point<double>& rate)&& {
			_extend = { rate.x, rate.y, 1 };
			_ext_cnt = float3{ 1 / (float(_extend.x)), 1 / (float(_extend.y)), 1 / (float(_extend.z)) };
			return static_cast<rect&&>(std::move(*this));
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual rect& extended(const point<double>& rate)& {
			_extend = { rate.x, rate.y, 1 };
			_ext_cnt = float3{ 1 / (float(_extend.x)), 1 / (float(_extend.y)), 1 / (float(_extend.z)) };
			return static_cast<rect&>(*this);
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual rect extended(double rate)&& {
			_extend = { rate, rate, rate };
			_ext_cnt = float3{ 1 / (float(_extend.x)), 1 / (float(_extend.y)), 1 / (float(_extend.z)) };
			return static_cast<rect&&>(std::move(*this));
		}

		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="rate">拡大率</param>
		virtual rect& extended(double rate)& {
			_extend = { rate, rate, rate };
			_ext_cnt = float3{ 1 / (float(_extend.x)), 1 / (float(_extend.y)), 1 / (float(_extend.z)) };
			return static_cast<rect&>(*this);
		}

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
		
		virtual line top() const;
		virtual line right() const;
		virtual line left() const;
		virtual line bottom() const;
	};
}
