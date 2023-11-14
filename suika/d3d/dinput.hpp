#pragma once
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>
#include <vector>
#include <unordered_map>
#include "../../include/suika/def.h"
#include "../../include/suika/type.h"
#include "../../include/suika/string.h"
namespace suika {
	namespace d3d {
		namespace dinput {
			struct info {
				ubyte	index = 255;
				int		states = 0;//0:disable 1:dinput 2:xinput
				string pid, vid;
				GUID guid;
				string	name;
			};

			extern std::vector<info> gamepad_list;
			extern BYTE key[256];
			extern DIMOUSESTATE mouse_state;
			extern std::unordered_map<string, DIJOYSTATE> gamepad_state;
			void update(bool = true);
		}
	}
}