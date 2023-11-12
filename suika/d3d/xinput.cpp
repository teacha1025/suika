#include <Windows.h>
#include <Xinput.h>
#include "../../include/suika/type.h"
#include "../../include/suika/def.h"
#include "xinput.h"
#include "dinput.hpp"
#pragma comment (lib, "xinput.lib")

namespace suika {
	namespace d3d{
		namespace xinput {
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

			XINPUT_STATE get_state(ulong index) {
				auto i = convert_index(index);
				if (i == ULONG_MAX) return {};
				init();
				auto er = XInputGetState(i, &xstate);
			}

			void enable(bool flag) {
				XInputEnable(flag);
			}
		}
	}
}