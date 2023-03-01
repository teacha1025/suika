#include <Windows.h>
#include "../include/suika/logger.h"
#include "../include/suika/window.h"

#include "d3d/device.hpp"
#include "d3d/vs.hpp"
#include "d3d/ps.hpp"
#include "d3d/cbuffer.hpp"

#include "d3d/shader/shape_vs.h"
#include "d3d/shader/shape_ps.h"

extern void init();
extern int main();

namespace suika {
	//logger log;
	struct vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 uv;
	};
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	suika::log.init();
	if (!suika::d3d::init()) {
		suika::log.error("d3d error");
		return 0;
	}
	{
		suika::d3d::vertex_shader vs;
		suika::d3d::pixel_shader ps;
		vs.create(g_vs_main, sizeof(g_vs_main), "shape");
		ps.create(g_ps_main, sizeof(g_ps_main), "shape");
	}
	auto cb = suika::d3d::set_view({1280,960});
	Microsoft::WRL::ComPtr<ID3D11Buffer> cbf;
	if (!suika::d3d::create_cbuffer(cbf.GetAddressOf(), sizeof(cb))) {
		suika::log.error("cb");
		return 0;
	}
	suika::d3d::update_cbuffer(cbf.Get(), &cb, 0);

	if (suika::window::create({ 1280,920 }, { 128,128 }, { 1.0,1.0 }, { 255,255,255 }, "Application") == nullptr) {
		return 0;
	}
	suika::window::background(suika::color(255, 127, 0));
	suika::window::title("APP");


	suika::vertex v[4] = {
		{{128,128,0},{1.0f,1.0f,1.0f,1.0f},{0,0}},
		{{192,128,0},{1.0f,1.0f,1.0f,1.0f},{0,0}},
		{{128,192,0},{1.0f,1.0f,1.0f,1.0f},{0,0}},
		{{192,192,0},{1.0f,1.0f,1.0f,1.0f},{0,0}},
	};


	auto update = [&]() {suika::window::flip(); suika::window::clear(); return suika::window::process(); };
	while (update()) {
		cb = suika::d3d::set_view({ 1280,960 });
		suika::d3d::update_cbuffer(cbf.Get(), &cb, 0);
	}
	suika::log.info("fin");
}