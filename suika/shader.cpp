#include "../suika/d3d/vs.hpp"
#include "../suika/d3d/ps.hpp"
#include "../include/suika/string.h"
#include "../include/suika/shader.h"
namespace suika {
	void add_vs(const string& input, const string& name) {
		d3d::vertex_shader_list.insert({ name.to_string(), {} });
		d3d::vertex_shader_list.at(name.to_string()).create(input, name);
	}
	void add_vs(const void* input, size_t size, const string& name) {
		d3d::vertex_shader_list.insert({ name.to_string(), {} });
		d3d::vertex_shader_list.at(name.to_string()).create(input, size, name);
	}
	void add_ps(const string& input, const string& name) {
		d3d::pixel_shader_list.insert({ name.to_string(), {} });
		d3d::pixel_shader_list.at(name.to_string()).create(input, name);
	}
	void add_ps(const void* input, size_t size, const string& name) {
		d3d::pixel_shader_list.insert({ name.to_string(), {} });
		d3d::pixel_shader_list.at(name.to_string()).create(input, size, name);
	}

	void set_vs(const string& name) {
		d3d::vertex_shader_list.at(name.to_string()).set();
	}
	void set_ps(const string& name) {
		d3d::pixel_shader_list.at(name.to_string()).set();
	}

	
}