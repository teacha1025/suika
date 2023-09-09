#pragma once

#include "string.h"

namespace suika {
	class exception {
	private:
		string message;

	public:
		exception(std::string message) : message(message) {}

		string what() const {
			return message;
		}
	};
}