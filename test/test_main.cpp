#include "suika.h"
#include "../suika/d3d/dwrite.h"
//#include "../suika/d3d/blend.hpp"
//#include "../suika/d3d/texture.hpp"
//#include "../suika/d3d/vertex.h"


void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}


int main() {
	//auto cid = suika::window::canvas().get()->id;
	//
	//suika::d3d::dwrite::font_data fd;
	//fd.color = suika::palette::white;
	//fd.color.a = 1.0f;
	//fd.weight = DWRITE_FONT_WEIGHT_BOLD;
	//fd.size = 64.0f;
	//fd.font = "游明朝";
	//suika::d3d::dwrite::set(fd, cid);

	suika::font f("メイリオ");

	suika::texture tex("test.bmp");

	define w = 64, h = 64;
	int i = 0, j = 0, edge = 0;
	//float f = 0;

	suika::rect r({ w - 1,h - 1 });
	suika::circle c(32);
	int cursor = suika::mouse::arrow;
	suika::line l(suika::window::size()/2, {0,0});
	while (suika::sys::update()) {
		if (suika::gamepad::pad[0].A.press()) {
			f.text("A").centered({ 0,0 }).at({ 0,0 }).draw();
		}
#if 0
		edge += suika::mouse::wheel();
		i %= 256;
		suika::window::title(std::format("{:4.1f}fps,{}, [{},{}], {}", suika::sys::fps(), edge, suika::mouse::position().x, suika::mouse::position().y, cursor));
		for (int y = 0; y < 16; y++) {
			for (int x = 0; x < 16; x++) {
				r.at({x*w, y*h}).colored(suika::color(suika::palette::gray, (x+y)*8)).blended(suika::blend::alpha).draw();
				//tex.centered({ 0, 0 }).at({ x * w + w / 2,y * h + h / 2 }).blended(suika::blend::alpha).rotated(i / 20.0f).draw();
			}
		}
		
		if (suika::mouse::Right.down()) {
			static bool flag = false;
			//suika::mouse::position({ 640,480 });
			//SetCursor(LoadCursor(NULL, IDC_HAND));

			while (true) {
				if (flag) {
					auto r = ShowCursor(TRUE);
					if (r >= 0)
						break;
				}
				else {
					auto r = ShowCursor(FALSE);
					if (r < 0)
						break;
				}
			}

			flag ^= 1;

			f.edged(flag, 2);
		}
		else if (suika::mouse::Left.down()) {
			cursor++;
			cursor %= 17;
		}
		suika::mouse::style((suika::mouse::cursor)cursor);
		c.at(suika::mouse::position()).resolution(24).colored(suika::color(suika::palette::red, i)).blended(suika::blend::add).draw();
		l.B(suika::mouse::position()).colored(suika::color(suika::palette::white, i)).blended(suika::blend::sub).draw(8.0f,false);
		f.text(L"こんにちは！！").centered({0,0}).at(suika::mouse::position()).resized(64).edged(true,edge).centered(f.rect().size() / 2);
		f.rect().centered(f.rect().size()/2).colored(suika::color(suika::palette::gray, 255)).blended(suika::blend::alpha).draw();
		f.colored(suika::hsv(j, 1.0f,1.0f).to_color(),suika::palette::white).draw();
		j++;
		j %= 360;
#endif
#if 0
		if (i == 60) {
			fd.color = suika::palette::yellow;
			fd.color.a = 1.0f;
			fd.weight = DWRITE_FONT_WEIGHT_LIGHT;
			fd.size = 32.0f;
			fd.font = "游明朝";
			suika::d3d::dwrite::set(fd, cid);
		}
		if (i ==120) {
			i = 0;
			fd.color = suika::palette::white;
			fd.color.a = 1.0f;
			fd.weight = DWRITE_FONT_WEIGHT_BOLD;
			fd.size = 64.0f;
			fd.font = "ＭＳゴシック";
			suika::d3d::dwrite::set(fd, cid);
		}
		suika::d3d::dwrite::draw(L"TEST☺", { 128,128 }, cid);
		i++;
#endif
		
	}
}
