#pragma once
#include <dinput.h>
namespace suika {
	namespace d3d {
		namespace dinput {
			extern BYTE key[256];
			extern DIMOUSESTATE2 mouse_state;
			void update(bool = true);
		}
	}
}