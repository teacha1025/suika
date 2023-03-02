#pragma once

#include "string.h"
namespace suika {
	void add_vs(const string& input, const string& name);
	void add_vs(const void* input, size_t size, const string& name);
	void add_ps(const string& input, const string& name);
	void add_ps(const void* input, size_t size, const string& name);

	void set_vs(const string& name);
	void set_ps(const string& name);

}