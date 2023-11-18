#include "suika.h"
namespace palette = suika::palette;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}

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
			f_elm.text(str).at({ 48 , e * 40 + 720 }).colored(e == elm ? palette::white : palette::gray, palette::black).draw();
		}
	}
	virtual void fadeout(double t) override {
		double _t = suika::ease::out_expo(t*2);
		f_title.at({ 640, 200 }).resized(64+_t*100).colored(palette::white,1-_t).centered(f_title.rect().size() / 2).draw();
		for (const auto& [e, str] : elm_str) {
			f_elm.text(str).at({ 48 - _t * 180 , e * 40 + 720 }).colored(e == elm ? palette::white : palette::gray, palette::black).draw();
		}
	}
	virtual void fadein(double t) override {
		double _t = 1-suika::ease::out_expo(t * 2);
		f_title.resized(64).colored(palette::white, 1).centered(f_title.rect().size() / 2).at({ 640 - _t * 1280, 200 }).draw();
		for (const auto& [e, str] : elm_str) {
			f_elm.text(str).at({ 48 - _t * 180 , e * 40 + 720 }).colored(e == elm ? palette::white : palette::gray, palette::black).draw();
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
				_p_manager->change<::start>(0.3, 0.3, true);
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
		double _t = suika::ease::out_expo(t * 2);
		f_title.at({ 640, -48 + _t * 120 }).colored(palette::white,1.0f).draw();
	}
	virtual void fadeout(double t) override {
		f_title.at({ 640, 72 }).colored(palette::white,(1-2*t)).draw();
	}
	virtual void update() override {
		if (suika::keyboard::Escape.down()) {
			_p_manager->back(0.3, 0.3, true);
		}
	}
};

int main() {
	suika::font f("メイリオ");
	suika::scene_manager sm;
	sm.change<title>(0.0, 0.0, true);
	while (suika::sys::update()) {
		sm.update();
		sm.draw();
	}
}
