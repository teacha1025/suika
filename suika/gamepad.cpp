#include "d3d/dinput.hpp"
#include "../include/suika/gamepad.h"
#include "../include/suika/logger.h"



namespace suika {
	namespace gamepad {
		std::vector<info> gamepads;

		

		void load_gamepads() {
            std::vector<info> gamepads(suika::d3d::dinput::gamepad_list.size());
			for (ubyte i = 0; i < suika::d3d::dinput::gamepad_list.size(); i++) {
				auto d = info{
					.index = i,
					.states = suika::d3d::dinput::gamepad_list[i].states == 0 ? pad_states::disable : suika::d3d::dinput::gamepad_list[i].states == 1 ? pad_states::direct_input : pad_states::xinput,
					.name = suika::d3d::dinput::gamepad_list[i].name,
					.pid = suika::d3d::dinput::gamepad_list[i].pid,
					.vid = suika::d3d::dinput::gamepad_list[i].vid,
				};
				gamepads.push_back(d);
				log.info(std::format(L"Gamepad{}({}):{}", d.index, d.states == pad_states::disable ? L"—˜—p•s‰Â" : d.states == pad_states::direct_input ? L"DirectInput" : L"XInput", d.name.to_wstring()));
			}
		}
	}
}

