#include "suika.h"
namespace palette = suika::palette;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}


int main() {
	suika::font f("メイリオ");
	//suika::texture t("g1.png");
	suika::animation anm("g1,png", { 7,1 });
	anm.patterned({ 0,1,2,1 }, 6);
	int c = 0, i = 0;
	float r = 0;
	int p[] = { 0,1,2,1 };
	while (suika::sys::update()) {
		//suika::rect(t.size()).centered({ 8,8 }).rotated(r).extended(2).at(suika::window::center()).colored(suika::palette::white).draw();
		anm.centered({8,8}).rotated(r).at(suika::window::center()).extended(2.0).updated(1).draw();
		//suika::circle(4).at(suika::window::center()).colored(suika::palette::red).draw();
		c++;
		if (c == 6) {
			i++;
			i %= 4;
			c = 0;
		}
		r += 0.01;
	}
}
