#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>
#include <dxgi.h>
#include <wbemidl.h>
#include <oleauto.h>
#include "info.hpp"
#include "dinput.hpp"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;
#define SAFE_RELEASE(p) { if (p != nullptr) { p->Release(); p = nullptr; } }
namespace suika {
	namespace d3d {
		namespace dinput {
			ComPtr<IDirectInputDevice8> key_dev;
			ComPtr<IDirectInputDevice8> mouse_dev;
			std::unordered_map<string, ComPtr<IDirectInputDevice8>> gamepad_dev;
			
			ComPtr<IDirectInput8> key_input;
			ComPtr<IDirectInput8> mouse_input;
			ComPtr<IDirectInput8> gamepad_input;

			DIMOUSESTATE mouse_state;
			BYTE key[256];
			std::unordered_map<string, DIJOYSTATE> gamepad_state;

			std::vector<info> gamepad_list;

			class BString {
			public:
				BSTR    m_bstr;
				BString(const OLECHAR* pStr) { if ((m_bstr = SysAllocString(pStr)) == NULL) throw - 1; }
				~BString() { if (m_bstr != NULL) SysFreeString(m_bstr); }
				operator BSTR& () { return m_bstr; }
			};
			

			info get_pad_info(const GUID* pGuid) {
				info ret;
				BOOL bIsXinput = FALSE;
				IWbemLocator* pIWbemLocator = NULL;
				auto hr = CoCreateInstance(__uuidof(WbemLocator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IWbemLocator), (LPVOID*)&pIWbemLocator);
				if (SUCCEEDED(hr) && pIWbemLocator != NULL) {

					// Connect to WMI
					BString    bstrNamespace(L"\\\\.\\root\\cimv2");
					IWbemServices* pIWbemServices = NULL;
					hr = pIWbemLocator->ConnectServer(bstrNamespace, NULL, NULL, 0L, 0L, NULL, NULL, &pIWbemServices);
					if (SUCCEEDED(hr) && pIWbemServices != NULL) {

						// Switch security level to IMPERSONATE.
						BString bstrClassName(L"Win32_PNPEntity");
						IEnumWbemClassObject* pEnumDevices = NULL;
						CoSetProxyBlanket(pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
						hr = pIWbemServices->CreateInstanceEnum(bstrClassName, 0, NULL, &pEnumDevices);
						if (SUCCEEDED(hr) && pEnumDevices != NULL) {

							DWORD    dwDevIdx, dwReturned;
							DWORD    dwPid, dwVid;
							WCHAR* strVid, * strPid;
							VARIANT var;
							BString bstrDeviceID(L"DeviceID");
							IWbemClassObject* pDevices[20] = { 0 };

							// Loop over all devices
							for (; !bIsXinput;) {

								// Get 20 at a time
								dwDevIdx = dwReturned = 0;
								hr = pEnumDevices->Next(10000, 20, pDevices, &dwReturned);
								if (FAILED(hr) || dwReturned == 0) break;

								for (dwDevIdx = 0; dwDevIdx < dwReturned; dwDevIdx++) {

									// For each device, get its device ID
									hr = pDevices[dwDevIdx]->Get(bstrDeviceID, 0L, &var, NULL, NULL);
									if (SUCCEEDED(hr) && var.vt == VT_BSTR && var.bstrVal != NULL) {

										// Check if the device ID contains "IG_".  If it does, then it's an XInput device
										// This information can not be found from DirectInput
										if (wcsstr(var.bstrVal, L"IG_")) {

											// If it does, then get the VID/PID from var.bstrVal
											dwVid = dwPid = 0;
											strVid = wcsstr(var.bstrVal, L"VID_");
											strPid = wcsstr(var.bstrVal, L"PID_");
											if (strVid && swscanf_s(strVid, L"VID_%4X", &dwVid) != 1) dwVid = 0;
											if (strPid && swscanf_s(strPid, L"PID_%4X", &dwPid) != 1) dwPid = 0;

											// Compare the VID/PID to the DInput device
											if (MAKELONG(dwVid, dwPid) == pGuid->Data1) {
												bIsXinput = TRUE;
												ret.pid = std::format(L"{:04x}", dwPid);
												ret.vid = std::format(L"{:04x}", dwVid);
												ret.states = 2;
												break;
											}
										}
									}
									SAFE_RELEASE(pDevices[dwDevIdx]);
								}
							}

							for (dwDevIdx = 0; dwDevIdx < 20; dwDevIdx++) SAFE_RELEASE(pDevices[dwDevIdx]);
							SAFE_RELEASE(pEnumDevices);
						}
						SAFE_RELEASE(pIWbemServices);
					}
					SAFE_RELEASE(pIWbemLocator);
				}
				return ret;
			}
			BOOL CALLBACK EnumJoysticksCallback(const LPCDIDEVICEINSTANCE  pdidInstance, VOID* pvRef) {
				std::vector<info>* ptr = (std::vector<info>*)pvRef;
				DIDEVICEINSTANCE tmp = *pdidInstance;
				
				auto i = get_pad_info(&(pdidInstance->guidProduct));
				i.guid = pdidInstance->guidProduct;
				i.name = pdidInstance->tszProductName;
				if (i.states != 2) {
					auto pid = pdidInstance->guidProduct.Data1 / 0x10000;
					auto vid = pdidInstance->guidProduct.Data1 % 0x10000;
					i.pid = std::format(L"{:04x}", pid);
					i.vid = std::format(L"{:04x}", vid);
					i.states = 1;
				}
				bool f = false;
				for(auto& gp : *ptr){
					if (gp.guid == i.guid) {
						gp = i;
						f = true;
						break;
					}
				}
				if (!f) {
					ptr->push_back(i);
				}
				return DIENUM_CONTINUE;
			}

			void load_gamepad(HWND hWnd) {
				for (auto& gp : gamepad_list) {
					gp.states = 0;
				}

				auto er = gamepad_input->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, &gamepad_list, DIEDFL_ATTACHEDONLY);
				if (FAILED(er)) {
					log_d3d.error("Failed to Enum XInput Gamepad");
					log_d3d.result(er);
				}
				er = gamepad_input->EnumDevices(DI8DEVTYPE_JOYSTICK, EnumJoysticksCallback, &gamepad_list, DIEDFL_ATTACHEDONLY);
				if (FAILED(er)) {
					log_d3d.error("Failed to Enum DirectInput Gamepad");
					log_d3d.result(er);
				}

				for (const auto& pad : gamepad_list) {
					log_d3d.info(std::format(L"Gamepad({}):{}", pad.states == 0 ? L"利用不可" : pad.states == 1 ? L"DirectInput" : L"XInput", pad.name.to_wstring()));
				}

				for (auto& i : gamepad_list) {
					if (i.states == 1) {
						string key = i.vid.to_string() + i.pid.to_string();
						if (!gamepad_dev.contains(key)) {
							gamepad_dev.insert({ key, {} });
							gamepad_state.insert({ key, {} });
						}
						er = gamepad_input->CreateDevice(i.guid, &(gamepad_dev[key]), NULL);
						if (FAILED(er)) {
							log_d3d.error("Failed to create GamepadInputDevice (" + i.name.to_string() + ")");
							log_d3d.result(er);
							i.states = 0;
							continue;
						}
						er = gamepad_dev[key]->SetDataFormat(&c_dfDIJoystick);
						if (FAILED(er)) {
							log_d3d.error("Failed to SetDataFormat Gamepad (" + i.name.to_string() + ")");
							log_d3d.result(er);
							i.states = 0;
							continue;
						}

						// 軸モードを絶対値モードとして設定
						DIPROPDWORD diprop;
						ZeroMemory(&diprop, sizeof(diprop));
						diprop.diph.dwSize = sizeof(diprop);
						diprop.diph.dwHeaderSize = sizeof(diprop.diph);
						diprop.diph.dwHow = DIPH_DEVICE;
						diprop.diph.dwObj = 0;
						diprop.dwData = DIPROPAXISMODE_ABS;	// 絶対値モードの指定(DIPROPAXISMODE_RELにしたら相対値)

						er = gamepad_dev[key]->SetProperty(DIPROP_AXISMODE, &diprop.diph);
						if (FAILED(er)) {
							log_d3d.error("Failed to SetProperty Axismode Gamepad (" + i.name.to_string() + ")");
							log_d3d.result(er);
							i.states = 0;
							continue;
						}

						// X軸の値の範囲設定
						DIPROPRANGE diprg;
						ZeroMemory(&diprg, sizeof(diprg));
						diprg.diph.dwSize = sizeof(diprg);
						diprg.diph.dwHeaderSize = sizeof(diprg.diph);
						diprg.diph.dwHow = DIPH_BYOFFSET;
						diprg.diph.dwObj = DIJOFS_X;
						diprg.lMin = -1000;
						diprg.lMax = 1000;

						er = gamepad_dev[key]->SetProperty(DIPROP_RANGE, &diprg.diph);
						if (FAILED(er)) {
							log_d3d.error("Failed to SetProperty XRange Gamepad (" + i.name.to_string() + ")");
							log_d3d.result(er);
							i.states = 0;
							continue;
						}

						// Y軸の値の範囲設定
						diprg.diph.dwObj = DIJOFS_Y;
						er = gamepad_dev[key]->SetProperty(DIPROP_RANGE, &diprg.diph);
						if (FAILED(er)) {
							log_d3d.error("Failed to SetProperty YRange Gamepad (" + i.name.to_string() + ")");
							log_d3d.result(er);
							i.states = 0;
							continue;
						}

						er = gamepad_dev[key]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
						if (FAILED(er)) {
							log_d3d.error("Failed to SetCooperativeLevel Gamepad (" + i.name.to_string() + ")");
							log_d3d.result(er);
							i.states = 0;
							continue;
						}

						gamepad_dev[key]->Poll();
						gamepad_dev[key]->Acquire();
					}
				}
			}

			void init_gamepad(HWND hWnd) {
				auto er = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)(gamepad_input.GetAddressOf()), NULL);
				if (FAILED(er)) {
					log_d3d.error("Failed to create GamepadInput");
					log_d3d.result(er);
					return;
				}
				load_gamepad(hWnd);
			}

			bool init(HWND hWnd) {
				auto er = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)(key_input.GetAddressOf()), NULL);
				if (FAILED(er)) {
					log_d3d.error("Failed to create KeyboardInput");
					log_d3d.result(er);
					return false;
				}

				er = key_input->CreateDevice(GUID_SysKeyboard, key_dev.GetAddressOf(), NULL);
				if (FAILED(er)) {
					log_d3d.error("Failed to create KeyboardInputDevice");
					log_d3d.result(er);
					return false;
				}

				er = key_dev->SetDataFormat(&c_dfDIKeyboard);
				if (FAILED(er)) {
					log_d3d.error("Failed to Keyboard SetDataFormat");
					log_d3d.result(er);
					return false;
				}

				er = key_dev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
				if (FAILED(er)) {
					log_d3d.error("Failed to Keyboard SetCooperativeLevel");
					log_d3d.result(er);
					return false;
				}



				er = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)(mouse_input.GetAddressOf()), NULL);
				if (FAILED(er)) {
					log_d3d.error("Failed to create MouseInput");
					log_d3d.result(er);
					return false;
				}

				er = mouse_input->CreateDevice(GUID_SysMouse, mouse_dev.GetAddressOf(), NULL);
				if (FAILED(er)) {
					log_d3d.error("Failed to create MouseInputDevice");
					log_d3d.result(er);
					return false;
				}

				er = mouse_dev->SetDataFormat(&c_dfDIMouse);
				if (FAILED(er)) {
					log_d3d.error("Failed to Mouse SetDataFormat");
					log_d3d.result(er);
					return false;
				}

				er = mouse_dev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
				if (FAILED(er)) {
					log_d3d.error("Failed to Mouse SetCooperativeLevel");
					log_d3d.result(er);
					return false;
				}

				init_gamepad(hWnd);

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
				for(auto& gp : gamepad_dev){
					gp.second->Unacquire();
				}
				//key_dev->Release();
			}

			void update(bool key_reset) {
				//auto er = key_dev->Acquire();
				//if (FAILED(er)) {
				//	if (key_reset && er == DIERR_INPUTLOST) {
				//		key_dev->Acquire();
				//	}
				//	//log_d3d.error("Failed to get key acquire");
				//	//log_d3d.result(er);
				//	//return;
				//}
				//er = mouse_dev->Acquire();
				//if (FAILED(er)) {
				//	if (key_reset && er == DIERR_INPUTLOST) {
				//		mouse_dev->Acquire();
				//	}
				//	//log_d3d.error("Failed to get mouse acquire");
				//	//log_d3d.result(er);
				//	//return;
				//}

				//for (auto& gp : gamepad_dev) {
				//	er = gp.second->Acquire();
				//	if (FAILED(er)) {
				//		if (key_reset && er == DIERR_INPUTLOST) {
				//			gp.second->Acquire();
				//		}
				//		//log_d3d.error("Failed to get mouse acquire");
				//		//log_d3d.result(er);
				//		//return;
				//	}
				//}

				auto er = key_dev->GetDeviceState(256, key);
				if (FAILED(er)) {
					er = key_dev->Acquire();
					if (FAILED(er)) {
						//log_d3d.error("Failed to get keyboard state");
						//log_d3d.result(er);
					}
					key_dev->Poll();
					er = key_dev->GetDeviceState(256, key);
					if (FAILED(er)) {
						//log_d3d.error("Failed to get keyboard state");
						//log_d3d.result(er);
					}
				}
				er = mouse_dev->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_state);
				if (FAILED(er)) {
					er = mouse_dev->Acquire();
					if (FAILED(er)) {
						//log_d3d.error("Failed to get mouse state");
						//log_d3d.result(er);
					}
					mouse_dev->Poll();
					er = mouse_dev->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_state);
					if (FAILED(er)) {
						//log_d3d.error("Failed to get mouse state");
						//log_d3d.result(er);
					}
				}
			}

			bool gp_update(const string& key) {
				auto& dev = gamepad_dev[key];
				auto er =dev->GetDeviceState(sizeof(DIJOYSTATE), &gamepad_state[key]);
				if (FAILED(er)) {
					er = dev->Acquire();
					if (FAILED(er)) {
						//log_d3d.error("Failed to get gamepad state");
						//log_d3d.result(er);
						return false;
					}
					dev->Poll();
					er = dev->GetDeviceState(sizeof(DIJOYSTATE), &gamepad_state[key]);
					if (FAILED(er)) {
						//log_d3d.error("Failed to get gamepad state");
						//log_d3d.result(er);
						return false;
					}
				}
				return true;
			}
		}
	}
}
#undef SAFE_RELEASE