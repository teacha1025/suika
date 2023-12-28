// -----------------------------------------------------------
// 
// d3d11 texture.
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
#include <d3d11.h>
#include <wrl/client.h>
#include <Windows.h>

#include "../../include/suika/string.h"
#include "../../include/suika/point.h"
namespace suika {
	namespace d3d {
        namespace texture {
            struct texture {
                std::vector<unsigned char> buffer;
                point<uint> size;
                uint pixelBytes = 0;
                string path;

                Microsoft::WRL::ComPtr<ID3D11Texture2D> g_texture;
                Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> g_srv;
                Microsoft::WRL::ComPtr<ID3D11SamplerState> g_sampler;

                texture();
                texture(string path);
            };

            void set(const texture& texture);

            extern texture* currentTexture;
        }
	}
}
