// -----------------------------------------------------------
// 
// direct input.
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
				int		states = 0;//0:Disable 1:dinput 2:XInput
				string pid, vid;
				GUID guid = {};
				string	name;
			};

			extern std::vector<info> gamepad_list;
			extern BYTE key[256];
			extern DIMOUSESTATE mouse_state;
			extern std::unordered_map<string, DIJOYSTATE> gamepad_state;
			void update(bool = true);
			bool gp_update(const string& key);

			void load_gamepad(HWND hWnd);
		}
	}
}
