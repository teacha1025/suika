#include "suika.h"
using namespace suika;
//namespace palette = suika::palette;

void init() {
	suika::window::background(suika::palette::skyblue);
	suika::window::title("APP");
	suika::window::vsync(true);
}

namespace std {
	template<class T1, class T2>
	struct hash<pair<T1, T2>> {
	public:
		size_t operator()(const pair<T1, T2>& p)const {
			 //first分をハッシュ化する
			auto hash1 = hash<T1>{}(p.first);

			//second分をハッシュ化する
			auto hash2 = hash<T2>{}(p.second);

			//重複しないようにハッシュ処理
			size_t seed = 0;
			seed ^= hash1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= hash2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			return seed;
		}
	};
}

namespace suika {
	class animator : public detail::ishape<animator> {
	private:
		animation _anm;
		struct pattern {
			std::vector<uint> pattern;
			double interval = 1;
			bool loop = true;
			uint next = 0;
			bool _smooth = false;
		};
		std::unordered_map<uint, pattern> _pattern;

		std::unordered_map<std::pair<uint, uint>, std::pair<std::function<bool()>, bool>> _condition;

		uint _key = 0;

		point<bool> _turn;

		virtual std::vector<vertex::vertex_2d> create_vertex() override {
			return {};
		}
	public:
		animator() = default;
		animator(string path, const point<uint>& div) {
			_anm = animation(path, div);
		}
		animator(string path, const point<uint>& div, const point<float>& region_lt, const point<float>& region_rb) {
			_anm = animation(path, div, region_lt, region_rb);
		}

		void add(uint key, std::vector<uint> pattern, double interval, uint next) {
			if (_pattern.empty()) {
				_key = key;
			}
			_pattern[key] = { pattern, interval, false, next };
		}

		void add(uint key, std::vector<uint> pattern, double interval) {
			if (_pattern.empty()) {
				_key = key;
			}
			_pattern[key] = { pattern, interval, true, 0 };
		}

		void condition(uint from, uint to, std::function<bool()> cond, bool smooth = true) {
			_condition[{from, to}] = { cond, smooth };
		}

		animator& turned(const point<bool>& turn)& {
			_turn = turn;
			return static_cast<animator&>(*this);
		}

		animator turned(const point<bool>& turn)&& {
			_turn = turn;
			return static_cast<animator&&>(std::move(*this));
		}

		/// <summary>
		/// アニメーションを更新する
		/// </summary>
		/// <param name="t">変化時間</param>
		virtual void updated(double t) {
			if (_pattern.empty()) {
				return;
			}
			for (const auto& [key, cond] : _condition) {
				if (key.first == _key) {
					if (cond.first()) {
						auto k = _key;
						int ind = (int)_anm.index();
						_key = key.second;
						_anm.patterned(_pattern[_key].pattern, _pattern[_key].interval, _pattern[_key].loop);
						if (cond.second && !_pattern[k].loop) {
							_anm.indexed(std::clamp((int)_pattern[k].pattern.size() - ind, 0, (int)_pattern[_key].pattern.size() - 1));
						}
						return;
					}
				}
			}
			if (_anm.finished()) {
				_key = _pattern[_key].next;
				_anm.patterned(_pattern[_key].pattern, _pattern[_key].interval, _pattern[_key].loop);
				return;
			}
			_anm.updated(t);
		}

		void set(uint key) {
			_key = key;
			_anm.patterned(_pattern[_key].pattern, _pattern[_key].interval, _pattern[_key].loop);
		}

		rect rect() const {
			return _anm.rect();
		}

		virtual void draw() override {
			_anm.at(_transition).blended(_blend).centered(_center).extended(_extend).rotated(_rotation).turned(_turn).draw();
		}
	};
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
