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

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <windows.h>
#include <unordered_map>
#include <wrl/client.h>

#include "../../include/suika/point.h"
#include "../../include/suika/string.h"
#include "info.hpp"
#include "vs.hpp"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		std::unordered_map<std::string, vertex_shader> vertex_shader_list;
		static std::pair<DXGI_FORMAT, ULONGLONG> GetDxgiFormat(D3D_REGISTER_COMPONENT_TYPE type, BYTE mask) {
			if (mask & 0x08)
			{
				switch (type)
				{
				case D3D10_REGISTER_COMPONENT_FLOAT32:
					return { DXGI_FORMAT_R32G32B32A32_FLOAT,sizeof(FLOAT) * 4 };
				
				case D3D10_REGISTER_COMPONENT_UINT32: 
					return { DXGI_FORMAT_R32G32B32A32_UINT,sizeof(UINT) * 4 };
				case D3D10_REGISTER_COMPONENT_SINT32:
					return { DXGI_FORMAT_R32G32B32A32_SINT,sizeof(INT) * 4 };
				}
			}

			if (mask & 0x04)
			{
				switch (type)
				{
				case D3D10_REGISTER_COMPONENT_FLOAT32:
					return { DXGI_FORMAT_R32G32B32_FLOAT ,sizeof(FLOAT) * 3 };
				case D3D10_REGISTER_COMPONENT_UINT32:
					return { DXGI_FORMAT_R32G32B32_UINT ,sizeof(UINT) * 3 };
				case D3D10_REGISTER_COMPONENT_SINT32:
					return { DXGI_FORMAT_R32G32B32_SINT ,sizeof(INT) * 3 };
				}
			}

			if (mask & 0x02)
			{
				switch (type)
				{
				case D3D10_REGISTER_COMPONENT_FLOAT32:
					return { DXGI_FORMAT_R32G32_FLOAT ,sizeof(FLOAT) * 2 };
				case D3D10_REGISTER_COMPONENT_UINT32:
					return { DXGI_FORMAT_R32G32_UINT ,sizeof(UINT) * 2 };
				case D3D10_REGISTER_COMPONENT_SINT32:
					return { DXGI_FORMAT_R32G32_SINT,sizeof(INT) * 2 };
				}
			}

			if (mask & 0x01)
			{
				switch (type)
				{
				case D3D10_REGISTER_COMPONENT_FLOAT32:
					return { DXGI_FORMAT_R32_FLOAT,sizeof(FLOAT) * 1 };
				case D3D10_REGISTER_COMPONENT_UINT32:
					return { DXGI_FORMAT_R32_UINT ,sizeof(UINT) * 1 };
				case D3D10_REGISTER_COMPONENT_SINT32:
					return { DXGI_FORMAT_R32_SINT ,sizeof(INT) * 1 };
				}
			}

				return { DXGI_FORMAT_UNKNOWN,  D3D11_APPEND_ALIGNED_ELEMENT };
		}
		HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) {
			HRESULT hr = S_OK;

			DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
			dwShaderFlags |= D3DCOMPILE_DEBUG;

			dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

			ID3DBlob* pErrorBlob = nullptr;
			hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
				dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
			if (FAILED(hr)) {
				if (pErrorBlob) {
					OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
					pErrorBlob->Release();
				}
				return hr;
			}
			if (pErrorBlob) pErrorBlob->Release();

			return S_OK;
		}
		void vertex_shader::create(const string& key_input, const string& name) {
			ComPtr<ID3DBlob> vblob;
			auto er = CompileShaderFromFile(key_input.to_wstring().data(), "vs_main", "vs_5_0", &vblob);
			if (FAILED(er)) {
				log_d3d.error("Failed to Compile VertexShader");
				log_d3d.result(er);
				return;
			}
			create(vblob.Get()->GetBufferPointer(), vblob.Get()->GetBufferSize(), name);
		}
		void vertex_shader::create(LPCVOID key_input, size_t size, const string& name) {
			auto er = pDevice->CreateVertexShader(key_input, size, nullptr, &pVS);
			ComPtr<ID3D11ShaderReflection> pReflector;
			er = D3DReflect(key_input, size, IID_ID3D11ShaderReflection, (void**)pReflector.GetAddressOf());
			if (FAILED(er)) {
				log_d3d.error("Failed to Create VertexShader");
				log_d3d.result(er);
				return;
			}

			D3D11_SHADER_DESC shaderdesc;
			pReflector->GetDesc(&shaderdesc);

			std::vector<D3D11_INPUT_ELEMENT_DESC> vbElement;
			UINT offset[3] = { 0 };
			for (UINT i = 0U; i < shaderdesc.InputParameters; ++i) {
				D3D11_SIGNATURE_PARAMETER_DESC sigdesc;
				pReflector->GetInputParameterDesc(i, &sigdesc);

				auto [format, size] = GetDxgiFormat(sigdesc.ComponentType, sigdesc.Mask);
				D3D11_INPUT_ELEMENT_DESC eledesc;
				if (std::string(sigdesc.SemanticName) == ("SV_InstanceID")) {
					continue;
				}
				if (std::string(sigdesc.SemanticName).starts_with("INS0")) {
					eledesc = {
						.SemanticName = sigdesc.SemanticName
						, .SemanticIndex = sigdesc.SemanticIndex
						, .Format = format
						, .InputSlot = 1
						, .AlignedByteOffset = /*sigdesc.SemanticIndex * size */(offset[1])
						, .InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA
						, .InstanceDataStepRate = 1
					};
					offset[1] += (UINT)size;
				}
				else if (std::string(sigdesc.SemanticName).starts_with("INS1")) {
					eledesc = {
						.SemanticName = sigdesc.SemanticName
						, .SemanticIndex = sigdesc.SemanticIndex
						, .Format = format
						, .InputSlot = 2
						, .AlignedByteOffset = /*sigdesc.SemanticIndex * size */(offset[2])
						, .InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA
						, .InstanceDataStepRate = 1
					};
					offset[2] += (UINT)size;
				}
				else {

					eledesc = {
						.SemanticName = sigdesc.SemanticName
						, .SemanticIndex = sigdesc.SemanticIndex
						, .Format = format
						, .InputSlot = 0
						, .AlignedByteOffset = offset[0]
						, .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA
						, .InstanceDataStepRate = 0
					};
					offset[0] += (UINT)size;
				}
				vbElement.push_back(eledesc);
			}

			if (!vbElement.empty()) {
				er = pDevice->CreateInputLayout(&vbElement[0], static_cast<UINT>(vbElement.size()),
					key_input, static_cast<SIZE_T>(size), pIL.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Input Layout");
					log_d3d.result(er);
					return;
				}
			}

			log_d3d.info("Create VS");
		}
		void vertex_shader::set() const {
			pContext->IASetInputLayout(pIL.Get());
			pContext->VSSetShader(pVS.Get(), nullptr, 0);
		}

	}
}
