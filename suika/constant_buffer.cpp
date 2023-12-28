// -----------------------------------------------------------
// 
// constant buffer
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
#include <directxmath.h>
#include <wrl/client.h>

#include "../include/suika/cbuffer.h"
#include "d3d/cbuffer.hpp"
#include "d3d/info.hpp"

namespace suika {
	cbuffer_default set_view(const point<int>& window_size) {
		auto p = (DirectX::XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(window_size.x), static_cast<float>(window_size.y), 0.0f, 0.0f, 1.0f));

		auto m = DirectX::XMMatrixTranspose(p);
		cbuffer_default b{};

		for (int i = 0; i < 4; i++) {
			b.mt.at(i,0) = m.r[i].m128_f32[0];
			b.mt.at(i,1) = m.r[i].m128_f32[1];
			b.mt.at(i,2) = m.r[i].m128_f32[2];
			b.mt.at(i,3) = m.r[i].m128_f32[3];
		}
		return { b };
	}

	std::unordered_map<uint, Microsoft::WRL::ComPtr<ID3D11Buffer>> cbuffers;
	void set_cbuffer(uint constant_size, void* constant, uint index) {
		if (!cbuffers.contains(index)) {
			cbuffers.insert({ index,{} });
			auto& cb = cbuffers[index];
			if (!d3d::cbuffer::create(cb.GetAddressOf(), constant_size)) {
				cbuffers.erase(index);
				d3d::log_d3d.error("Failed to Create CBuffer");
				return;
			}
		}
		auto& cb = cbuffers[index];

		d3d::cbuffer::update(cb.Get(), constant, sizeof(cb), index);
		d3d::cbuffer::set(cb.GetAddressOf());
	}
}
