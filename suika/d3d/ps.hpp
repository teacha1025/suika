#pragma once
#include <unordered_map>
#include <d3d11.h>
#include <wrl/client.h>
#include <Windows.h>

#include "../../include/suika/string.h"
namespace suika {
	namespace d3d {
		struct pixel_shader {
			Microsoft::WRL::ComPtr<ID3D11PixelShader> pPS;
			void create(const string& key_input, const string& name);
			void create(LPCVOID key_input, size_t size, const string& name);
			void set();
		};

		extern std::unordered_map<std::string, pixel_shader> pixel_shader_list;
	}
}