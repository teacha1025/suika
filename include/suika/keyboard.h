#pragma once
#include "input_base.h"

namespace suika {
	class _key : public input_base {
	public:
		_key(unsigned int Code, string name);
		_key() {}
		void update();
	};
}