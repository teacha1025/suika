#pragma once
#include <directxmath.h>
#include <d3d11.h>
#include "../../include/suika/point.h"
namespace suika {
	namespace d3d {
		namespace cbuffer {
			bool create(ID3D11Buffer** cb, UINT size);
			void set(ID3D11Buffer* const* cb);
			void update(ID3D11Buffer* cb, void* buffer, size_t size, UINT index);
		}
	}
}