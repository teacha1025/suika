/*
* fileIO
*	ファイル入出力に関するサンプル
*/

#include "../include/suika.h"
using namespace suika;

//アプリケーションの初期化
void init() {
	//log.logにログを出力する
	suika::log.set(true, "log.log");

	//ウィンドウの設定
	window::background(palette::black);
	window::title("APP");
	window::vsync(true);
}

struct save_data {
	uint hp;
	uint mp;
	float atk;
	uint money;
};

int main() {
	//現在のディレクトリ内のファイルをログに出力
	auto files = filesystem::enumerate_files(filesystem::current_path());
	for (auto& file : files) {
		suika::log.info(file);
	}

	//text.txtにテキストを書き込む
	{
		auto writer = filesystem::text_writer("text.txt", filesystem::encode::utf8, filesystem::new_line::crlf);
		writer.writeln(u8"Hello World!");
		writer.writeln(u8"こんにちは世界！");
		writer.writeln(u8"你好世界！");
	}

	//text.txtのテキストを読み込む
	{
		auto reader = filesystem::text_reader("text.txt", filesystem::encode::utf8, filesystem::new_line::crlf);
		auto text_line = reader.readln();
		for(const auto& line : text_line) {
			suika::log.info(line);
		}
	}

	//save.datにデータを書き込む
	{
		save_data data;
		data.hp = 100;
		data.mp = 50;
		data.atk = 10.5f;
		data.money = 1000;

		auto writer = filesystem::binary_writer("save.dat");
		writer.write(data);
	}

	//save.datのデータを読み込む
	{
		save_data data;
		auto reader = filesystem::binary_reader("save.dat");
		data = reader.read<save_data>();

		suika::log.info(std::format("hp:{}", data.hp));
		suika::log.info(std::format("mp:{}", data.mp));
		suika::log.info(std::format("atk:{}", data.atk));
		suika::log.info(std::format("money:{}", data.money));
	}

	while (sys::update()) {
		
	}

	return 0;
}
