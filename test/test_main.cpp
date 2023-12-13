#include "suika.h"
using namespace suika;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}

int main() {
	{
		auto path = filesystem::current_path();
		auto files = filesystem::enumerate_files(path);
		for (auto& file : files) {
			suika::log.info(file.to_u32string());
		}

		auto writer = filesystem::text_writer(U"write_test.txt");
		writer.writeln(U"Hello, world!");
	}
	while (sys::update()) {
		
	}
}
