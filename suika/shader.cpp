// -----------------------------------------------------------
// 
// shader
// 
// Copyright 2023 teacha1025
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// -----------------------------------------------------------

#include "../suika/d3d/vs.hpp"
#include "../suika/d3d/ps.hpp"
#include "d3d/vertex.h"
#include "../include/suika/string.h"
#include "../include/suika/shader.h"
namespace suika {
	void add_vs(const string& key_input, const string& name) {
		d3d::vertex_shader_list.insert({ name.to_string(), {} });
		d3d::vertex_shader_list.at(name.to_string()).create(key_input, name);
	}

	void add_vs(const void* key_input, size_t size, const string& name) {
		d3d::vertex_shader_list.insert({ name.to_string(), {} });
		d3d::vertex_shader_list.at(name.to_string()).create(key_input, size, name);
	}

	void add_ps(const string& key_input, const string& name) {
		d3d::pixel_shader_list.insert({ name.to_string(), {} });
		d3d::pixel_shader_list.at(name.to_string()).create(key_input, name);
	}

	void add_ps(const void* key_input, size_t size, const string& name) {
		d3d::pixel_shader_list.insert({ name.to_string(), {} });
		d3d::pixel_shader_list.at(name.to_string()).create(key_input, size, name);
	}

	void set_vs(const string& name) {
		static string vs = "";
		if (vs != name) {
			d3d::vertex::flush();
			d3d::vertex_shader_list.at(name.to_string()).set();
			vs = name;
		}
	}

	void set_ps(const string& name) {
		static string ps = "";
		if (ps != name) {
			d3d::vertex::flush();
			d3d::pixel_shader_list.at(name.to_string()).set();
			ps = name;
		}
	}
}
