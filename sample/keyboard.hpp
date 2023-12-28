/*
* keyboard
*	キー入力によってオブジェクトを移動させる
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

int main() {
	// オブジェクトの位置
	float2 position = window::center();

	// オブジェクトの定義
	rect object(float2{ 128,128 });

	// オブジェクトの設定
	object.colored(palette::white).centered(object.size() / 2);
	while (sys::update()) {
		// キーが押されたとき
		if (keyboard::Left.press()) {
			// 左に移動
			position.x -= 4;
		}

		// キーが押されたとき
		else if (keyboard::Right.press()) {
			// 右に移動
			position.x += 4;
		}

		// キーが押されたとき
		if (keyboard::Up.press()) {
			// 上に移動
			position.y -= 4;
		}

		// キーが押されたとき
		else if (keyboard::Down.press()) {
			// 下に移動
			position.y += 4;
		}

		object.at(position).draw();
	}

	return 0;
}
