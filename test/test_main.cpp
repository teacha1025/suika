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
	r2.centered({ 8,8 }).extended(1.4).at({ 512,480 });
	auto c1 = circle(48);
	c1.centered({ 8,8 }).extended(1.5);
	auto c2 = circle(64);
	c2.centered({ -8,8 }).extended(1.5).at({ 320,480 });
	while (sys::update()) {
		r2.rotated(-r);
		c2.rotated(-r).at(float2{ 320,480 } + c2.offset());
		switch (mode) {
			case 0: {
				r1.at(mouse::position()).rotated(r - 0.4);
				if (collision_2d::collision(r1, r2)) {
					r1.colored(palette::red);
				}
				else if (collision_2d::collision(r1, c2)) {
					r1.colored(palette::red);
				}
				else {
					r1.colored(palette::blue);
				}
				break;
			}
			case 1: {
				c1.at(mouse::position()).rotated(r - 0.4);
				if (collision_2d::collision(c1, r2)) {
					//c1.colored(palette::red);
				}
			 if (collision_2d::collision(c1, c2)) {
					c1.colored(palette::red);
				}
				else {
					c1.colored(palette::blue);
				}
			 
				break;
			}
		}
		//r2.draw();
		c2.draw();
		switch (mode) {
			case 0: {
				r1.draw();
				break;
			}
			case 1: {
				c1.draw();
				line(c1.position() - c1.offset(), c2.position() - c2.offset()).colored(palette::green).draw();
				break;
			}
		}
		r += 0.01;
	}
}
