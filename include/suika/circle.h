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
	/// ‰~Œ`ƒNƒ‰ƒX
	/// </summary>
	class circle : public detail::ishape<circle> {
	protected:
		float _radius = 64;
		uint16 _resolution = 64;
		color_f _color = palette::white;

		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// ‰~‚Ìì¬
		/// </summary>
		/// <param name="r">‰~‚Ì”¼Œa</param>
		circle(float r) : _radius(r) {
			_shaders = { .vs = SHAPE_VERTEX, .ps = SHAPE_PIXEL };
			_resolution = (uint16)r;
		}

		/// <summary>
		/// ‰~‚ğ•`‰æ‚·‚é
		/// </summary>
		virtual void draw() override;

		/// <summary>
		/// F‚ğİ’è
		/// </summary>
		/// <param name="color">“h‚è‚Â‚Ô‚µ‚ÌF</param>
		virtual circle colored(const color_f& color)&& {
			this->_color = color;
			return static_cast<circle&&>(std::move(*this));
		}

		/// <summary>
		/// F‚ğİ’è
		/// </summary>
		/// <param name="color">“h‚è‚Â‚Ô‚µ‚ÌF</param>
		virtual circle& colored(const color_f& color)& {
			this->_color = color;
			return static_cast<circle&>(*this);
		}

		/// <summary>
		/// ”¼Œa‚ğ•Ï‚¦‚é
		/// </summary>
		/// <param name="r">•ÏXŒã‚Ì”¼Œa</param>
		virtual circle resized(float r)&& {
			this->_radius = r;
			return static_cast<circle&&>(std::move(*this));
		}

		/// <summary>
		/// ”¼Œa‚ğ•Ï‚¦‚é
		/// </summary>
		/// <param name="r">•ÏXŒã‚Ì‘å‚«‚³</param>
		virtual circle& resized(float r)& {
			this->_radius = r;
			return static_cast<circle&>(*this);
		}

		/// <summary>
		/// •`‰æ‚Ì•ª‰ğ”\‚ğİ’è
		/// </summary>
		/// <param name="r">•ªŠ„”</param>
		virtual circle resolution(uint16 r)&& {
			this->_resolution = r;
			return static_cast<circle&&>(std::move(*this));
		}

		/// <summary>
		/// •`‰æ‚Ì•ª‰ğ”\‚ğİ’è
		/// </summary>
		/// <param name="r">•ªŠ„”</param>
		virtual circle& resolution(uint16 r)& {
			this->_resolution = r;
			return static_cast<circle&>(*this);
		}

		/// <summary>
		/// ‰~‚Ì”¼Œa‚ğæ“¾
		/// </summary>
		/// <returns>”¼Œa</returns>
		virtual float radius() const {
			return this->_radius;
		}

		/// <summary>
		/// ‰~‚ÌF‚ğæ“¾
		/// </summary>
		/// <returns>‰~‚ÌF</returns>
		virtual color_f color() const {
			return this->_color;
		}

		virtual point<position_type> offset() const;
		virtual vector3<position_type> offset_xyz() const;

		/// <summary>
		/// •`‰æ‚Ì•ª‰ğ”\‚ğæ“¾
		/// </summary>
		/// <returns>•ª‰ğ”\</returns>
		virtual uint16 resolution() const {
			return this->_resolution;
		}
	};
}