/*
* keyboard
*	繧ｭ繝ｼ蜈･蜉帙ｒ蛻ｩ逕ｨ縺励◆繧ｪ繝悶ず繧ｧ繧ｯ繝医・遘ｻ蜍・
*/

#include "../include/suika.h"
using namespace suika;

//繧｢繝励Μ繧ｱ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ蛻晄悄蛹・
void init() {
	//log.log縺ｫ繝ｭ繧ｰ繧貞・蜉帙☆繧・
	suika::log.set(true, "log.log");

	//繧ｦ繧｣繝ｳ繝峨え縺ｮ險ｭ螳・
	window::background(palette::black);
	window::title("APP");
	window::vsync(true);
}

int main() {
	// 繧ｪ繝悶ず繧ｧ繧ｯ繝医・蠎ｧ讓吮仄
	float2 position = window::center();

	// 繧ｪ繝悶ず繧ｧ繧ｯ繝・遏ｩ蠖｢)縺ｮ螳夂ｾｩ
	rect object(float2{ 128,128 });

	// 繧ｪ繝悶ず繧ｧ繧ｯ繝医・濶ｲ縺ｪ縺ｩ繧定ｨｭ螳・
	object.colored(palette::white).centered(object.size() / 2);
	while (sys::update()) {
		// 蜊∝ｭ励く繝ｼ蟾ｦ繧呈款縺励※縺・ｋ髢薙・
		if (keyboard::Left.press()) {
			// x蠎ｧ讓吶ｒ豈弱ヵ繝ｬ繝ｼ繝貂帙ｉ縺・
			position.x -= 4;
		}

		// 蜊∝ｭ励く繝ｼ蟾ｦ繧呈款縺励※縺・ｋ髢薙・
		else if (keyboard::Right.press()) {
			position.x += 4;
		}

		// 蜊∝ｭ励く繝ｼ蟾ｦ繧呈款縺励※縺・ｋ髢薙・
		if (keyboard::Up.press()) {
			position.y -= 4;
		}

		// 蜊∝ｭ励く繝ｼ蟾ｦ繧呈款縺励※縺・ｋ髢薙・
		else if (keyboard::Down.press()) {
			position.y += 4;
		}

		object.at(position).draw();
	}

	return 0;
}
