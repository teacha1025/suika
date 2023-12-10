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
	while (sys::update()) {
		r2.rotated(-r);
		c2.rotated(-r).at(float2{ 320,480 });
		switch (mode) {
			case 0: {
				auto& x = r1.at(mouse::position()).rotated(r - 0.4);
				if (collision_2d::collision(x, r2)) {
					x.colored(palette::red);
				}
				else if (collision_2d::collision(x, c2)) {
					x.colored(palette::blue);
				}
				else {
					x.colored(palette::white);
				}
				break;
			}
			case 1: {
				auto& x = c1.at(mouse::position()).rotated(r - 0.4);
				if (collision_2d::collision(x, r2)) {
					x.colored(palette::red);
				}
				else if (collision_2d::collision(x, c2)) {
					x.colored(palette::blue);
				}
				else {
					x.colored(palette::white);
				}
				break;
			}
		}
		r2.draw();
		c2.draw();
		switch (mode) {
			case 0: {
				r1.draw();
				break;
			}
			case 1: {
				c1.draw();
				line(c1.position() - c1.offset(), c2.position() - c2.offset()).colored(palette::green).draw();
				line(c1.position() - c1.offset(), c1.position()).colored(palette::red).draw();
				break;
			}
		}
		r += 0.01;
	}
}
