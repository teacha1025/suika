// -----------------------------------------------------------
// 
// d3d11 shader:constant buffer.
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