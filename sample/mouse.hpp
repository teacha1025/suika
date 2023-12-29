/*
* mouse
*	マウスにオブジェクトを追従させる
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
    //円の定義
    circle c(64);

    //円の拡大率
    range<0.1f, 5.0f> rate = 1.0f;

    while(sys::update()) {
        //マウスの位置を取得
        float2 position = mouse::position();

        //マウスの左ボタンが押されているとき
        if(mouse::Left.press()) {
           //円の色を赤にする
              c.colored(palette::red);
        }
        else {
            //円の色を白にする
            c.colored(palette::white);
        }

        //ホイールの回転で拡大率を変更
        rate += mouse::wheel() * 0.1f;

        //マウスの位置に円を描画
        c.extended(rate).at(position).draw();
    }

    return 0;
}
