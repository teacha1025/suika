#pragma once
#include "draw.h"
#include "vertex.h"
#include "pallet.h"

namespace suika {
	class rect : public detail::ishape<rect> {
	protected:
		point<float> _size = { 64,64 };
		color _color = pallet::white;

		virtual vertex::vertex_2d affine(const point<int>& uv) {
			point<float> _p = this->_size * uv;
			float4 p(_p.x, _p.y, 0, 0);

			return vertex::vertex_2d{ .position = p, .color = {.r = this->_color.r, .g = this->_color.g, .b = this->_color.b, .a = this->_color.a}, .uv = uv };
		}
		std::vector<suika::vertex::vertex_2d> create_vertex(suika::point<float> size) {
			return {
				vertex::create_2d({0.f,0.f},this->_color,{0,0}),
				vertex::create_2d({size.x,0.f},this->_color,{1,0}),
				vertex::create_2d({0.f,size.y},this->_color,{0,1}),
				vertex::create_2d({size.x,size.y},this->_color,{1,1}),
			};
		}
	public:
		rect(const point<float>& size) : _size(size) {
			_shaders = { .vs = "shape", .ps = "shape" };
		}


		virtual void draw() override;

		virtual rect colored(const color& color)&& {
			this->_color = color;
			return static_cast<rect&&>(std::move(*this));
		}
		virtual rect& colored(const color& color)& {
			this->_color = color;
			return static_cast<rect&>(*this);
		}

		virtual rect resized(const point<float>& size)&& {
			this->_size = size;
			return static_cast<rect&&>(std::move(*this));
		}
		virtual rect& resized(const point<float>& size)& {
			this->_size = size;
			return static_cast<rect&>(*this);
		}
		
	};
}