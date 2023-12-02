#include "suika.h"
#include <queue>
#include <regex>
#include <fstream>
using namespace suika;
//namespace palette = suika::palette;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}
static task<> task_wait(uint count) {
	for (uint i = 0; i < count; i++) {
		co_yield{};
	}
}

#define wait(c) co_await task_wait(c)
enum type {
	wit=1,
	angle=2,
	speed=4,
	pos=8,
	angle_speed=16,
};

union edata {
	point<float> pos;
	float angle;
	float speed;
	float angle_speed;
	uint wait_time;
};
struct enemy_info {
	point<float> pos;
	float angle;
	float speed;
	float angle_speed;
	uint flag = 0;
};
struct emove_data {
	type t;
	edata d;
};




class enemy {
	font f = font("メイリオ");
	
	task<enemy_info> test_task(std::queue<emove_data> data) {
		enemy_info ifo;
		uint counter = 0;
		while (!data.empty()) {
			auto d = data.front();
			data.pop();
			switch (d.t) {
				case type::angle:
					ifo.angle = d.d.angle;
					ifo.flag |= type::angle;
					break;
				case type::speed:
					ifo.speed = d.d.speed;
					ifo.flag |= type::speed;
					break;
				case type::pos:
					ifo.pos = d.d.pos;
					ifo.flag |= type::pos;
					break;
				case type::angle_speed:
					ifo.angle_speed = d.d.angle_speed;
					ifo.flag |= type::angle_speed;
					break;
				case type::wit:
					for (; counter < d.d.wait_time; counter++) {
						co_yield ifo;
						ifo.flag = 0;
					}
					break;
			}
		}
		co_return ifo;
	}
	task<enemy_info> t;
public:
	enemy_info info;
	enemy(std::queue<emove_data> data) {
		info = { .pos = {0,0},.angle = 0,.speed = 0,.angle_speed = 0 };
		t = (test_task(data));
	}
	void update() {
		t.resume();
		auto i = t.value();
		if (i.flag & type::angle) {
			info.angle = i.angle;
		}
		if (i.flag & type::speed) {
			info.speed = i.speed;
		}
		if (i.flag & type::pos) {
			info.pos = i.pos;
		}
		if (i.flag & type::angle_speed) {
			info.angle_speed = i.angle_speed;
		}
		auto d = polar2(info.speed, info.angle);
		info.pos += d.to_vector();
		info.angle += info.angle_speed;
	}
	void draw() {
		circle(16).at(info.pos).draw();
	}
};

class enemy_manager {
private:
	std::vector<enemy> enemies;
public:
	void update() {
		for (uint i = 0; i < enemies.size(); i++) {
			enemies[i].update();
		}
	}
	void draw() {
		for (auto& e : enemies) {
			e.draw();
		}
	}
	void add(std::queue<emove_data> data) {
		enemies.push_back(enemy(data));
	}
	void clear() {
		enemies.clear();
		enemies.shrink_to_fit();
	}
};
std::unordered_map<string,std::queue<emove_data>> data;

task<> stage(enemy_manager& e, std::unordered_map<string, std::queue<emove_data>> data) {
	e.add(data["test2"]);
	wait(60);
	e.add(data["test1"]);
	wait(60);
	e.add(data["test2"]);
	wait(60);
	e.add(data["test1"]);
}

std::queue<emove_data> parse(std::vector<std::string> ecl) {
	const std::string REG_INT = R"([+|-]*\d+)";
	const std::string REG_FLOAT = R"([+|-]*\d*(?:\.\d*)?)";
	const std::string REG_COUNT = R"(^(\s*\d+):)";

	const std::string REG_POS = R"(^\s*pos\s*=\s*\[()" + REG_FLOAT + R"()\s*,\s*()" + REG_FLOAT + R"()\])";
	const std::string REG_ANGLE = R"(^\s*angle\s*=\s*()" + REG_FLOAT + R"())";
	const std::string REG_SPEED = R"(^\s*speed\s*=\s*()" + REG_FLOAT + R"())";
	const std::string REG_ANGLESPEED = R"(^\s*agl_spd\s*=\s*()" + REG_FLOAT + R"())";
	std::queue<emove_data> ret;
	for (auto line : ecl) {
		line = std::regex_replace(line, std::regex(R"([\n|\r]+)"), "");
		std::smatch m;
		if (std::regex_match(line, m, std::regex(REG_COUNT))) {
			uint count = std::stoi(m[1].str());
			ret.push(emove_data{ .t = type::wit, .d = {.wait_time = count} });
		}
		else if (std::regex_match(line, m, std::regex(REG_POS))) {
			float x = std::stof(m[1].str());
			float y = std::stof(m[2].str());
			ret.push(emove_data{ .t = type::pos, .d = {.pos = {x,y}} });
		}
		else if (std::regex_match(line, m, std::regex(REG_ANGLE))) {
			float angle = std::stof(m[1].str());
			ret.push(emove_data{ .t = type::angle, .d = {.angle = (float)math::radian(angle)} });
		}
		else if (std::regex_match(line, m, std::regex(REG_SPEED))) {
			float speed = std::stof(m[1].str());
			ret.push(emove_data{ .t = type::speed, .d = {.speed = speed} });
		}
		else if (std::regex_match(line, m, std::regex(REG_ANGLESPEED))) {
			float angle_speed = std::stof(m[1].str());
			ret.push(emove_data{ .t = type::angle_speed, .d = {.angle_speed = (float)math::radian(angle_speed)} });
		}

	}

	return ret;
}

int main() {
	font f("メイリオ");
	f.at({ 0,0 });
	enemy_manager e;
	task<> s;
	auto load = [&]() {
		std::ifstream ifs("test.ecl");
		std::string str;
		std::vector<std::string> ecl;
		bool is_in_sub = false;
		string sub_name;
		std::smatch m;
		data.clear();
		e.clear();
		while (std::getline(ifs, str)) {
			if (std::regex_match(str, m, std::regex(R"(^\s*sub\s+([a-zA-Z_]+[a-zA-Z_0-9]*))"))) {
				is_in_sub = true;
				sub_name = m[1].str();
				continue;
			}
			if (std::regex_match(str, m, std::regex(R"(^\s*end\s+sub)"))) {
				is_in_sub = false;
				data[sub_name] = parse(ecl);
				ecl.clear();
				continue;
			}
			ecl.push_back(str);
		}
		s = stage(e, data);
	};
	load();
	while (sys::update()) {
		if (keyboard::F5.down()) load();
		s.resume();
		e.update();
		e.draw();
	}
}
