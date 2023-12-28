// -----------------------------------------------------------
// 
// xinput.
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

#include <typeinfo>
#include <Windows.h>
#include <Xinput.h>

#include "../../include/suika/type.h"
#include "../../include/suika/def.h"
#include "info.hpp"
#include "xinput.h"
#include "dinput.hpp"

#pragma comment (lib, "xinput.lib")

namespace suika {
	namespace d3d{
		namespace XInput {
			XINPUT_STATE xstate;
			XINPUT_VIBRATION xvibration;

			void init() {
				ZeroMemory(&xstate, sizeof(XINPUT_STATE));
				ZeroMemory(&xvibration, sizeof(XINPUT_VIBRATION));
			}

			ulong convert_index(ulong index) {
				ulong i = 0;
				for (const auto& gp : d3d::dinput::gamepad_list) {
					if (gp.states == 2) {
						if (i == index) return i;
						i++;
					}
				}
				return ULONG_MAX;
			}

			bool get_state(ulong index) {
				auto i = index;
				if (i == ULONG_MAX) return false;
				init();
				auto er = XInputGetState(i, &xstate);
				if (er == ERROR_SUCCESS) {
					return true;
				}
				else if (er == ERROR_DEVICE_NOT_CONNECTED) {

				}
				else {

				}
				return false;
			}

			void enable(bool flag) {

			}
		}
	}
}
