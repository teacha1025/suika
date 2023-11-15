#include "d3d/xinput.h"
#include "d3d/dinput.hpp"
#include "../include/suika/gamepad.h"
#include "../include/suika/logger.h"



namespace suika {
	namespace gamepad {
		//std::vector<info> gamepads;
		std::unordered_map<ubyte,info> gamepads;
		std::array<detail::gamepad, MAX_JOYPAD_NUM> pad;

		void load_gamepads() {
            gamepads.reserve(suika::d3d::dinput::gamepad_list.size());
			for (ubyte i = 0; i < suika::d3d::dinput::gamepad_list.size(); i++) {
				auto d = info{
					.index = i,
					.states = suika::d3d::dinput::gamepad_list[i].states == 0 ? pad_states::disable : suika::d3d::dinput::gamepad_list[i].states == 1 ? pad_states::direct_input : pad_states::xinput,
					.name = suika::d3d::dinput::gamepad_list[i].name,
					.pid = suika::d3d::dinput::gamepad_list[i].pid,
					.vid = suika::d3d::dinput::gamepad_list[i].vid,
				};
				//gamepads.push_back(d);
				gamepads[i] = d;
				log.info(std::format(L"Gamepad{}({}):{}", d.index, d.states == pad_states::disable ? L"—˜—p•s‰Â" : d.states == pad_states::direct_input ? L"DirectInput" : L"XInput", d.name.to_wstring()));
			}
		}
		void init() {
			suika::gamepad::load_gamepads();
			for (ubyte i = 0; i < suika::gamepad::gamepads.size(); i++) {
				init(suika::gamepad::pad[i], i, suika::gamepad::gamepads[i]);
			}
		}
		void update() {
			for (ubyte i = 0; i < suika::gamepad::gamepads.size(); i++) {
				update(suika::gamepad::pad[i]);
			}
		}
	}
	namespace detail {
		define PAD_A = 0;
		define PAD_B = 1;
		define PAD_X = 2;
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

		

		

		//TODO:gamepads‚ðvector‚©‚çmap‚É•Ï‚¦‚é
		void init(gamepad& gp, ubyte id, suika::gamepad::info info) {
			gp.A = gamepad_button(XINPUT_GAMEPAD_A, PAD_A, "A", "Button 01", id);
			gp.B = gamepad_button(XINPUT_GAMEPAD_B, PAD_A, "B", "Button 02", id);
			gp.X = gamepad_button(XINPUT_GAMEPAD_X, PAD_A, "X", "Button 03", id);
			gp.Y = gamepad_button(XINPUT_GAMEPAD_Y, PAD_A, "Y", "Button 04", id);

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

			gp._states = info.states;
			gp.ID = id;
			gp._name = info.name;
		}
		void update(gamepad& gp) {
			auto state = d3d::xinput::get_state(gp.ID);
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

		gamepad_button::gamepad_button(ubyte xcode, ubyte dcode, const string& xname, const string& dname, ubyte id) {
			_code = xcode;
			_dcode = dcode;
			_device_name = xname;
			_dname = dname;
			_id = id;
		}

		void gamepad_button::update() {
			if (suika::gamepad::gamepads[_id].states == suika::pad_states::disable) {
				return;
			}
			if (_is_use_xinput && suika::gamepad::gamepads[_id].states == suika::pad_states::xinput) {
				auto tmp = _press_count;

				if (d3d::xinput::xstate.Gamepad.wButtons & _code) {
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
				if (d3d::dinput::gamepad_state[suika::gamepad::gamepads[_id].vid.to_string() + suika::gamepad::gamepads[_id].pid.to_string()].rgbButtons[_dcode] & 0x80) {
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

		gamepad_trigger::gamepad_trigger(ubyte xcode, ubyte dcode, const string& xname, const string& dname, ubyte id) {
			_code = xcode;
			_dcode = dcode;
			_device_name = xname;
			_dname = dname;
			_id = id;

			_button = gamepad_button(xcode, dcode, xname, dname, id);
		}

		void gamepad_trigger::update() {
			
			if (suika::gamepad::gamepads[_id].states == suika::pad_states::disable) {
				return;
			}
			
			if (_is_use_xinput && suika::gamepad::gamepads[_id].states == suika::pad_states::xinput) {
				define TRIGGER_MAX = 255.0;
				auto t = d3d::xinput::xstate.Gamepad.bLeftTrigger / TRIGGER_MAX;
				_value =  (t < _deadzone) ? 0 : t;
			}
			else {
				define TRIGGER_MAX = 1000.0;
				_button.update();
			}
		}

		gamepad_stick::gamepad_stick(ubyte xcode, ubyte dcode, const string& xname, const string& dname, ubyte id) {
			_code = xcode;
			_dcode = dcode;
			_device_name = xname;
			_dname = dname;
			_id = id;
		}

		void gamepad_stick::update() {

			if (suika::gamepad::gamepads[_id].states == suika::pad_states::disable) {
				return;
			}

			if (_is_use_xinput && suika::gamepad::gamepads[_id].states == suika::pad_states::xinput) {

			}
			else {

			}
		}
	}
}

