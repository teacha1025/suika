// -----------------------------------------------------------
// 
// gamepad.
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

#include "d3d/xinput.h"
#include "d3d/dinput.hpp"
#include "../include/suika/window.h"
#include "../include/suika/gamepad.h"
#include "../include/suika/logger.h"
#include "../include/suika/math.h"

namespace suika {
	namespace detail {
		ubyte xinput_count = 0;
	}
	namespace gamepad {
		std::unordered_map<ubyte,info> gamepads;
		std::array<detail::gamepad, MAX_JOYPAD_NUM> pad;

		void load_gamepads() {
			d3d::dinput::load_gamepad(window::default_id);
            gamepads.reserve(suika::d3d::dinput::gamepad_list.size());
			detail::xinput_count = 0;
			for (ubyte i = 0; i < suika::d3d::dinput::gamepad_list.size(); i++) {
				auto d = info{
					.index = i,
					.states = suika::d3d::dinput::gamepad_list[i].states == 0 ? pad_states::Disable : suika::d3d::dinput::gamepad_list[i].states == 1 ? pad_states::DirectInput : pad_states::XInput,
					.name = suika::d3d::dinput::gamepad_list[i].name,
					.pid = suika::d3d::dinput::gamepad_list[i].pid,
					.vid = suika::d3d::dinput::gamepad_list[i].vid,
				};
				gamepads[i] = d;
				log.info(std::format(L"Gamepad{}({}):{}", d.index, d.states == pad_states::Disable ? L"利用不可" : d.states == pad_states::DirectInput ? L"DirectInput" : L"XInput", d.name.to_wstring()));
			}
			for (ubyte i = 0; i < suika::gamepad::gamepads.size(); i++) {
				init(suika::gamepad::pad[i], i, suika::gamepad::gamepads[i]);
			}
		}

		void init() {
			suika::gamepad::load_gamepads();
		}

		void update() {
			for (ubyte i = 0; i < suika::gamepad::gamepads.size(); i++) {
				update(suika::gamepad::pad[i]);
			}
		}
	}

	namespace detail {
		define PAD_A = 1;
		define PAD_B = 2;
		define PAD_X = 0;
		define PAD_Y = 3;

		define PAD_LB = 4;
		define PAD_RB = 5;

		define PAD_LT = 6;
		define PAD_RT = 7;

		define PAD_BACK = 8;
		define PAD_START = 9;

		define PAD_LSTICK = 10;
		define PAD_RSTICK = 11;

		define PAD_UP = 12;
		define PAD_DOWN = 13;
		define PAD_LEFT = 14;
		define PAD_RIGHT = 15;

		define XPAD_LT = 0x10000;
		define XPAD_RT = 0x20000;

		void init(gamepad& gp, ubyte id, suika::gamepad::info info) {
			gp.A = gamepad_button(XINPUT_GAMEPAD_A, PAD_A, "A", "Button 01", id);
			gp.B = gamepad_button(XINPUT_GAMEPAD_B, PAD_B, "B", "Button 02", id);
			gp.X = gamepad_button(XINPUT_GAMEPAD_X, PAD_X, "X", "Button 03", id);
			gp.Y = gamepad_button(XINPUT_GAMEPAD_Y, PAD_Y, "Y", "Button 04", id);

			gp.LShoulder = gamepad_button(XINPUT_GAMEPAD_LEFT_SHOULDER, PAD_LB, "LB", "Button 05", id);
			gp.RShoulder = gamepad_button(XINPUT_GAMEPAD_RIGHT_SHOULDER, PAD_RB, "RB", "Button 06", id);

			gp.LTrigger = gamepad_trigger(XPAD_LT, PAD_LT, "LT", "Button 07", id);
			gp.RTrigger = gamepad_trigger(XPAD_RT, PAD_RT, "RT", "Button 08", id);

			gp.Back = gamepad_button(XINPUT_GAMEPAD_BACK, PAD_BACK, "BACK", "Button 09", id);
			gp.Start = gamepad_button(XINPUT_GAMEPAD_START, PAD_START, "START", "Button 10", id);

			gp.LStick = gamepad_stick(XINPUT_GAMEPAD_LEFT_THUMB, PAD_LSTICK, "LStick", "LStick", id);
			gp.RStick = gamepad_stick(XINPUT_GAMEPAD_RIGHT_THUMB, PAD_RSTICK, "RStick", "RStick", id);

			gp.Up = gamepad_button(XINPUT_GAMEPAD_DPAD_UP, PAD_UP, "Up", "Button 11", id);
			gp.Down = gamepad_button(XINPUT_GAMEPAD_DPAD_DOWN, PAD_DOWN, "Down", "Button 12", id);
			gp.Left = gamepad_button(XINPUT_GAMEPAD_DPAD_LEFT, PAD_LEFT, "Left", "Button 13", id);
			gp.Right = gamepad_button(XINPUT_GAMEPAD_DPAD_RIGHT, PAD_RIGHT, "Right", "Button 14", id);

			gp._id = id;
			gp._info = info;

			if (info.states != suika::pad_states::XInput) {
				gp._info.index = id + 10;
			}
			else {
				xinput_count++;
				ubyte index = 0, count = 0;
				for (int i = 0; i < 4; i++) {
					XINPUT_STATE s;
					if (XInputGetState(i, &s) == ERROR_SUCCESS) {
						count++;
						if (xinput_count == count) {
							index = i;
							break;
						}
					}
				}
				gp._info.index = index;
			}
		}

		void update(gamepad& gp) {
			if (gp._is_use_xinput && suika::gamepad::gamepads[gp._id].states == suika::pad_states::XInput) {
				gp._info.states = d3d::XInput::get_state(gp._info.index) ? suika::pad_states::XInput : suika::pad_states::Disable;
			}
			else {
				gp._info.states = d3d::dinput::gp_update(gp._info.vid.to_string() + gp._info.pid.to_string()) ? suika::pad_states::DirectInput : suika::pad_states::Disable;
			}
			gp.A.update();
			gp.B.update();
			gp.X.update();
			gp.Y.update();

			gp.LShoulder.update();
			gp.RShoulder.update();

			gp.LTrigger.update();
			gp.RTrigger.update();

			gp.Back.update();
			gp.Start.update();

			gp.LStick.update();
			gp.RStick.update();

			gp.Up.update();
			gp.Down.update();
			gp.Left.update();
			gp.Right.update();
		}

		gamepad_button::gamepad_button(ulong xcode, ulong dcode, const string& xname, const string& dname, ubyte id) {
			_xcode = xcode;
			_dcode = dcode;
			_device_name = xname;
			_dname = dname;
			_id = id;
		}

		void gamepad_button::update() {
			if (suika::gamepad::gamepads[_id].states == suika::pad_states::Disable) {
				return;
			}
			if (_is_use_xinput && suika::gamepad::gamepads[_id].states == suika::pad_states::XInput) {
				auto tmp = _press_count;

				if (d3d::XInput::xstate.Gamepad.wButtons & _xcode) {
					_press_count++;
					_state = _press_count > 1 ? input_state::press : input_state::down;
					//gamepad::pressed_button.emplace_back(*this);
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
			else {
				auto tmp = _press_count;
				bool flag = false;
				if (_dcode == PAD_UP || _dcode == PAD_DOWN || _dcode == PAD_LEFT || _dcode == PAD_RIGHT) {
					auto d = d3d::dinput::gamepad_state[suika::gamepad::gamepads[_id].vid.to_string() + suika::gamepad::gamepads[_id].pid.to_string()].rgdwPOV[0];
					if (d != ULONG_MAX) {
						float rad = ((float)math::radian(d / 100.0f));
						float x = sinf(rad);
						float y = cosf(rad);
						bool f[4] = { false };//u,d,l,r
						if (x < -0.01f) {
							f[2] = true;
						}
						else if (x > 0.01f) {
							f[3] = true;
						}

						if (y > 0.01f) {
							f[0] = true;
						}
						else if (y < -0.01f) {
							f[1] = true;
						}
						switch (_dcode) {
							case PAD_UP:
								flag = f[0];
								break;
							case PAD_DOWN:
								flag = f[1];
								break;
							case PAD_LEFT:
								flag = f[2];
								break;
							case PAD_RIGHT:
								flag = f[3];
								break;
						}
					}
				}
				else {
					flag = d3d::dinput::gamepad_state[suika::gamepad::gamepads[_id].vid.to_string() + suika::gamepad::gamepads[_id].pid.to_string()].rgbButtons[_dcode] & 0x80;
				}
				if (flag) {
					_press_count++;
					_state = _press_count > 1 ? input_state::press : input_state::down;
					//gamepad::pressed_button.emplace_back(*this);
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

		void gamepad_button::update_trigger(double value) {
			if (suika::gamepad::gamepads[_id].states == suika::pad_states::Disable) {
				return;
			}
			else {
				auto tmp = _press_count;
				if (value >= 0.5) {
					_press_count++;
					_state = _press_count > 1 ? input_state::press : input_state::down;
					//gamepad::pressed_button.emplace_back(*this);
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

		string gamepad_button::to_string() const {
			if (_is_use_xinput && suika::gamepad::gamepads[_id].states == suika::pad_states::XInput) {
				return _device_name;
			}
			else {
				return _dname;
			}
		}

		gamepad_trigger::gamepad_trigger(ulong xcode, ulong dcode, const string& xname, const string& dname, ubyte id) {
			_xcode = xcode;
			_dcode = dcode;
			_device_name = xname;
			_dname = dname;
			_id = id;

			_button = gamepad_button(xcode, dcode, xname, dname, id);
		}

		void gamepad_trigger::update() {
			
			if (suika::gamepad::gamepads[_id].states == suika::pad_states::Disable) {
				return;
			}
			
			if (_is_use_xinput && suika::gamepad::gamepads[_id].states == suika::pad_states::XInput) {
				define TRIGGER_MAX = 255.0;
				auto trg = _xcode == XPAD_LT ? d3d::XInput::xstate.Gamepad.bLeftTrigger : d3d::XInput::xstate.Gamepad.bRightTrigger;
				auto t = trg / TRIGGER_MAX;
				_value =  (t < _deadzone) ? 0 : t;
				_button.update_trigger(_value);
			}
			else {
				define TRIGGER_MAX = 1000.0;
				_button.update();
				_value = _button.press() ? 1.0 : 0.0;
			}
		}

		string gamepad_trigger::to_string() const {
			if (_is_use_xinput && suika::gamepad::gamepads[_id].states == suika::pad_states::XInput) {
				return _device_name;
			}
			else {
				return _dname;
			}
		}

		gamepad_stick::gamepad_stick(ulong xcode, ulong dcode, const string& xname, const string& dname, ubyte id) {
			_xcode = xcode;
			_dcode = dcode;
			_device_name = xname;
			_dname = dname;
			_id = id;

			button = gamepad_button(xcode, dcode, xname, dname, id);
		}

		void gamepad_stick::update() {

			if (suika::gamepad::gamepads[_id].states == suika::pad_states::Disable) {
				return;
			}

			if (_is_use_xinput && suika::gamepad::gamepads[_id].states == suika::pad_states::XInput) {
				if (_xcode == XINPUT_GAMEPAD_LEFT_THUMB) {
					_value.x = d3d::XInput::xstate.Gamepad.sThumbLX / 32767.0;
					_value.y = d3d::XInput::xstate.Gamepad.sThumbLY / 32767.0;
				}
				else if(_xcode == XINPUT_GAMEPAD_RIGHT_THUMB) {
					_value.x = d3d::XInput::xstate.Gamepad.sThumbRX / 32767.0;
					_value.y = d3d::XInput::xstate.Gamepad.sThumbRY / 32767.0;
				}
			}
			else {
				if (_dcode == PAD_LSTICK) {
					_value.x = d3d::dinput::gamepad_state[suika::gamepad::gamepads[_id].vid.to_string() + suika::gamepad::gamepads[_id].pid.to_string()].lX / 1000.0;
					_value.y = d3d::dinput::gamepad_state[suika::gamepad::gamepads[_id].vid.to_string() + suika::gamepad::gamepads[_id].pid.to_string()].lY / 1000.0;
				}
				else if (_dcode == PAD_RSTICK) {
					_value.x = d3d::dinput::gamepad_state[suika::gamepad::gamepads[_id].vid.to_string() + suika::gamepad::gamepads[_id].pid.to_string()].lZ /  (double)(SHRT_MAX) - 1.0;
					_value.y = d3d::dinput::gamepad_state[suika::gamepad::gamepads[_id].vid.to_string() + suika::gamepad::gamepads[_id].pid.to_string()].lRz / (double)(SHRT_MAX) - 1.0;
				}
			}
			button.update();
		}

		string gamepad_stick::to_string() const {
			if (_is_use_xinput && suika::gamepad::gamepads[_id].states == suika::pad_states::XInput) {
				return _device_name;
			}
			else {
				return _dname;
			}
		}
	}
}

