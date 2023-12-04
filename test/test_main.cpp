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
	while (sys::update()) {
		
	}
}
