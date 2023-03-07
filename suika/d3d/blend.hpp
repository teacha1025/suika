#pragma once
#include <unordered_map>
#include <d3d11.h>
#include <wrl/client.h>
#include <Windows.h>

#include "../../include/suika/string.h"
namespace suika {
	enum class blend;
	namespace d3d {
		namespace blend {
			struct blend_state {
				Microsoft::WRL::ComPtr<ID3D11BlendState> state;
				void create(D3D11_BLEND_DESC desc, suika::blend id);
				void set();
			};
			void init();
			extern std::unordered_map<suika::blend, blend_state> blends;
		}
	}
}