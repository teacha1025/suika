#include "suika.h"
namespace palette = suika::palette;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}


int main() {
	suika::font f("メイリオ");
	suika::texture t("g1.png");
	int c = 0, i = 0;
	int p[] = { 0,1,2,1 };
	while (suika::sys::update()) {
		t.at({ 320,240 }).extended(2.0).uv({(p[i]) / 7.0f,0.0f}, {(p[i] + 1) / 7.0f,1.0f}).draw();
		c++;
		if (c == 6) {
			i++;
			i %= 4;
			c = 0;
		}
	}
}
