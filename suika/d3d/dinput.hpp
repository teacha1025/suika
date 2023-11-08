#pragma once
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>
namespace suika {
	namespace d3d {
		namespace dinput {
			extern BYTE key[256];
			extern DIMOUSESTATE mouse_state;
			void update(bool = true);
		}
	}
}