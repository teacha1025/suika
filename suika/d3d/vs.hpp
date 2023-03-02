#pragma once
#include <unordered_map>
#include <d3d11.h>
#include <wrl/client.h>
#include <Windows.h>

#include "../../include/suika/string.h"
namespace suika {
	namespace d3d {
		struct vertex_shader {
			Microsoft::WRL::ComPtr<ID3D11VertexShader> pVS;
			Microsoft::WRL::ComPtr<ID3D11InputLayout> pIL;
			void create(const string& input, const string& name);
			void create(LPCVOID input, size_t size, const string& name);
			void set();
		};

		extern std::unordered_map<std::string, vertex_shader&> vertex_shader_list;
	}
}