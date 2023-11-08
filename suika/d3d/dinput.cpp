#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>
#include "info.hpp"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		namespace dinput {
			ComPtr<IDirectInputDevice8> key_dev;
			ComPtr<IDirectInputDevice8> mouse_dev;
			ComPtr<IDirectInput8> key_input;
			ComPtr<IDirectInput8> mouse_input;
			DIMOUSESTATE mouse_state;
			BYTE key[256];

			bool init(HWND hWnd) {
				auto er = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)(key_input.GetAddressOf()), NULL);
				if (FAILED(er)) {
					log_d3d.error("Failed to create DInput");
					log_d3d.result(er);
					return false;
				}

				er = key_input->CreateDevice(GUID_SysKeyboard, key_dev.GetAddressOf(), NULL);
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

				er = key_dev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
				if (FAILED(er)) {
					log_d3d.error("Failed to SetCooperativeLevel");
					log_d3d.result(er);
					return false;
				}



				er = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)(mouse_input.GetAddressOf()), NULL);
				if (FAILED(er)) {
					log_d3d.error("Failed to create DInput");
					log_d3d.result(er);
					return false;
				}

				er = mouse_input->CreateDevice(GUID_SysMouse, mouse_dev.GetAddressOf(), NULL);
				if (FAILED(er)) {
					log_d3d.error("Failed to create DInputDevice");
					log_d3d.result(er);
					return false;
				}

				er = mouse_dev->SetDataFormat(&c_dfDIMouse);
				if (FAILED(er)) {
					log_d3d.error("Failed to SetDataFormat");
					log_d3d.result(er);
					return false;
				}

				er = mouse_dev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
				if (FAILED(er)) {
					log_d3d.error("Failed to SetCooperativeLevel");
					log_d3d.result(er);
					return false;
				}
				key_dev->Poll();
				key_dev->Acquire();
				mouse_dev->Poll();
				mouse_dev->Acquire();

				log_d3d.info("Create DirectInput Device");
				return true;
			}

			void fin() {
				key_dev->Unacquire();
				mouse_dev->Unacquire();
				log_d3d.info("Finalize DirectInput Device");
				//key_dev->Release();
			}

			void update(bool key_reset) {
				auto er = key_dev->Acquire();
				if (FAILED(er)) {
					if (key_reset && er == DIERR_INPUTLOST) {
						key_dev->Acquire();
					}
					//log_d3d.error("Failed to get key acquire");
					log_d3d.result(er);
					//return;
				}
				er = mouse_dev->Acquire();
				if (FAILED(er)) {
					if (key_reset && er == DIERR_INPUTLOST) {
						mouse_dev->Acquire();
					}
					//log_d3d.error("Failed to get mouse acquire");
					log_d3d.result(er);
					//return;
				}

				er = key_dev->GetDeviceState(256, key);
				if (FAILED(er)) {
					if (key_reset && er == DIERR_INPUTLOST) {
						key_dev->Acquire();
						update(false);
					}
					log_d3d.error("Failed to get key state");
					log_d3d.result(er);
					return;
				}
				er = mouse_dev->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_state);
				if (FAILED(er)) {
					if (key_reset && er == DIERR_INPUTLOST) {
						mouse_dev->Acquire();
						update(false);
					}
					log_d3d.error("Failed to get mouse state");
					log_d3d.result(er);
					return;
				}
			}
		}
	}
}