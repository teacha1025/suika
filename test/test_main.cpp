#include "suika.h"
using namespace suika;
//namespace palette = suika::palette;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}
int main() {
	font f("メイリオ");
	//texture t("g1.png");
	define interval = 5;
	animator anm("player.png", { 8,3 });
	enum {
		S, SL, LS, L, SR, RS, RL, LR, R,
	};
	anm.add(S, { 0,1,2,3,4,5,6,7 }, interval);
	anm.add(SL, { 8,9,10,11 }, interval, L);
	anm.add(LS, { 11,10,9,8 }, interval, S);
	anm.add(L, { 12,13,14,15 }, interval);
	anm.add(SR, { 16,17,18,19 }, interval, R);
	anm.add(RS, { 19,18,17,16 }, interval, S);
	anm.add(RL, { 19,18,17,8,9,10,11 }, interval, L);
	anm.add(LR, { 11,10,9,8,17,18,19 }, interval,R);
	anm.add(R, { 20,21,22,23 }, interval);

	anm.condition(S, SL, []() {return keyboard::Left.down(); });
	anm.condition(S, SR, []() {return keyboard::Right.down(); });
	anm.condition(SL, LS, []() {return keyboard::Right.release() && keyboard::Left.release(); });
	anm.condition(SL, LR, []() {return keyboard::Right.press(); });
	anm.condition(SR, RL, []() {return keyboard::Right.release() && keyboard::Left.down(); });
	anm.condition(SR, RS, []() {return keyboard::Right.release() && keyboard::Left.release(); });
	anm.condition(LS, LR, []() {return keyboard::Right.press() && keyboard::Left.release(); });
	anm.condition(LS, SL, []() {return keyboard::Right.release() && keyboard::Left.press(); });
	anm.condition(RS, RL, []() {return keyboard::Right.release() && keyboard::Left.press(); });
	anm.condition(RS, SR, []() {return keyboard::Right.press() && keyboard::Left.release(); });
	anm.condition(L, LS, []() {return keyboard::Right.release() && keyboard::Left.release(); });
	anm.condition(L, LR, []() {return keyboard::Right.press(); });
	anm.condition(R, RS, []() {return keyboard::Right.release() && keyboard::Left.release(); });
	anm.condition(R, RL, []() {return keyboard::Right.release() && keyboard::Left.press(); });

	float rot = 0;

	anm.set(S);
	while (sys::update()) {
		anm.centered({ 16,16 }).at(window::center()).extended(4.0).rotated(rot).updated(1);
		anm.rect().draw();
		anm.draw();
		rot += sys::delta() / 2;
	}
}
