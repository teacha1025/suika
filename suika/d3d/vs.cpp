#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <windows.h>
#include <unordered_map>
#include <wrl/client.h>

#include "../../include/suika/point.h"
#include "info.hpp"
#include "vs.hpp"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		std::unordered_map<std::string, vertex_shader> vertex_shader_list;
		DXGI_FORMAT GetDxgiFormat(D3D_REGISTER_COMPONENT_TYPE type, BYTE mask) {
			if (mask & 0x0F)
			{
				// xyzw
				switch (type)
				{
				case D3D10_REGISTER_COMPONENT_FLOAT32:
					return DXGI_FORMAT_R32G32B32A32_FLOAT;
				
				case D3D10_REGISTER_COMPONENT_UINT32: 
					return DXGI_FORMAT_R32G32B32A32_UINT;
				case D3D10_REGISTER_COMPONENT_SINT32:
					return DXGI_FORMAT_R32G32B32A32_SINT;
				}
			}

			if (mask & 0x07)
			{
				// xyz
				switch (type)
				{
				case D3D10_REGISTER_COMPONENT_FLOAT32:
					return DXGI_FORMAT_R32G32B32_FLOAT;
				case D3D10_REGISTER_COMPONENT_UINT32:
					return DXGI_FORMAT_R32G32B32_UINT;
				case D3D10_REGISTER_COMPONENT_SINT32:
					return DXGI_FORMAT_R32G32B32_SINT;
				}
			}

			if (mask & 0x3)
			{
				// xy
				switch (type)
				{
				case D3D10_REGISTER_COMPONENT_FLOAT32:
					return DXGI_FORMAT_R32G32_FLOAT;
				case D3D10_REGISTER_COMPONENT_UINT32:
					return DXGI_FORMAT_R32G32_UINT;
				case D3D10_REGISTER_COMPONENT_SINT32:
					return DXGI_FORMAT_R32G32_SINT;
				}
			}

			if (mask & 0x1)
			{
				// x
				switch (type)
				{
				case D3D10_REGISTER_COMPONENT_FLOAT32:
					return DXGI_FORMAT_R32_FLOAT;
				case D3D10_REGISTER_COMPONENT_UINT32:
					return DXGI_FORMAT_R32_UINT;
				case D3D10_REGISTER_COMPONENT_SINT32:
					return DXGI_FORMAT_R32_SINT;
				}
			}

			return DXGI_FORMAT_UNKNOWN;
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
		void vertex_shader::create(const string& input, const string& name) {
			ComPtr<ID3DBlob> vblob;
			auto er = CompileShaderFromFile(input.to_wstring().data(), "vs_main", "vs_5_0", &vblob);
			if (FAILED(er)) {
				log_d3d.error("Failed to Compile VertexShader");
				log_d3d.result(er);
				return;
			}
			create(vblob.Get()->GetBufferPointer(), vblob.Get()->GetBufferSize(), name);
		}
		void vertex_shader::create(LPCVOID input, size_t size, const string& name) {
			auto er = pDevice->CreateVertexShader(input, size, nullptr, &pVS);
			ComPtr<ID3D11ShaderReflection> pReflector;
			er = D3DReflect(input, size, IID_ID3D11ShaderReflection, (void**)pReflector.GetAddressOf());
			if (FAILED(er)) {
				log_d3d.error("Failed to Create VertexShader");
				log_d3d.result(er);
				return;
			}

			D3D11_SHADER_DESC shaderdesc;
			pReflector->GetDesc(&shaderdesc);

			// Create InputLayout
			std::vector<D3D11_INPUT_ELEMENT_DESC> vbElement;
			for (UINT i = 0U; i < shaderdesc.InputParameters; ++i) {
				D3D11_SIGNATURE_PARAMETER_DESC sigdesc;
				pReflector->GetInputParameterDesc(i, &sigdesc);

				auto format = GetDxgiFormat(sigdesc.ComponentType, sigdesc.Mask);

				D3D11_INPUT_ELEMENT_DESC eledesc = {
					sigdesc.SemanticName // Semantic–¼
					, sigdesc.SemanticIndex // POSITION0‚Æ‚©‚Ì”ŽšB–³‚¯‚ê‚Î0
					, format // DXGI_FORMAT
					, 0 // Œˆ‚ß‘Å‚¿
					, D3D11_APPEND_ALIGNED_ELEMENT // Œˆ‚ß‘Å‚¿
					, D3D11_INPUT_PER_VERTEX_DATA // Œˆ‚ß‘Å‚¿
					, 0 // Œˆ‚ß‘Å‚¿
				};
				vbElement.push_back(eledesc);
			}

			if (!vbElement.empty()) {
				er = pDevice->CreateInputLayout(&vbElement[0], vbElement.size(),
					input, static_cast<SIZE_T>(size), pIL.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Input Layout");
					log_d3d.result(er);
					return;
				}
			}

			log_d3d.info("Create VS");
		}
		void vertex_shader::set() {
			pContext->IASetInputLayout(pIL.Get());
			pContext->VSSetShader(pVS.Get(), nullptr, 0);
		}

	}
}