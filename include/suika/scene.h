#pragma once
#include <functional>
#include <stack>
#include "def.h"
#include "base.h"

namespace suika {
	class scene_manager;
	class iscene {
	private:
		friend scene_manager;
	protected:
		scene_manager* _p_manager;
	public:
		virtual void update() = 0;
		virtual void draw() = 0;
		virtual void fin() {};
		virtual ~iscene() = default;
	};

	class scene_manager {
	private:
		struct scene_data {
			std::function<void(double)> fadein;
			double fadein_time;
			std::function<void(double)> fadeout;
			double fadeout_time;
		} _data;

		std::stack<std::unique_ptr<iscene>> _scenes;
		std::unique_ptr<iscene> _next_scene, _now_scene;

		enum class change_state {
			none,
			change,
			back,
		} _change_state;

		enum class fade_state {
			none,
			fadein,
			fadeout
		} _fade_state = fade_state::none;

		double _fade_time = 0;
	public:
		template<class Scene, class... Args>
		void change(std::function<void(double)> fadeout, double fadeout_time, std::function<void(double)> fadein, double fadein_time, Args... arg) {
			_next_scene.reset((iscene*)(new Scene(arg...)));
			_next_scene->_p_manager = this;
			_change_state = change_state::change;
			_data = {fadein, fadein_time, fadeout, fadeout_time};
			_fade_time = 0;
		}

		void back(std::function<void(double)> fadeout, double fadeout_time, std::function<void(double)> fadein, double fadein_time);

		void update(double fade_dt);

		void draw();
	};
}