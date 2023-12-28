// -----------------------------------------------------------
// 
// mouse.
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

#include "../include/suika/mouse.h"
#include "d3d/dinput.hpp"

namespace suika {
	namespace mouse {
		detail::mouse Left;
		detail::mouse Right;
		detail::mouse Middle;
		detail::mouse Button4;
		detail::mouse Button5;
		detail::mouse Button6;
		detail::mouse Button7;
		detail::mouse Button8;

		void init() {
			Left = detail::mouse(0, "LeftClick");
			Right = detail::mouse(1, "RightClick");
			Middle = detail::mouse(2, "MiddleClick");
			Button4 = detail::mouse(3, "Mouse4");
			Button5 = detail::mouse(4, "Mouse5");
			Button6 = detail::mouse(5, "Mouse6");
			Button7 = detail::mouse(6, "Mouse7");
			Button8 = detail::mouse(7, "Mouse8");
		}

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

		point<int> position(window::id id) {
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(id, &p);
			return { p.x, p.y };
		}

		void position(const point<int>& p, window::id id, bool flag) {
			if (flag && GetActiveWindow() == id) {
				POINT pt{ .x = p.x, .y = p.y };
				ClientToScreen(id, &pt);
				SetCursorPos(pt.x, pt.y);
			}
		}

		point<int> delta_position(window::id id) {
			return {d3d::dinput::mouse_state.lX, d3d::dinput::mouse_state.lY};
		}

		int wheel() {
			return d3d::dinput::mouse_state.lZ / 120;
		}

		void style(cursor s) {
			auto c = IDC_ARROW;
			switch (s) {
			case icon:
			case arrow: {
				c = IDC_ARROW;
				break;
			}
			case up_arrow: {
				c = IDC_UPARROW;
				break;
			}
			case ibeam: {
				c = IDC_IBEAM;
				break;
			}
			case cross: {
				c = IDC_CROSS;
				break;
			}
			case hand: {
				c = IDC_HAND;
				break;
			}
			case no: {
				c = IDC_NO;
				break;
			}
			case resize_NS: {
				c = IDC_SIZENS;
				break;
			}
			case resize_WE: {
				c = IDC_SIZEWE;
				break;
			}
			case resize_NWSE: {
				c = IDC_SIZENWSE;
				break;
			}
			case resize_NESW: {
				c = IDC_SIZENESW;
				break;
			}
			case resize_all: {
				c = IDC_SIZEALL;
				break;
			}
			case help: {
				c = IDC_HELP;
				break;
			}
			case pin: {
				c = IDC_PIN;
				break;
			}
			case person: {
				c = IDC_PERSON;
				break;
			}
			case wait: {
				c = IDC_WAIT;
				break;
			}
			case appstarting: {
				c = IDC_APPSTARTING;
				break;
			}
			default: {
				c = IDC_ARROW;
				break;
			}
			}
			SetCursor(LoadCursor(NULL, c));
		}
	}

	namespace detail {
		mouse::mouse(unsigned int code, string name) {
			_state = input_state::release;
			_code = code;
			_press_count = 0;
			_device_name = name;
		}

		template<class T>
		bool contain(const std::vector<T>& v, T val) {
			return std::find(v.begin(), v.end(), val) != v.end();
		}

		void mouse::update() {
			auto tmp = _press_count;
			auto wid = GetActiveWindow();
			if (contain(window::all_id(), wid) && (d3d::dinput::mouse_state.rgbButtons[_code] & 0x80) != 0) {
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
