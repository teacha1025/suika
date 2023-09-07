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
                uint pixelBytes;
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