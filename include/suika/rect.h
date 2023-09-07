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
		virtual void draw() override;
	};
}