#include <d3d11.h>
#include <d3dcompiler.h>
#include <windows.h>
#include <unordered_map>
#include <wrl/client.h>

#include "../../include/suika/point.h"
#include "info.hpp"
#include "ps.hpp"

using namespace Microsoft::WRL;

namespace suika {
    namespace d3d {

        std::unordered_map<std::string, pixel_shader&> pixel_shader_list;
        HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
        void pixel_shader::create(const string& input, const string& name) {
            ComPtr<ID3DBlob> vblob;
            auto er = CompileShaderFromFile(input.to_wstring().data(), "ps_main", "ps_5_0", &vblob);
            if (FAILED(er)) {
                log_d3d.error("Failed to Compile VertexShader");
                log_d3d.result(er);
                return;
            }
            create(vblob.Get()->GetBufferPointer(), vblob.Get()->GetBufferSize(), name);
        }
        void pixel_shader::create(LPCVOID input, size_t size, const string& name) {
            auto er = pDevice->CreatePixelShader(input, size, NULL, pPS.GetAddressOf());
            if (FAILED(er)) {
                log_d3d.error("Failed to Create PixelShader");
                log_d3d.result(er);
                return;
            }
            pixel_shader_list.insert({ name.to_string(), *this});
            log_d3d.info("Create PS");
        }
        void pixel_shader::set() {
            pContext->PSSetShader(pPS.Get(), nullptr, 0);
        }
    }
}