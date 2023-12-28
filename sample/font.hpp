/*
* font
*	フォントを使って文字列を描画する
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
	// 表示する絵文字の定義
	const string emoji_list[] = { U"🍉", U"🥝", U"🍓", U"和", U"🚅" };

	// フォントサイズ64のメイリオの淵付きフォントを作成
	font edged_font("メイリオ", 64, true, 2, font_weight::extra_bold);

	// フォントサイズ64の游明朝の淵なしフォントを作成
	font font("游明朝", 64);

	// 文字色白、淵色赤で画面中央に表示
	edged_font.text(U"Hello, suika!!").colored(palette::white, palette::red).centered(edged_font.rect().center()).at(window::center());

	// スイカの絵文字を表示
	font.text(emoji_list[0]).centered(font.rect().center()).colored(palette::white);

	while (sys::update()) {

		// フォントを表示
		edged_font.draw();
		
		// 左クリックで文字を切り替える
		if (mouse::Left.down()) {
			static uint i = 0;
			i++;
			i %= 5;

			// 絵文字をセット
			font.text(emoji_list[i]).centered(font.rect().center());
		}

		// マウスの位置にフォントを表示
		font.at(mouse::position()).draw();
	}

	return 0;
}
