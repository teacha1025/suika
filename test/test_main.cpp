#include "suika.h"
using namespace suika;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}

int main() {
	{
		auto writer = filesystem::text_writer(U"write_test.txt", filesystem::encode::utf8);
		writer.writeln(U"Hello, world!");
		writer.writeln(U"こんにちは、世界！");
		writer.writeln(U"안녕하세요, 세계!");
		writer.writeln(U"你好，世界！");
		writer.writeln(U"Привет, мир!");
		writer.writeln(U"مرحبا بالعالم!");
		writer.writeln(U"สวัสดีชาวโลก!");
		writer.writeln(U"नमस्ते दुनिया!");
	}
	{
		auto reader = filesystem::text_reader(U"write_test.txt", filesystem::encode::utf8);
		auto lines = reader.readln();
		for (auto& line : lines) {
			suika::log.info(line);
		}
	}
	while (sys::update()) {
		
	}
}
