/*
* animator
*	画像を読み込んでアニメーションを表示する
*/

#include "../include/suika.h"
using namespace suika;

//アプリケーションの初期化
void init() {
	//log.logにログを出力する
	suika::log.set(true, "log.log");

	//ウィンドウの設定
	window::background(palette::yellowgreen);
	window::title("APP");
	window::vsync(true);
}

int main() {
	//画像を読み込んでx:4,y:3に分割しアニメーションを作成する
	animator anm("resource/test2.bmp", { 4,3 });

	//id:0のアニメーションにフレーム番号0,1,2,1を8フレームごとに切替で設定する
	anm.add(0, { 0,1,2,1 }, 8);
	anm.add(1, { 3,4,5,4 }, 8);
	anm.add(2, { 7,8,9 }, 8);

	//初期アニメーションを0にし、画面中央に4倍に拡大して表示する
	anm.at({ 640,480 }).centered(anm.rect().size()/2).extended(4).set(0);

	uint state = 0;
	while (sys::update()) {
		//スペースキーでアニメーションを切り替える
		if (keyboard::Space.down()) {
			state++;
			state %= 3;
			anm.set(state);
		}

		//毎フレームカウントを1進めて描画する
		anm.updated(1);
		anm.draw();
	}

	return 0;
}
