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

#include <unordered_map>
#include <d3d11.h>
#include <wincodec.h>
#include <wrl/client.h>
#include <Windows.h>

#include "texture.hpp"
#include "vertex.h"
#include "info.hpp"

#pragma comment(lib, "windowscodecs.lib")

namespace suika {
    namespace d3d {
        namespace texture {
            Microsoft::WRL::ComPtr<IWICImagingFactory> m_factory;
            Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
            Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
            std::unordered_map<string, texture> texture_list;

            texture* currentTexture;

            texture::texture() {

            }
            
            texture::texture(string path) {
                if(texture_list.find(path) != texture_list.end()) {
					*this = texture_list[path];
					return;
				}
                auto pointer = [&]() {return buffer.empty() ? nullptr : &buffer[0]; };
                this->path = path;
                Microsoft::WRL::ComPtr<IWICFormatConverter> FC;
                pixelBytes = 4u;

                HRESULT er = CoCreateInstance(
                    CLSID_WICImagingFactory,
                    nullptr,
                    CLSCTX_INPROC_SERVER,
                    IID_PPV_ARGS(m_factory.GetAddressOf())
                );
                if (FAILED(er)) {
                    log_d3d.error("Failed to Create Instance");
                    log_d3d.result(er);
                    return;
                }

                er = m_factory->CreateDecoderFromFilename(path.to_wstring().c_str(), 0
                    , GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
                if (FAILED(er)) {
                    log_d3d.error("Failed to Create Decoder");
                    log_d3d.result(er);
                    return;
                }

                er = decoder->GetFrame(0, &frame);
                if (FAILED(er)) {
                    log_d3d.error("Failed to Get Frame");
                    log_d3d.result(er);
                    return;
                }

                size = { 0,0 };
                er = frame->GetSize(&size.x, &size.y);
                if (FAILED(er)) {
                    log_d3d.error("Failed to Get Size");
                    log_d3d.result(er);
                    return;
                }

                if (!(size.x > 0 && size.y > 0)) {
                    return;
                }

                WICPixelFormatGUID pixelFormat;
                er = frame->GetPixelFormat(&pixelFormat);
                if (FAILED(er)) {
                    log_d3d.error("Failed to Get PixelFormat");
                    log_d3d.result(er);
                    return;
                }

                buffer.resize(static_cast<size_t>(size.x) * static_cast<size_t>(size.y) * static_cast<size_t>(pixelBytes));

                if (pixelFormat != GUID_WICPixelFormat32bppRGBA) {
                    er = m_factory->CreateFormatConverter(&FC);
                    if (FAILED(er)) {
                        log_d3d.error("Failed to Create FormatConverter");
                        log_d3d.result(er);
                        return;
                    }

                    er = FC->Initialize(frame.Get(), GUID_WICPixelFormat32bppRGBA
                        , WICBitmapDitherTypeErrorDiffusion
                        , 0, 0, WICBitmapPaletteTypeCustom);
                    if (FAILED(er)) {
                        log_d3d.error("Failed to Initialize WICFactory");
                        log_d3d.result(er);
                        return;
                    }

                    er = FC->CopyPixels(0, size.x * pixelBytes, static_cast<UINT>(buffer.size()), pointer());
                    if (FAILED(er)) {
                        log_d3d.error("Failed to Copy Pixel");
                        log_d3d.result(er);
                        return;
                    }
                }
                else {
                    er = frame->CopyPixels(0, size.x * pixelBytes, static_cast<UINT>(buffer.size()), pointer());
                    if (FAILED(er)) {
                        log_d3d.error("Failed to Copy Pixel");
                        log_d3d.result(er);
                        return;
                    }
                }


                static D3D11_TEXTURE2D_DESC desc;
                desc.Width = size.x;
                desc.Height = size.y;
                desc.MipLevels = 1;
                desc.ArraySize = 1;
                desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                desc.SampleDesc.Count = 1;
                desc.SampleDesc.Quality = 0;
                desc.Usage = D3D11_USAGE_DEFAULT;
                desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                desc.CPUAccessFlags = 0;
                desc.MiscFlags = 0;

                static D3D11_SUBRESOURCE_DATA initData;
                initData.pSysMem = pointer();
                initData.SysMemPitch = size.x * pixelBytes;
                initData.SysMemSlicePitch = static_cast<UINT>(buffer.size());

                er = d3d::pDevice->CreateTexture2D(&desc, &initData, &g_texture);
                if (FAILED(er)) {
                    log_d3d.error("Failed to Create Texture2D");
                    log_d3d.result(er);
                    return;
                }

                static D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
                SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                SRVDesc.Texture2D.MipLevels = 1;

                er = d3d::pDevice->CreateShaderResourceView(g_texture.Get(), &SRVDesc, &g_srv);
                if (FAILED(er)) {
                    log_d3d.error("Failed to Create SRV");
                    log_d3d.result(er);
                    return;
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

                er = d3d::pDevice->CreateSamplerState(&samplerDesc, &g_sampler);
                if (FAILED(er)) {
                    log_d3d.error("Failed to Create SamplerState");
                    log_d3d.result(er);
                    return;
                }

                texture_list.insert({ path, *this });
            }

            void set(const texture& image) {
                if (&image != currentTexture) {
                    vertex::flush();
                }

                d3d::pContext->PSSetShaderResources(0, 1, image.g_srv.GetAddressOf());
                d3d::pContext->PSSetSamplers(0, 1, image.g_sampler.GetAddressOf());
            }

            void fin() {
                frame.Reset();
                decoder.Reset();
                m_factory.Reset();
            }
        }
    }
}
