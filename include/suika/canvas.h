#pragma once
#include "color.h"
#include "point.h"

namespace suika {
	struct canvas {
		using canvas_id = uint;
		canvas_id id;
		color bg_color;

		canvas(const point<float>& size, const point<float>& top, HWND hWnd, const color& bg);

		void clear();
		void set();
		void present(bool vsync = false);
	};

	std::shared_ptr<canvas> make_canvas(const point<float>& size, const point<float>& top, HWND hWnd, const color& fillcolor);
}