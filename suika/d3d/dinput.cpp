#include <dinput.h>
#include "info.hpp"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		namespace dinput {
			ComPtr<IDirectInputDevice8> key_dev;
			ComPtr<IDirectInput8> input;
			BYTE key[256];

			bool init(HWND hWnd) {
				auto er = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)(input.GetAddressOf()), NULL);
				if (FAILED(er)) {
					log_d3d.error("Failed to create DInput");
					log_d3d.result(er);
					return false;
				}

				er = input->CreateDevice(GUID_SysKeyboard, key_dev.GetAddressOf(), NULL);
				if (FAILED(er)) {
					log_d3d.error("Failed to create DInputDevice");
					log_d3d.result(er);
					return false;
				}

				er = key_dev->SetDataFormat(&c_dfDIKeyboard);
				if (FAILED(er)) {
					log_d3d.error("Failed to SetDataFormat");
					log_d3d.result(er);
					return false;
				}

				er = key_dev->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
				if (FAILED(er)) {
					log_d3d.error("Failed to SetCooperativeLevel");
					log_d3d.result(er);
					return false;
				}

				key_dev->Acquire();
			}

			void fin() {
				//key_dev->Unacquire();
				//key_dev->Release();
			}

			void update(bool key_reset) {
				auto er = key_dev->GetDeviceState(256, key);
				if (FAILED(er)) {
					if (key_reset && er == DIERR_INPUTLOST) {
						key_dev->Acquire();
						update(false);
					}
					log_d3d.error("Failed to get key state");
					log_d3d.result(er);
					return;
				}
			}
		}
	}
}