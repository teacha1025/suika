#include <unordered_map>
#include <d3d11.h>
#include <directxmath.h>
#include <wrl/client.h>
#include "../include/suika/cbuffer.h"
#include "d3d/cbuffer.hpp"
#include "d3d/info.hpp"

namespace suika {
	cbuffer_default set_view(const point<int>& window_size) {
		auto p = DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(window_size.x), static_cast<float>(window_size.y), 0.0f, 0.0f, 1.0f));

		auto m = DirectX::XMMatrixTranspose(p);
		cbuffer_default b{};
		for (int i = 0; i < 4; i++) {
			b.mt.m[i][0] = m.r[i].m128_f32[0];
			b.mt.m[i][1] = m.r[i].m128_f32[1];
			b.mt.m[i][2] = m.r[i].m128_f32[2];
			b.mt.m[i][3] = m.r[i].m128_f32[3];
		}
		return { b };
	}

	std::unordered_map<uint, Microsoft::WRL::ComPtr<ID3D11Buffer>> cbuffers;
	void set_cbuffer(uint constant_size, void* constant, uint index) {
		if (!cbuffers.contains(index)) {
			cbuffers.insert({ index,{} });
			auto& cb = cbuffers[index];
			if (!d3d::create_cbuffer(cb.GetAddressOf(), constant_size)) {
				cbuffers.erase(index);
				d3d::log_d3d.error("Failed to Create CBuffer");
				return;
			}
		}
		auto& cb = cbuffers[index];

		d3d::update_cbuffer(cb.Get(), constant, sizeof(cb), index);
		d3d::set_cbuffer(cb.GetAddressOf());
	}
}