#include "suika.h"
#include "../suika/d3d/dwrite.h"
#include "../suika/d3d/blend.hpp"
#include "../suika/d3d/texture.hpp"


void init() {
	suika::window::background(suika::pallet::skyblue);
	suika::window::title("APP");
}

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

	define w = 64, h = 64;
	std::vector<suika::vertex::vertex_2d> vertices = {
		suika::vertex::create_2d(suika::vector2<float>{64,64}, suika::pallet::red, {0,0}),
		suika::vertex::create_2d(suika::vector2<float>{64+w,64}, suika::pallet::yellow, {1,0}),
		suika::vertex::create_2d(suika::vector2<float>{64,64+h}, suika::pallet::blue, {0,1}),
		suika::vertex::create_2d(suika::vector2<float>{64+w,64+h}, suika::pallet::green, {1,1}),
	};

	// 四角形のインデックスを定義
	std::vector<suika::uint16> index =
	{
		0, 1, 2,
		2, 1, 3,
	};
	suika::vertex::set_index(index, suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	auto update = [&]() {suika::window::flip(); suika::window::clear(); return suika::window::process(); };
	int i = 0;

	suika::d3d::texture::texture tex("test.bmp");
	suika::set_vs("texture");
	suika::set_ps("texture");

	suika::texture tex;

	while (update()) {
		suika::d3d::dwrite::draw(L"TEST😀", { 128,128 }, cid);
		for (auto& v : vertices) {
			v.color.a = i % 255;
		}
		suika::vertex::set(vertices, index, suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		suika::d3d::texture::set(tex);
		suika::d3d::pContext->DrawIndexed(static_cast<UINT>(index.size()), 0, 0);
		i++;
	}
}