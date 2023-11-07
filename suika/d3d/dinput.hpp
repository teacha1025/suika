#pragma once
#include <dinput.h>
namespace suika {
	namespace d3d {
		namespace dinput {
			extern BYTE key[256];
			void update(bool = true);
		}
	}
}