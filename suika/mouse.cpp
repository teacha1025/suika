#include "../include/suika/mouse.h"
#include "d3d/dinput.hpp"
namespace suika {
	namespace mouse {
		detail::_mouse Left(0, "LeftClick");
		detail::_mouse Right(1, "RightClick");
		detail::_mouse Middle(2, "MiddleClick");
		detail::_mouse Button4(3, "Mouse4");
		detail::_mouse Button5(3, "Mouse5");
		detail::_mouse Button6(3, "Mouse6");
		detail::_mouse Button7(3, "Mouse7");
		detail::_mouse Button8(3, "Mouse8");

		void update() {
			Left.update();
			Right.update();
			Middle.update();
			Button4.update();
			Button5.update();
			Button6.update();
			Button7.update();
			Button8.update();
		}
	}

	namespace detail {
		_mouse::_mouse(unsigned int code, string name) {
			_state = input_state::release;
			_code = code;
			_press_count = 0;
			_device_name = name;
		}

		void _mouse::update() {
			auto tmp = _press_count;

			if ((d3d::dinput::mouse_state.rgbButtons[_code] & 0x80) != 0) {
				_press_count++;
				_state = _press_count > 1 ? input_state::press : input_state::down;
			}
			else {
				if (tmp > 0) {
					_state = input_state::up;
				}
				else {
					_state = input_state::release;
				}
				_press_count = 0;
			}
		}
	}
}