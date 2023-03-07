#include "suika.h"
#include "../suika/d3d/dwrite.h"
#include "../suika/d3d/blend.hpp"


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
	fd.font = "メイリオ";
	suika::d3d::dwrite::set(fd, cid);

	auto cb = suika::set_view({ 1280,960 });
	suika::set_cbuffer(sizeof(cb), &cb, 0);
	suika::d3d::blend::blends[suika::blend::alpha].set();
	std::vector<suika::vertex::vertex_2d> vertices = {
		suika::vertex::create_2d(suika::point<float>{64,64}, suika::pallet::red, {0,0}),
		suika::vertex::create_2d(suika::point<float>{480,64}, suika::pallet::yellow, {0,0}),
		suika::vertex::create_2d(suika::point<float>{64,480}, suika::pallet::blue, {0,0}),
		suika::vertex::create_2d(suika::point<float>{480,480}, suika::pallet::green, {0,0}),
	};
	vertices[0].color.a = 127;
	vertices[1].color.a = 127;
	vertices[2].color.a = 127;
	vertices[3].color.a = 127;	

	// 四角形のインデックスを定義
	std::vector<suika::uint16> index =
	{
		0, 1, 2,
		2, 1, 3
	};
	auto update = [&]() {suika::window::flip(); suika::window::clear(); return suika::window::process(); };
	int i = 0;
	while (update()) {
		suika::d3d::dwrite::draw(L"TEST😀", { 128,128 }, cid);
		vertices[0].color.a = i%255;
		vertices[1].color.a = i%255;
		vertices[2].color.a = i%255;
		vertices[3].color.a = i%255;
		suika::vertex::set(vertices, vertices.data(), index, suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		//suika::d3d::blend::blends[suika::blend::alpha].set();
		suika::d3d::pContext->DrawIndexed(6, 0, 0);

		
		i++;
	}
}