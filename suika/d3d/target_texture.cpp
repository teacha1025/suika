// -----------------------------------------------------------
// 
// d3d11 render target view.
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

#include <d3d11.h>
#include <windows.h>
#include <unordered_map>
#include <wrl/client.h>

#include "../../include/suika/point.h"
#include "info.hpp"

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		std::unordered_map<canvas_id, ComPtr<ID3D11Texture2D>> pTargetTexture;
		std::unordered_map<canvas_id, ComPtr<ID3D11SamplerState>> pSamplerState;
		namespace target_texture {
			bool create(const point<float>& size, canvas_id id) {
                pTargetTexture.insert({ id, {} });
                pSamplerState.insert({ id, {} });
                auto& tex = (pTargetTexture[id]);
                auto& sampler = (pSamplerState[id]);

                static D3D11_TEXTURE2D_DESC desc;
                desc.Width = (UINT)size.x;
                desc.Height = (UINT)size.y;
                desc.MipLevels = 1;
                desc.ArraySize = 1;
                desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                desc.SampleDesc.Count = 1;
                desc.SampleDesc.Quality = 0;
                desc.Usage = D3D11_USAGE_DEFAULT;
                desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
                desc.CPUAccessFlags = 0;
                desc.MiscFlags = 0;

                auto er = d3d::pDevice->CreateTexture2D(&desc, nullptr, &tex);
                if (FAILED(er)) {
                    log_d3d.error("Failed to Create Texture2D");
                    log_d3d.result(er);
                    return false;
                }

                static D3D11_SAMPLER_DESC samplerDesc;
                samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
                samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
                samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
                samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
                samplerDesc.MipLODBias = 0.0f;
                samplerDesc.MaxAnisotropy = 1;
                samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
                samplerDesc.BorderColor[0] = 0;
                samplerDesc.BorderColor[1] = 0;
                samplerDesc.BorderColor[2] = 0;
                samplerDesc.BorderColor[3] = 0;
                samplerDesc.MinLOD = 0;
                samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

                er = d3d::pDevice->CreateSamplerState(&samplerDesc, &sampler);
                if (FAILED(er)) {
                    log_d3d.error("Failed to Create SamplerState");
                    log_d3d.result(er);
                    return false;
                }

				log_d3d.info("Create TargetTexture");
				return true;
			}
		}
	}
}
