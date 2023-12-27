/*
* keyboard
*	キー入力を利用したオブジェクトの移動
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
	// オブジェクトの座標
	float2 position = window::center();

	// オブジェクト(矩形)の定義
	rect object(float2{ 128,128 });

	// オブジェクトの色などを設定
	object.colored(palette::white).centered(object.size() / 2);
	while (sys::update()) {
		// 十字キー左を押している間は
		if (keyboard::Left.press()) {
			// x座標を毎フレーム減らす
			position.x -= 4;
		}

		// 十字キー左を押している間は
		else if (keyboard::Right.press()) {
			position.x += 4;
		}

		// 十字キー左を押している間は
		if (keyboard::Up.press()) {
			position.y -= 4;
		}

		// 十字キー左を押している間は
		else if (keyboard::Down.press()) {
			position.y += 4;
		}

		object.at(position).draw();
	}

	return 0;
}