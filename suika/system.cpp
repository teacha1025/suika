#include "..\include\suika\def.h"

#include "..\include\suika\system.h"
#include "..\include\suika\window.h"

#include "..\include\suika\keyboard.h"

#include "d3d\vertex.h"
#include "d3d\dinput.hpp"
#include <mutex>

namespace suika {
	namespace keyboard {
		void update();
	}
	namespace mouse {
		void update();
	}
	namespace gamepad {
		void update();
	}


	namespace sys {
		bool exit_flag = false;
		bool stop_flag = false;
		float now_fps = 0.0f;

		std::mutex mtxA,mtxB;

		std::chrono::nanoseconds delta_time = std::chrono::nanoseconds(0);

		bool update() {
			if (exit_flag)return false;

			{
				static int  cnt = 0;
				static auto _fps_old = std::chrono::system_clock::now(), _old = std::chrono::system_clock::now(), _now = std::chrono::system_clock::now();
				_now = std::chrono::system_clock::now();
				if (auto d = std::chrono::duration_cast<std::chrono::nanoseconds>(_now - _fps_old); d >= std::chrono::milliseconds(500)) {
					//fpsŒv‘ª
					now_fps = static_cast<float>(cnt / (d.count() * suffix::NANO));
					_fps_old = _now;
					cnt = 0;

				}
				delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(_now - _old);
				_old = _now;
				cnt++;
			}

			d3d::vertex::flush();
			window::flip();
			window::clear();

			d3d::dinput::update();

			keyboard::update();
			mouse::update();
			gamepad::update();

			return window::process();
		}

		void exit() {
			mtxA.lock();
			{
				exit_flag = true;
			}
			mtxA.unlock();
		}


		void sleep(std::chrono::nanoseconds t) {
			std::this_thread::sleep_for(t);
		}

		void wait(std::chrono::system_clock::time_point t) {
			std::this_thread::sleep_until(t);
		}

		float fps() {
			return now_fps;
		}

		double delta() {
			return delta_time.count() * suffix::NANO;
		}

		long long delta_nano() {
			return delta_time.count();
		}
	}
}