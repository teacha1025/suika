#include "../include/suika/scene.h"

namespace suika {
	void scene_manager::back(std::function<void(double)> fadeout, double fadeout_time, std::function<void(double)> fadein, double fadein_time) {
		_next_scene = std::move(_scenes.top());
		_change_state = change_state::back;
		_data = { fadein, fadein_time, fadeout, fadeout_time };
		_fade_time = 0;
	}

	void scene_manager::update(double fade_dt) {
		if (_change_state == change_state::change) {
			if (_fade_state == fade_state::none) {
				_fade_state = fade_state::fadeout;
				_fade_time = 0;
				if (_fade_time >= _data.fadeout_time) {
					_fade_state = fade_state::fadein;
					_fade_time = 0;
					if(_now_scene) _now_scene->fin();
					_scenes.push(std::move(_now_scene));
					_now_scene = std::move(_next_scene);
					_now_scene->init();
					_next_scene = nullptr;

					if (_fade_time >= _data.fadein_time) {

						_change_state = change_state::none;
						_fade_state = fade_state::none;
					}
				}
			}
			else if (_fade_state == fade_state::fadeout) {
				_fade_time += fade_dt;
				if (_fade_time >= _data.fadeout_time) {
					_fade_state = fade_state::fadein;
					_fade_time = 0;
					if (_now_scene) _now_scene->fin();
					_scenes.push(std::move(_now_scene));
					_now_scene = std::move(_next_scene);
					_now_scene->init();
					_next_scene = nullptr;
				}
			}
			else if (_fade_state == fade_state::fadein) {
				_fade_time += fade_dt;
				if (_fade_time >= _data.fadein_time) {
					
					_change_state = change_state::none;
					_fade_state = fade_state::none;
				}
			}
		}
		else if (_change_state == change_state::back) {
			if (_fade_state == fade_state::none) {
				_fade_state = fade_state::fadeout;
				_fade_time = 0;
				
				if (_fade_time >= _data.fadeout_time) {
					_fade_state = fade_state::fadein;
					_fade_time = 0;
					_now_scene->fin();
					_scenes.pop();
					_now_scene = std::move(_next_scene);
					_next_scene = nullptr;
					if (_fade_time >= _data.fadein_time) {

						_change_state = change_state::none;
						_fade_state = fade_state::none;
					}
				}
			}
			else if (_fade_state == fade_state::fadeout) {
				_fade_time += fade_dt;
				if (_fade_time >= _data.fadeout_time) {
					_fade_state = fade_state::fadein;
					_fade_time = 0;
					_now_scene->fin();
					_scenes.pop();
					_now_scene = std::move(_next_scene);
					_next_scene = nullptr;
				}
			}
			else if (_fade_state == fade_state::fadein) {
				_fade_time += fade_dt;
				if (_fade_time >= _data.fadein_time) {
					
					_change_state = change_state::none;
					_fade_state = fade_state::none;
				}
			}
		}
		{
			if (_scenes.empty()) return;
			_now_scene->update();
		}
	}

	void scene_manager::draw() {
		if (_scenes.empty()) return;
		_now_scene->draw();
		if (_fade_state == fade_state::fadein) {
			_data.fadein(_fade_time);
		}
		else if (_fade_state == fade_state::fadeout) {
			_data.fadeout(_fade_time);
		}
	}
}