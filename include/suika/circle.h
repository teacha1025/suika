#pragma once
#pragma once
#include "draw.h"
#include "vertex.h"
#include "palette.h"

namespace suika {
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
		/// <param name="size">‰~‚Ì”¼Œa</param>
		circle(float r) : _radius(r) {
			_shaders = { .vs = SHAPE_VERTEX, .ps = SHAPE_PIXEL };
			_resolution = r;
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
		/// <param name="size">•ÏXŒã‚Ì‘å‚«‚³</param>
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
		/// <summary>
		/// •`‰æ‚Ì•ª‰ğ”\‚ğæ“¾
		/// </summary>
		/// <returns>•ª‰ğ”\</returns>
		virtual uint16 resolution() const {
			return this->_resolution;
		}

	};
}