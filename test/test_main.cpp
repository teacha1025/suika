#include "suika.h"
#include <queue>
#include <regex>
#include <fstream>
using namespace suika;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}

int main() {
	uint mode = 1;
	float r = 0;
	auto r1 = rect({ 64,32 });
	r1.centered({ 8,8 }).extended(1.4);
	auto r2 = rect({ 120,96 });
	r2.centered({ 8,8 }).extended(1.4).at({ 640,640 });
	auto c1 = circle(48);
	c1.centered({ 16,16 }).extended(1.4);
	auto c2 = circle(64);
	c2.centered({ -16,16 }).extended(1.8).at({ 320,480 });
	auto l1 = line({ 0,0 }, { 64,80 });
	l1.centered({ 32,40 }).extended(1.4);
	auto l2 = line({ 0,0 }, { 64,80 });
	l2.centered({ 32,40 }).extended(1.5).at({ 720,80 });
	range<0.1, 5.0> s = 1.0;
	while (sys::update()) {
		window::title(std::format("{}, {:1.3f}, [{:2.2f}]", mouse::position(), s.get(), sys::fps()));
		if (mouse::Left.down()) {
			mode = (mode + 1) % 3;
		}
		s += mouse::wheel() * 0.01;
		r2.rotated(-r).extended(s);
		c2.rotated(-r).extended(s);
		l2.rotated(-r).extended(s);
		switch (mode) {
			case 0: {
				auto& x = r1.at(mouse::position()).extended(s).rotated(r - 0.4);
				if (collision_2d::collision(x, r2)) {
					x.colored(palette::red);
				}
				else if (collision_2d::collision(x, c2)) {
					x.colored(palette::blue);
				}
				else if (collision_2d::collision(x, l2)) {
					x.colored(palette::green);
				}
				else {
					x.colored(palette::white);
				}
				break;
			}
			case 1: {
				auto& x = c1.at(mouse::position()).extended(s).rotated(r - 0.4);
				if (collision_2d::collision(x, r2)) {
					x.colored(palette::red);
				}
				else if (collision_2d::collision(x, c2)) {
					x.colored(palette::blue);
				}
				else if (collision_2d::collision(x, l2)) {
					x.colored(palette::green);
				}
				else {
					x.colored(palette::white);
				}
				break;
			}
			case 2: {
				auto& x = l1.at(mouse::position()).extended(s).rotated(r - 0.4);
				if (collision_2d::collision(x, r2)) {
					x.colored(palette::red);
				}
				else if (collision_2d::collision(x, c2)) {
					x.colored(palette::blue);
				}
				else if (collision_2d::collision(x, l2)) {
					x.colored(palette::green);
				}
				else {
					x.colored(palette::white);
				}
				break;
			}
		}
		r2.draw();
		c2.draw();
		l2.draw();
		
		switch (mode) {
			case 0: {
				r1.draw();
				break;
			}
			case 1: {
				c1.draw();
				break;
			}
			case 2: {
				l1.draw();
				break;
			}
		}
		r += 0.01;
	}
}
