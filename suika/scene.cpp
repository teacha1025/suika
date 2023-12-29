// -----------------------------------------------------------
// 
// scene manager
// 
// Copyright 2023 teacha1025
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// -----------------------------------------------------------


#include "../include/suika/window.h"
#include "../include/suika/except.h"
#include "../include/suika/scene.h"
#include "../include/suika/system.h"

namespace suika {
	void scene_manager::back(double fadeout_time, double fadein_time, bool is_fade_sametime) {
		if (_scenes.empty() || _fade_state != fade_state::none) return;
		_next_scene = std::move(_scenes.top());
		_change_state = change_state::back;
		_fade_state = fade_state::none;
		_data = { std::bind(&iscene::fadein, *_next_scene, std::placeholders::_1), fadein_time, std::bind(&iscene::fadeout, *_now_scene, std::placeholders::_1), fadeout_time };
		_fade_time = 0;
		_is_fade_sametime = is_fade_sametime;
	}

	void scene_manager::update() {
		double dt = sys::delta();
		if (_now_scene != nullptr) {
			
			_now_scene->update();
		}
		if (_change_state == change_state::change) {
			if (_is_fade_sametime) {
				if (_fade_state == fade_state::none) {
					_fade_state = fade_state::fade;
					_fade_time = 0;
					_next_scene->init();
					if (_fade_time >= _data.fadeout_time) {
						_change_state = change_state::none;
						_fade_state = fade_state::none;
						if (_now_scene) {
							_now_scene->fin();
							_scenes.push(std::move(_now_scene));
						}
						_now_scene = std::move(_next_scene);
						_next_scene = nullptr;
					}
				}
				else if(_fade_state == fade_state::fade) {
					_fade_time += sys::delta();
					if (_fade_time >= _data.fadeout_time) {
						_change_state = change_state::none;
						_fade_state = fade_state::none;
						if (_now_scene) {
							_now_scene->fin();
							_scenes.push(std::move(_now_scene));
						}
						_now_scene = std::move(_next_scene);
						_next_scene = nullptr;
					}
				}
			}
			else {
				if (_fade_state == fade_state::none) {
					_fade_state = fade_state::fadeout;
					_fade_time = 0;
					if (_fade_time >= _data.fadeout_time) {
						_fade_state = fade_state::fadein;
						_fade_time = 0;
						if (_now_scene) {
							_now_scene->fin();
							_scenes.push(std::move(_now_scene));
						}
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
					_fade_time += dt;
					if (_fade_time >= _data.fadeout_time) {
						_fade_state = fade_state::fadein;
						_fade_time = 0;
						if (_now_scene) {
							_now_scene->fin();
							_scenes.push(std::move(_now_scene));
						}
						_now_scene = std::move(_next_scene);
						_now_scene->init();
						_next_scene = nullptr;
					}
				}
				else if (_fade_state == fade_state::fadein) {
					_fade_time += dt;
					if (_fade_time >= _data.fadein_time) {

						_change_state = change_state::none;
						_fade_state = fade_state::none;
					}
				}
			}
		}
		else if (_change_state == change_state::back) {
			if (_is_fade_sametime) {
				if (_fade_state == fade_state::none) {
					_fade_state = fade_state::fade;
					_fade_time = 0;
					_next_scene->init();
					if (_fade_time >= _data.fadeout_time) {
						_change_state = change_state::none;
						_fade_state = fade_state::none;
						if (_now_scene) {
							_now_scene->fin();
							_scenes.pop();
						}
						_now_scene = std::move(_next_scene);
						_next_scene = nullptr;
					}
				}
				else if (_fade_state == fade_state::fade) {
					_fade_time += dt;
					if (_fade_time >= _data.fadeout_time) {
						_change_state = change_state::none;
						_fade_state = fade_state::none;
						if (_now_scene) {
							_now_scene->fin();
							_scenes.pop();
						}
						_now_scene = std::move(_next_scene);
						_next_scene = nullptr;
					}
				}
			}
			else {
				if (_fade_state == fade_state::none) {
					_fade_state = fade_state::fadeout;
					_fade_time = 0;

					if (_fade_time >= _data.fadeout_time) {
						_fade_state = fade_state::fadein;
						_fade_time = 0;
						_now_scene->fin();
						_scenes.pop();
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
					_fade_time += dt;
					if (_fade_time >= _data.fadeout_time) {
						_fade_state = fade_state::fadein;
						_fade_time = 0;
						_now_scene->fin();
						_scenes.pop();
						_now_scene = std::move(_next_scene);
						_now_scene->init();
						_next_scene = nullptr;
					}
				}
				else if (_fade_state == fade_state::fadein) {
					_fade_time += dt;
					if (_fade_time >= _data.fadein_time) {

						_change_state = change_state::none;
						_fade_state = fade_state::none;
					}
				}
			}
		}
		
	}

	void scene_manager::draw() {
		if (_change_state != change_state::none) {
			if (_fade_state == fade_state::fade) {
				if (_now_scene) {
					_now_scene->fadeout(_fade_time);
				}
				_next_scene->fadein(_fade_time);
			}
			else if (_fade_state == fade_state::fadein) {
				_now_scene->fadein(_fade_time);
			}
			else if (_fade_state == fade_state::fadeout) {
				_now_scene->fadeout(_fade_time);
			}
		}
		else {
			_now_scene->draw();
		}
	}
}
