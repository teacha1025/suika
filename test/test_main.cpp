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
	suika::circle c(32);
	int cursor = suika::mouse::arrow;
	suika::line l(suika::window::size()/2, {0,0});
	while (suika::sys::update()) {
		i += suika::mouse::wheel();
		i %= 256;
		suika::window::title(std::format("{:4.1f}fps,{}, [{},{}], {}", suika::sys::fps(), i, suika::mouse::position().x, suika::mouse::position().y, cursor));
		for (int y = 0; y < 16; y++) {
			for (int x = 0; x < 16; x++) {
				r.at({x*w, y*h}).colored(suika::color(suika::palette::gray, i)).blended(suika::blend::alpha).draw();
				//tex.centered({ 0, 0 }).at({ x * w + w / 2,y * h + h / 2 }).blended(suika::blend::alpha).rotated(i / 20.0f).draw();
			}
		}
		/*if (suika::keyboard::A.press()) {
			i++;
		}
		if (suika::mouse::Left.press()) {
			i--;
		}*/
		
		if (suika::mouse::Right.press()) {
			suika::mouse::position({ 640,480 });
			//SetCursor(LoadCursor(NULL, IDC_HAND));
		}
		else if (suika::mouse::Left.down()) {
			cursor++;
			cursor %= 17;
		}
		suika::mouse::style((suika::mouse::cursor)cursor);
		c.at(suika::mouse::position()).resolution(24).colored(suika::color(suika::palette::red, i)).blended(suika::blend::alpha).draw();
		l.B(suika::mouse::position()).colored(suika::color(suika::palette::white, i)).blended(suika::blend::alpha).draw(8.0f,false);
		//suika::point<float> a = { l.B() - l.A() };
		//suika::point<float> u = suika::point<float>{ a.y,-a.x };
		//suika::point<float> v = suika::point<float>{ -a.y,a.x };
		//u = suika::vector::set_length(u, 64) + l.A();
		//v = suika::vector::set_length(v, 64) + l.A();
		//suika::line(suika::vector::set_length(u, 64) + l.A(), suika::vector::set_length(v, 64) + l.A()).draw();
		//suika::line(suika::vector::set_length(u, 64) + l.B(), suika::vector::set_length(v, 64) + l.B()).draw();

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