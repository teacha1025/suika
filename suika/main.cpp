#include <Windows.h>
#include "../include/suika/logger.h"
#include "../include/suika/window.h"
#include "../include/suika/shader.h"
#include "../include/suika/color.h"
#include "../include/suika/pallet.h"
#include "../include/suika/vertex.h"

#include "d3d/info.hpp"
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
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	suika::log.init();
	if (!suika::d3d::init()) {
		suika::log.error("d3d error");
		return 0;
	}	

	if (suika::window::create({ 1280,960 }, { 1.0,1.0 }, { 255,255,255 }, "Application") == nullptr) {
		return 0;
	}

	//suika::add_vs(g_vs_main, sizeof(g_vs_main), "shape");
	//suika::add_ps(g_ps_main, sizeof(g_ps_main), "shape");
	suika::add_vs("../suika/d3d/shader/shape.hlsl", "shape");
	suika::add_ps("../suika/d3d/shader/shape.hlsl", "shape");
	suika::set_vs("shape");
	suika::set_ps("shape");

	auto cb = suika::d3d::set_view({ 1280,960 });
	Microsoft::WRL::ComPtr<ID3D11Buffer> cbf;
	if (!suika::d3d::create_cbuffer(cbf.GetAddressOf(), sizeof(cb))) {
		suika::log.error("cb");
		return 0;
	}
	suika::d3d::update_cbuffer(cbf.Get(), &cb, sizeof(cb), 0);
	suika::d3d::set_cbuffer(cbf.GetAddressOf());

	suika::window::background(suika::color(0, 0, 0));
	suika::window::title("APP");

	suika::window::canvas().get()->set();
	
	suika::vertex::vertex_2d vertices[4] = {
		suika::vertex::create_2d(suika::point<float>{64,64}, suika::pallet::red, {0,0}),
		suika::vertex::create_2d(suika::point<float>{480,64}, suika::pallet::yellow, {0,0}),
		suika::vertex::create_2d(suika::point<float>{64,480}, suika::pallet::blue, {0,0}),
		suika::vertex::create_2d(suika::point<float>{480,480}, suika::pallet::green, {0,0}),
	};
	suika::vertex::set_vertex(vertices, sizeof(vertices), sizeof(suika::vertex::vertex_2d));

	// 四角形のインデックスを定義
	WORD index[] =
	{
		0, 1, 2,
		2, 1, 3
	};
	suika::vertex::set_index(index, sizeof(index), suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	auto update = [&]() {suika::window::flip(); suika::window::clear(); return suika::window::process(); };
	while (update()) {
		vertices[0].position.x += 1.0f;
		vertices[1].position.x += 1.0f;
		vertices[2].position.x += 1.0f;
		vertices[3].position.x += 1.0f;
		suika::vertex::set_vertex(vertices, sizeof(vertices), sizeof(suika::vertex::vertex_2d));
		suika::d3d::pContext->DrawIndexed(6, 0, 0);
	}
	suika::log.info("fin");

	return 0;
}