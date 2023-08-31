#include "..\include\suika\def.h"

#include "..\include\suika\system.h"
#include "..\include\suika\window.h"




namespace suika {
	namespace sys {
		bool exit_flag = false;
		bool stop_flag = false;
		float now_fps = 0.0f;

		std::mutex mtxA,mtxB;

		bool update() {
			if (exit_flag)return false;

			{
				static int  cnt = 0;
				static auto _old = std::chrono::system_clock::now(), _now = std::chrono::system_clock::now();
				_now = std::chrono::system_clock::now();
				if (auto d = std::chrono::duration_cast<std::chrono::nanoseconds>(_now - _old); d >= std::chrono::milliseconds(500)) {
					//fps�v��
					now_fps = static_cast<float>(cnt / (d.count() * suffix::NANO));
					_old = _now;
					cnt = 0;

				}
				cnt++;
			}


			window::flip();
			window::clear();
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
	}
}