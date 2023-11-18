#include "suika.h"
#include "../suika/d3d/dwrite.h"
//#include "../suika/d3d/blend.hpp"
//#include "../suika/d3d/texture.hpp"
//#include "../suika/d3d/vertex.h"

namespace palette = suika::palette;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}

void test_pad(int i) {
	static suika::font f("メイリオ");
	define X = 280, OFS = 40;
	auto btn = [&](suika::detail::gamepad_button b, int y) {
		auto c = suika::palette::gray;
		if (b.press()) {
			c = suika::palette::white;
		}
		if (b.down()) {
			c = suika::palette::blue;
		}
		if (b.up()) {
			c = suika::palette::red;
		}
		f.text(b.to_string()).colored(c).at({ i*X,y*20 + OFS }).draw();
	};
	auto trg = [&](suika::detail::gamepad_trigger t, int y) {
		auto c = suika::hsv(0, 0, t.value() / 2.0 + 0.5, 255).to_color();
		f.text(std::format("{}:{:1.3f}", t.to_string().to_string(), t.value())).colored(c).at({ i * X,y * 20 + OFS }).draw();
	};
	auto stk = [&](suika::detail::gamepad_stick s, int y) {
		f.text(s.to_string()).colored(s.press() ? suika::palette::white : suika::palette::gray).at({ i * X,y * 20 + OFS }).draw();
		f.text(std::format("{}:{}", s.to_string().to_string(), s.value().to_string().to_string())).at({i * X,y * 20 + OFS }).draw();
	};
	auto& pad = suika::gamepad::pad[i];
	f.text(pad.info().name).colored(suika::palette::white).at({i * X,0}).draw();
	f.text(std::format("{}, VID:{},PID:{}", std::string(magic_enum::enum_name(pad.info().states)), pad.info().vid.to_string(), pad.info().pid.to_string())).colored(suika::palette::white).at({i * X,20}).draw();
	btn(pad.A, 0);
	btn(pad.B, 1);
	btn(pad.X, 2);
	btn(pad.Y, 3);
	btn(pad.Up, 4);
	btn(pad.Down, 5);
	btn(pad.Left, 6);
	btn(pad.Right, 7);
	btn(pad.Back, 8);
	btn(pad.Start, 9);
	btn(pad.LShoulder, 10);
	btn(pad.RShoulder, 11);
	stk(pad.LStick, 13);
	stk(pad.RStick, 14);
	trg(pad.LTrigger, 15);
	trg(pad.RTrigger, 16);
	
}

class S2;

class S1 : suika::iscene {
	suika::font f;
	suika::rect r;
public:
	S1() {
		f.resized(32).colored(suika::palette::red).blended(suika::blend::alpha).text("S1");
		r = suika::rect(suika::window::size());
		r.blended(suika::blend::alpha).centered({ 0,0 }).at({ 0,0 });
	}
	virtual void init() override {
		f.resized(32).at({ 0,0 }).colored(suika::palette::red);
	}
	virtual void draw() override {
		f.draw();
	}
	virtual void fadein(double t) override{
		//r.colored(suika::color_f(suika::palette::black, 1 - t)).draw();
		auto _t = 1 - t;
		f.resized(32 * t).colored(suika::color_f(suika::palette::red, t)).text("S1").at({ 0,920 * _t * _t }).draw();
		//f.resized(20).colored(suika::color_f(1, 1, 1, 1)).text("S1FI").at({ 0,160 });
	}
	virtual void fadeout(double t) override{
		//r.colored(suika::color_f(suika::palette::black, t)).draw();
		auto _t = 1 - t;
		f.resized(32 * _t).colored(suika::color_f(suika::palette::red, _t)).at({ 0,920 * t * t }).draw();
	}
	virtual void update() override {
		if (suika::keyboard::A.down()) {
			_p_manager->change<S2>(1.0, 1.0, true);
		}
	}
};

class S2 : suika::iscene {
	suika::font f;
	suika::rect r;
public:
	S2() {
		f.resized(48).colored(suika::palette::red).blended(suika::blend::alpha).text("S2");
		r = suika::rect(suika::window::size());
		r.blended(suika::blend::alpha).centered({ 0,0 }).at({ 0,0 });
	}
	virtual void init() override {
		//suika::window::background(suika::palette::yellowgreen);
		f.resized(32).at({ 0,0 }).colored(suika::palette::red);
	}
	virtual void draw() override {
		f.draw();
	}
	virtual void fadein(double t) override {
		//r.colored(suika::color_f(suika::palette::black, 1 - t)).draw();
		auto _t = 1 - t;
		f.resized(48 * t).colored(suika::color_f(suika::palette::red, t)).at({ 0,920 * _t * _t }).draw();
	}
	virtual void fadeout(double t) override {
		//r.colored(suika::color_f(suika::palette::black, t)).draw();
		auto _t = 1 - t;
		f.resized(48 * _t).colored(suika::color_f(suika::palette::red, _t)).at({ 0,920 * t * t }).draw();
	}
	virtual void update() override {
		if (suika::keyboard::A.down()) {
			_p_manager->back(1.0, 1.0, true);
		}
	}
};

class start;
class title : suika::iscene {
private:
	suika::font f_elm;
	suika::font f_title;

	enum element {
		start,
		option,
		exit,
		size
	} elm = start;

	std::unordered_map<element, suika::string> elm_str = {
		{start, L"スタート"},
		{option, L"オプション"},
		{exit, L"終了"},
	};
public:
	title() {
		f_elm = suika::font("UD デジタル 教科書体 N-B", 24);
		f_elm.colored(suika::palette::white, 1.0).blended(suika::blend::alpha);
		f_title.resized(64).colored(suika::palette::white, 1.0).blended(suika::blend::alpha).text("ゲームタイトル");
	}
	virtual void init() override {

	}
	virtual void draw() override {
		f_title.centered(f_title.rect().size() / 2).at({ 640, 200 }).draw();
		for(const auto& [e, str] : elm_str) {
			f_elm.text(str).at({ e == elm ? 64 : 48 , e * 40 + 720 }).colored(e == elm ? palette::white : palette::gray, palette::black).draw();
		}
	}
	virtual void fadeout(double t) override {
		f_title.centered(f_title.rect().size() / 2).at({ 640 - (2 * t) * 1280, 200 }).draw();
		for (const auto& [e, str] : elm_str) {
			f_elm.text(str).at({ (e == elm ? 64 : 48) - (2 * t) * 160 , e * 40 + 720 }).colored(e == elm ? palette::white : palette::gray, palette::black).draw();
		}
	}
	virtual void fadein(double t) override {
		f_title.centered(f_title.rect().size() / 2).at({ 640 - (1 - 2 * t) * 1280, 200 }).draw();
		for (const auto& [e, str] : elm_str) {
			f_elm.text(str).at({ (e == elm ? 64 : 48) - (1-2*t) * 160 , e * 40 + 720 }).colored(e == elm ? palette::white : palette::gray, palette::black).draw();
		}
	}
	virtual void update() override {
		if(suika::keyboard::Up.down()) {
			int e = (int)elm;
			e = (e+size-1)%size;
			elm = (element)e;
		}
		if (suika::keyboard::Down.down()) {
			int e = (int)elm;
			e = (e + 1) % size;
			elm = (element)e;
		}
if (suika::keyboard::Return.down()) {
			switch (elm) {
			case start:
				_p_manager->change<::start>(0.5, 0.5, true);
				break;
			case option:
				break;
			case exit:
				suika::sys::exit();
				break;
			}
		}
	}
};

class start : suika::iscene {
private:
	suika::font f_elm;
	suika::font f_title;
public:
	start() {
		f_elm = suika::font("UD デジタル 教科書体 N-B", 24);
		f_elm.colored(suika::palette::white, 1.0).blended(suika::blend::alpha);
		f_title.resized(48).colored(suika::palette::white, 1.0).blended(suika::blend::alpha).text("難易度選択").centered(f_title.rect().size()/2);
	}
	virtual void init() override {

	}
	virtual void draw() override {
		f_title.at({ 640, 72 }).draw();
	}
	virtual void fadein(double t) override {
		f_title.at({ 640, -48 + (2*t) * 120 }).colored(palette::white,1.0f).draw();
	}
	virtual void fadeout(double t) override {
		f_title.at({ 640, 72 }).colored(palette::white,(1-2*t)).draw();
	}
	virtual void update() override {
		if (suika::keyboard::Escape.down()) {
			_p_manager->back(0.5, 0.5, true);
		}
	}
};

int main() {
	suika::font f("メイリオ");

	suika::texture tex("test.bmp");

	define w = 64, h = 64;
	int i = 0, j = 0, edge = 0;

	suika::rect r({ w - 1,h - 1 });
	suika::circle c(32);
	int cursor = suika::mouse::arrow;
	suika::line l(suika::window::size()/2, {0,0});

	suika::scene_manager sm;
	static suika::rect rc(suika::window::size());
	rc.blended(suika::blend::alpha).centered({ 0,0 }).at({ 0,0 });
	sm.change<title>(0.0, 0.0, true);
	while (suika::sys::update()) {
		sm.update();
		sm.draw();
#if 0
		test_pad(0);
		test_pad(1);
		test_pad(2);
		test_pad(3);

		if (suika::keyboard::Return.down()) {
			suika::gamepad::load_gamepads();
		}
#endif
#if 0
		edge += suika::mouse::wheel();
		i %= 256;
		suika::window::title(std::format("{:4.1f}fps,{}, [{},{}], {}", suika::sys::fps(), edge, suika::mouse::position().x, suika::mouse::position().y, cursor));
		for (int y = 0; y < 16; y++) {
			for (int x = 0; x < 16; x++) {
				r.at({x*w, y*h}).colored(suika::color(suika::palette::gray, (x+y)*8)).blended(suika::blend::alpha).draw();
				//tex.centered({ 0, 0 }).at({ x * w + w / 2,y * h + h / 2 }).blended(suika::blend::alpha).rotated(i / 20.0f).draw();
			}
		}
		
		if (suika::mouse::Right.down()) {
			static bool flag = false;
			//suika::mouse::position({ 640,480 });
			//SetCursor(LoadCursor(NULL, IDC_HAND));

			while (true) {
				if (flag) {
					auto r = ShowCursor(TRUE);
					if (r >= 0)
						break;
				}
				else {
					auto r = ShowCursor(FALSE);
					if (r < 0)
						break;
				}
			}

			flag ^= 1;

			f.edged(flag, 2);
		}
		else if (suika::mouse::Left.down()) {
			cursor++;
			cursor %= 17;
		}
		suika::mouse::style((suika::mouse::cursor)cursor);
		c.at(suika::mouse::position()).resolution(24).colored(suika::color(suika::palette::red, i)).blended(suika::blend::add).draw();
		l.B(suika::mouse::position()).colored(suika::color(suika::palette::white, i)).blended(suika::blend::sub).draw(8.0f,false);
		f.text(L"こんにちは！！").centered({0,0}).at(suika::mouse::position()).resized(64).edged(true,edge).centered(f.rect().size() / 2);
		f.rect().centered(f.rect().size()/2).colored(suika::color(suika::palette::gray, 255)).blended(suika::blend::alpha).draw();
		f.colored(suika::hsv(j, 1.0f,1.0f).to_color(),suika::palette::white).draw();
		j++;
		j %= 360;
#endif
#if 0
		if (i == 60) {
			fd.color = suika::palette::yellow;
			fd.color.a = 1.0f;
			fd.weight = DWRITE_FONT_WEIGHT_LIGHT;
			fd.size = 32.0f;
			fd.font = "游明朝";
			suika::d3d::dwrite::set(fd, cid);
		}
		if (i ==120) {
			i = 0;
			fd.color = suika::palette::white;
			fd.color.a = 1.0f;
			fd.weight = DWRITE_FONT_WEIGHT_BOLD;
			fd.size = 64.0f;
			fd.font = "ＭＳゴシック";
			suika::d3d::dwrite::set(fd, cid);
		}
		suika::d3d::dwrite::draw(L"TEST☺", { 128,128 }, cid);
		i++;
#endif
	}
}
