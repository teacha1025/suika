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
				//auto i = convert_index(index);
				auto i = index;
				if (i == ULONG_MAX) return false;
				init();
				auto er = XInputGetState(i, &xstate);
				if (er == ERROR_SUCCESS) {
					//XInputGetState(i, &xstate);
					return true;
				}
				else if (er == ERROR_DEVICE_NOT_CONNECTED) {
					//log_d3d.error(std::format(L"XInputGetState({}) failed:Device Not Connected", i));
				}
				else {
					//log_d3d.error(std::format(L"XInputGetState({}) failed:{}", i, er));
				}
				return false;
			}

			void enable(bool flag) {
				//XInputEnable(flag);
			}
		}
	}
}