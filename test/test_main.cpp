#include "suika.h"
#include "../suika/d3d/dwrite.h"
#include "../suika/d3d/blend.hpp"
#include "../suika/d3d/texture.hpp"
#include "../suika/d3d/vertex.h"


void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}


int main() {
	auto cid = suika::window::canvas().get()->id;
	suika::d3d::dwrite::init(cid);
	suika::d3d::dwrite::font_data fd;
	fd.Color = suika::palette::white;
	fd.Color.a = 255;
	fd.fontWeight = DWRITE_FONT_WEIGHT_BOLD;
	fd.fontSize = 64.0f;
	fd.font = "游明朝";
	suika::d3d::dwrite::set(fd, cid);

	suika::texture tex("test.bmp");

	define w = 64, h = 64;
	int i = 0;
	float f = 0;

	//suika::d3d::texture::texture tex("test.bmp");
	suika::rect r({ w - 1,h - 1 });
	int cursor = suika::mouse::arrow;
	while (suika::sys::update()) {
		suika::window::title(std::format("{:4.1f}fps, [{},{}], {}", suika::sys::fps(), suika::mouse::position().x, suika::mouse::position().y, cursor));
		for (int y = 0; y < 16; y++) {
			for (int x = 0; x < 16; x++) {
				r.at({x*w, y*h}).colored(suika::color(suika::palette::gray, i%=256)).blended(suika::blend::alpha).draw();
				//tex.centered({ 0, 0 }).at({ x * w + w / 2,y * h + h / 2 }).blended(suika::blend::alpha).rotated(i / 20.0f).draw();
			}
		}
		/*if (suika::keyboard::A.press()) {
			i++;
		}
		if (suika::mouse::Left.press()) {
			i--;
		}*/
		i += suika::mouse::wheel();
		if (suika::mouse::Right.press()) {
			suika::mouse::position({ 640,480 });
			//SetCursor(LoadCursor(NULL, IDC_HAND));
		}
		else if (suika::mouse::Left.down()) {
			cursor++;
			cursor %= 17;
			
		}
		suika::mouse::style((suika::mouse::cursor)cursor);
		
#if 0
		if (i == 60) {
			fd.Color = suika::palette::yellow;
			fd.Color.a = 255;
			fd.fontWeight = DWRITE_FONT_WEIGHT_LIGHT;
			fd.fontSize = 32.0f;
			fd.font = "游明朝";
			suika::d3d::dwrite::set(fd, cid);
		}
		if (i ==120) {
			i = 0;
			fd.Color = suika::palette::white;
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