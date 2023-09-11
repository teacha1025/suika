#include "suika.h"
#include "../suika/d3d/dwrite.h"
#include "../suika/d3d/blend.hpp"
#include "../suika/d3d/texture.hpp"
#include "../suika/d3d/vertex.h"


void init() {
	suika::window::background(suika::pallet::skyblue);
	suika::window::title("APP");
}

struct f4 {
	float a, b, c, d;
};

int main() {
	auto cid = suika::window::canvas().get()->id;
	suika::d3d::dwrite::init(cid);
	suika::d3d::dwrite::font_data fd;
	fd.Color = suika::pallet::white;
	fd.Color.a = 255;
	fd.fontWeight = DWRITE_FONT_WEIGHT_BOLD;
	fd.fontSize = 64.0f;
	fd.font = "游明朝";
	suika::d3d::dwrite::set(fd, cid);

	auto cb = suika::set_view({ 1280,960 });
	suika::set_cbuffer(sizeof(cb), &cb, 0);
	suika::d3d::blend::blends[suika::blend::alpha].set();

	define w = 32, h = 32;

	auto create_vertex = [](suika::point<float> pos, suika::point<float> size) {
		return std::vector<suika::vertex::vertex_2d> {
			suika::vertex::create_2d(suika::vector2<float>{pos.x, pos.y}, suika::pallet::red, {0,0}),
			suika::vertex::create_2d(suika::vector2<float>{pos.x + size.x, pos.y}, suika::pallet::yellow, {1,0}),
			suika::vertex::create_2d(suika::vector2<float>{pos.x, pos.y + size.y}, suika::pallet::blue, {0,1}),
			suika::vertex::create_2d(suika::vector2<float>{pos.x + size.x, pos.y + size.y}, suika::pallet::green, {1,1}),
		};
	};

	std::vector<suika::vertex::vertex_2d> vertices = create_vertex({ 64,64 }, { w,h });

	// 四角形のインデックスを定義
	std::vector<suika::uint16> index =
	{
		0, 1, 2,
		2, 1, 3,
	};
	suika::d3d::vertex::set_index(index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//auto update = [&]() {suika::window::flip(); suika::window::clear(); return suika::window::process(); };
	int i = 0;

	suika::d3d::texture::texture tex("test.bmp");
#if 1
	suika::set_vs("shape");
	suika::set_ps("shape");
#else
	suika::set_vs("texture");
	suika::set_ps("texture");
#endif
	//suika::texture tex;

	suika::vector3<float> v[32][32];
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 32; y++) {
			v[x][y] = suika::vector3<float>{ x * w, y * h, 0 };
			//suika::d3d::texture::set(tex);
			//suika::d3d::pContext->DrawIndexed(static_cast<UINT>(index.size()), 0, 0);
		}
	}
	//sizeof(suika::vector2<float>);
	//sizeof(f4);
	//sizeof(float);
	while (suika::sys::update()) {
		suika::window::title(std::format("{:4.1f}fps", suika::sys::fps()));
		//suika::d3d::texture::set(tex);
		for (int y = 0; y < 32; y++) {
			for (int x = 0; x < 32; x++) {
				//suika::d3d::vertex::set_vertex_instance(create_vertex({ 0,0 }, { w,h }));
				//suika::d3d::vertex::add_index({ 0,0,0 }, v[x][y], {0,0,0}, {1,1,1});

				suika::rect({w,h}).at(v[x][y]).colored(suika::pallet::white).draw();
			}
		}
		
		//suika::d3d::vertex::flush();
#if 0
		if (i == 60) {
			fd.Color = suika::pallet::yellow;
			fd.Color.a = 255;
			fd.fontWeight = DWRITE_FONT_WEIGHT_LIGHT;
			fd.fontSize = 32.0f;
			fd.font = "游明朝";
			suika::d3d::dwrite::set(fd, cid);
		}
		if (i ==120) {
			i = 0;
			fd.Color = suika::pallet::white;
			fd.Color.a = 255;
			fd.fontWeight = DWRITE_FONT_WEIGHT_BOLD;
			fd.fontSize = 64.0f;
			fd.font = "ＭＳゴシック";
			suika::d3d::dwrite::set(fd, cid);
		}
		suika::d3d::dwrite::draw(L"TEST☺", { 128,128 }, cid);
		i++;
#endif
		
	}
}