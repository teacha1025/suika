#pragma once
#include "def.h"
#include "string.h"
namespace suika {
	const string SHAPE_VERTEX = "shape";
	const string SHAPE_PIXEL  = "shape";
	const string TEXTURE_VERTEX = "texture";
	const string TEXTURE_PIXEL  = "texture";

	void add_vs(const string& input, const string& name);
	void add_vs(const void* input, size_t size, const string& name);
	void add_ps(const string& input, const string& name);
	void add_ps(const void* input, size_t size, const string& name);

	void set_vs(const string& name);
	void set_ps(const string& name);

}