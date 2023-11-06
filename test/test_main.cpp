#include "suika.h"
#include "../suika/d3d/dwrite.h"
#include "../suika/d3d/blend.hpp"
#include "../suika/d3d/texture.hpp"
#include "../suika/d3d/vertex.h"


void init() {
	suika::window::background(suika::pallet::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}

struct f4 {
	float a, b, c, d;
};

int main() {
	auto cid = suika::window::canvas().get()->id;
	suika::d3d::dwrite::init(cid);
	suika::d3d::dwrite::font_data fd;
	fd.Color = suika::pallet::white;
	fd.Color.a = 255;
	fd.fontWeight = DWRITE_FONT_WEIGHT_BOLD;
	fd.fontSize = 64.0f;
	fd.font = "游明朝";
	suika::d3d::dwrite::set(fd, cid);

	auto cb = suika::set_view({ 1280,960 });
	suika::set_cbuffer(sizeof(cb), &cb, 0);
	suika::d3d::blend::blends[suika::blend::alpha].set();

	define w = 32, h = 32;

	auto create_vertex = [](suika::point<float> pos, suika::point<float> size) {
		return std::vector<suika::vertex::vertex_2d> {
			suika::vertex::create_2d(suika::vector2<float>{pos.x, pos.y}, suika::pallet::red, {0,0}),
			suika::vertex::create_2d(suika::vector2<float>{pos.x + size.x, pos.y}, suika::pallet::yellow, {1,0}),
			suika::vertex::create_2d(suika::vector2<float>{pos.x, pos.y + size.y}, suika::pallet::blue, {0,1}),
			suika::vertex::create_2d(suika::vector2<float>{pos.x + size.x, pos.y + size.y}, suika::pallet::green, {1,1}),
		};
	};

	std::vector<suika::vertex::vertex_2d> vertices = create_vertex({ 64,64 }, { w,h });

	int i = 0;

	suika::d3d::texture::texture tex("test.bmp");
#if 1
	suika::set_vs("shape");
	suika::set_ps("shape");
#else
	suika::set_vs("texture");
	suika::set_ps("texture");
#endif

	suika::vector3<float> v[32][32];
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 32; y++) {
			v[x][y] = suika::vector3<float>{ x * w, y * h, 0 };
		}
	}

	suika::rect r({ w - 1,h - 1 });

	while (suika::sys::update()) {
		suika::window::title(std::format("{:4.1f}fps", suika::sys::fps()));
		for (int y = 0; y < 32; y++) {
			for (int x = 0; x < 32; x++) {
				r.at(v[x][y]).colored(suika::pallet::gray).draw();
			}
		}
#if 0
		if (i == 60) {
			fd.Color = suika::pallet::yellow;
			fd.Color.a = 255;
			fd.fontWeight = DWRITE_FONT_WEIGHT_LIGHT;
			fd.fontSize = 32.0f;
			fd.font = "游明朝";
			suika::d3d::dwrite::set(fd, cid);
		}
		if (i ==120) {
			i = 0;
			fd.Color = suika::pallet::white;
			fd.Color.a = 255;
			fd.fontWeight = DWRITE_FONT_WEIGHT_BOLD;
			fd.fontSize = 64.0f;
			fd.font = "ＭＳゴシック";
			suika::d3d::dwrite::set(fd, cid);
		}
		suika::d3d::dwrite::draw(L"TEST☺", { 128,128 }, cid);
		i++;
#endif
		
	}
}