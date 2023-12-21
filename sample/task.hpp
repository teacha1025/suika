/*
* task
*	複数の矩形をタスクを使用して移動させる
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

// 矩形移動のタスク
task<void> task_move(rect& r) {
	point<float> pos = r.position();
	while (true) {
		r.at(pos);
		
		//処理を中断
		co_yield{};

		//矩形を移動
		pos += {1, 1};
	}
}

int main() {
	//128x128の矩形を作成
	rect r1({ 128,128 });
	r1.colored(palette::orange).at({ 0,0 });

	rect r2({ 128,128 });
	r2.colored(palette::greenyellow).at({ 640,0 });

	//タスクを作成
	auto task1 = task_move(r1);
	auto task2 = task_move(r2);

	while (sys::update()) {
		//タスクを再開
		task1.resume();
		task2.resume();

		//矩形を描画
		r1.draw();
		r2.draw();
	}

	return 0;
}