#pragma once
#include <Windows.h>
#include <Xinput.h>
#include "../../include/suika/type.h"

namespace suika {
	namespace d3d {
		namespace xinput {
			extern XINPUT_STATE xstate;

			XINPUT_STATE get_state(ulong index);

			void enable(bool flag);
		}
	}
}