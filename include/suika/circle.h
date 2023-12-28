// -----------------------------------------------------------
// 
// circle
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
	/// 円形クラス
	/// </summary>
	class circle : public detail::ishape<circle> {
	protected:
		float _radius = 64;
		uint16 _resolution = 64;
		color_f _color = palette::white;

		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// 円の作成
		/// </summary>
		/// <param name="r">円の半径</param>
		circle(float r) : _radius(r) {
			_shaders = { .vs = SHAPE_VERTEX, .ps = SHAPE_PIXEL };
			_resolution = (uint16)r;
		}

		/// <summary>
		/// 円を描画する
		/// </summary>
		virtual void draw() override;

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		virtual circle colored(const color_f& color)&& {
			this->_color = color;
			return static_cast<circle&&>(std::move(*this));
		}

		/// <summary>
		/// 色を設定
		/// </summary>
		/// <param name="color">塗りつぶしの色</param>
		virtual circle& colored(const color_f& color)& {
			this->_color = color;
			return static_cast<circle&>(*this);
		}

		/// <summary>
		/// 半径を変える
		/// </summary>
		/// <param name="r">変更後の半径</param>
		virtual circle resized(float r)&& {
			this->_radius = r;
			return static_cast<circle&&>(std::move(*this));
		}

		/// <summary>
		/// 半径を変える
		/// </summary>
		/// <param name="r">変更後の大きさ</param>
		virtual circle& resized(float r)& {
			this->_radius = r;
			return static_cast<circle&>(*this);
		}

		/// <summary>
		/// 描画の分解能を設定
		/// </summary>
		/// <param name="r">分割数</param>
		virtual circle resolution(uint16 r)&& {
			this->_resolution = r;
			return static_cast<circle&&>(std::move(*this));
		}

		/// <summary>
		/// 描画の分解能を設定
		/// </summary>
		/// <param name="r">分割数</param>
		virtual circle& resolution(uint16 r)& {
			this->_resolution = r;
			return static_cast<circle&>(*this);
		}

		/// <summary>
		/// 円の半径を取得
		/// </summary>
		/// <returns>半径</returns>
		virtual float radius() const {
			return this->_radius;
		}

		/// <summary>
		/// 円の色を取得
		/// </summary>
		/// <returns>円の色</returns>
		virtual color_f color() const {
			return this->_color;
		}

		virtual point<position_type> offset() const;
		virtual vector3<position_type> offset_xyz() const;

		/// <summary>
		/// 描画の分解能を取得
		/// </summary>
		/// <returns>分解能</returns>
		virtual uint16 resolution() const {
			return this->_resolution;
		}
	};
}
