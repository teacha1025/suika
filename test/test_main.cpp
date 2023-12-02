#include "suika.h"
using namespace suika;
//namespace palette = suika::palette;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}

task<void> test_task(font f) {
	for (int i = 0; i < 100; i++) {
		f.text(std::to_string(i)).draw();
		co_yield {};
	}
}

int main() {
	font f("メイリオ");
	f.at({ 0,0 });
	auto t = test_task(f);
	while (sys::update()) {
		t.next();
	}
}
