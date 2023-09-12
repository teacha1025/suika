#pragma once
#include "draw.h"
#include "vertex.h"
#include "pallet.h"

namespace suika {
	class rect : public detail::ishape<rect> {
	protected:
		point<float> _size = { 64,64 };
		color _color = pallet::white;
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