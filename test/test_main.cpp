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
	suika::animation anm("g1.png", { 7,1 });
	std::vector<suika::uint> A = { 0,1,2,1 };
	std::vector<suika::uint> m = { 3 };
	std::vector<suika::uint> B = { 4,5,6,5 };
	anm.patterned(A, 0.1);
	int state = 0;
	while (suika::sys::update()) {
		if (suika::keyboard::A.down()) {
			anm.patterned(m, 0.1, false);
			state = 1;
		}
		if (suika::keyboard::B.down()) {
			anm.patterned(m, 0.1, false);
			state = 2;
		}
		if (anm.finished()) {
			anm.patterned(state == 1 ? A : B, 0.1, true);
		}
		suika::rect(anm.size()).centered({ 8,8 }).extended(4).at(suika::window::center()).colored(suika::palette::white).draw();
		anm.centered({ 8,8 }).at(suika::window::center()).extended(4.0).updated(suika::sys::delta()).draw();
	}
}
