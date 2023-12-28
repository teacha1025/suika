// -----------------------------------------------------------
// 
// line
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

namespace suika {
	/// <summary>
	/// 線分クラス
	/// </summary>
	class line : public detail::ishape<line> {
	protected:
		point<float> _A, _B;
		color_f _color = palette::white;

		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
		virtual std::vector<suika::vertex::vertex_2d> create_vertex_bold(float b);
		virtual std::vector<suika::vertex::vertex_2d> create_vertex_bold_round(float b);
	public:
		line() {
			_shaders = { .vs = SHAPE_VERTEX, .ps = SHAPE_PIXEL };
		}

		/// <summary>
		///　2点から線分作成
		/// </summary>
		/// <param name="A">始点</param>
		/// <param name="B">終点</param>
		line(point<float> A, point<float> B) : _A(A), _B(B) {
			_shaders = { .vs = SHAPE_VERTEX, .ps = SHAPE_PIXEL };
		}

		/// <summary>
		/// 太さ1の線分を描画する
		/// </summary>
		virtual void draw() override;

		/// <summary>
		/// 太さbの線分を描画する
		/// </summary>
		/// <param name="b">太さ</param>
		/// <param name="rounded">角を丸めるか</param>
		virtual void draw(float b, bool rounded = false);

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		virtual line colored(const color_f& color)&& {
			this->_color = color;
			return static_cast<line&&>(std::move(*this));
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		virtual line& colored(const color_f& color)& {
			this->_color = color;
			return static_cast<line&>(*this);
		}

		/// <summary>
		/// 線分の点を設定
		/// </summary>
		/// <param name="A">始点</param>
		virtual line& A(const point<float>& A)& {
			this->_A = A;
			return static_cast<line&>(*this);
		}

		/// <summary>
		/// 線分の点を設定
		/// </summary>
		/// <param name="A">始点</param>
		virtual line A(point<float>&& A)&& {
			this->_A = A;
			return static_cast<line&&>(std::move(*this));
		}

		/// <summary>
		/// 線分の点を設定
		/// </summary>
		/// <param name="B">終点</param>
		virtual line& B(const point<float>& B)& {
			this->_B = B;
			return static_cast<line&>(*this);
		}

		/// <summary>
		/// 線分の点を設定
		/// </summary>
		/// <param name="B">終点</param>
		virtual line B(point<float>&& B)&& {
			this->_B = B;
			return static_cast<line&&>(std::move(*this));
		}

		/// <summary>
		/// 線分の色を取得
		/// </summary>
		/// <returns>線分の色</returns>
		virtual color_f color() const {
			return this->_color;
		}

		/// <summary>
		/// 線分の点を取得
		/// </summary>
		/// <returns>始点</returns>
		virtual point<float> A() const;

		/// <summary>
		/// 線分の点を取得
		/// </summary>
		/// <returns>終点</returns>
		virtual point<float> B() const;
	};
}
