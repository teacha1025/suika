#include <d3d11.h>
#include <wrl/client.h>

#include "../../include/suika/blend.h"
#include "blend.hpp"
#include "info.hpp"

using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		namespace blend {
			std::unordered_map<suika::blend, blend_state> blends;

			void blend_state::create(D3D11_BLEND_DESC desc, suika::blend id) {
				pDevice->CreateBlendState(&desc, &state);
			}
			void blend_state::set() {
				static const FLOAT factor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
				pContext->OMSetBlendState(state.Get(), factor, 0xffffffff);
			}

			void init() {
				using b = suika::blend;
				b id;
				D3D11_BLEND_DESC blendDesc;
				ZeroMemory(&blendDesc, sizeof(blendDesc));
				blendDesc.AlphaToCoverageEnable = FALSE;
				blendDesc.IndependentBlendEnable = FALSE;
				blendDesc.RenderTarget[0].BlendEnable = TRUE;
				{
					id = b::none;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					
					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::alpha;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::add;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					
					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::sub;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::mul;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::dest;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::inv_dest;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::inv_src;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_INV_SRC_COLOR;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::pma_alpha;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_ALPHA;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::pma_add;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::pma_sub;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
				{
					id = b::pma_inv_src;

					blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_INV_SRC_COLOR;
					blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
					blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
					blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					blends.insert({ id, {} });
					blends[id].create(blendDesc, id);
				}
			}
		}
	}
}