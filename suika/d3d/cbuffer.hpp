#pragma once
#include <directxmath.h>
#include <d3d11.h>
#include "../../include/suika/point.h"
namespace suika {
	namespace d3d {
		struct cbuffer_0 {
			//DirectX::XMMATRIX world;
			//DirectX::XMMATRIX view;
			//DirectX::XMMATRIX projection;
			DirectX::XMMATRIX mt;
		};

		bool create_cbuffer(ID3D11Buffer** cb, UINT size);
		void set_cbuffer(ID3D11Buffer* const* cb);
		void update_cbuffer(ID3D11Buffer* cb, void* buffer, size_t size, UINT index);
		cbuffer_0 set_view(const point<int>& window_size);
	}
}