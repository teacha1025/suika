// -----------------------------------------------------------
// 
// d3d11 shader:vertex shader.
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


#pragma once
#include <unordered_map>
#include <xmemory>
#include <d3d11.h>
#include <wrl/client.h>
#include <Windows.h>

#include "../../include/suika/string.h"
namespace suika {
	namespace d3d {
		struct vertex_shader {
			Microsoft::WRL::ComPtr<ID3D11VertexShader> pVS;
			Microsoft::WRL::ComPtr<ID3D11InputLayout> pIL;
			void create(const string& key_input, const string& name);
			void create(LPCVOID key_input, size_t size, const string& name);
			void set() const;
		};

		extern std::unordered_map<std::string, vertex_shader> vertex_shader_list;
	}
}
