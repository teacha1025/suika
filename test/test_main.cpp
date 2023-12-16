#include "suika.h"
using namespace suika;

void init() {
	suika::log.set(true, "log.log");
	suika::window::background(suika::palette::yellowgreen);
	suika::window::title("APP");
	suika::window::vsync(true);
}

struct save_data {
	int HP = 200;         //HP
	int MP = 52;         //MP
	int Money = 1500;      //所持金
	int Exp = 80;        //経験値
};
auto s = sizeof(save_data);
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
	{
		auto writer = filesystem::binary_writer(U"write_test.bin");
		save_data data1, data2;
		data2.HP = 200;
		writer.write(data1);
		writer.write(data2);
	}
	{
		auto reader = filesystem::binary_reader(U"write_test.bin");
		auto data = reader.read<save_data>();
		suika::log.info("1");
		suika::log.info(std::format("HP:{}", data.HP));
		suika::log.info(std::format("MP:{}", data.MP));
		suika::log.info(std::format("Money:{}", data.Money));
		suika::log.info(std::format("Exp:{}", data.Exp));

		data = reader.read<save_data>();
		suika::log.info("2");
		suika::log.info(std::format("HP:{}", data.HP));
		suika::log.info(std::format("MP:{}", data.MP));
		suika::log.info(std::format("Money:{}", data.Money));
		suika::log.info(std::format("Exp:{}", data.Exp));

	}
	while (sys::update()) {
		
	}
}
