#include "d3d/vs.hpp"
#include "d3d/ps.hpp"
#include "d3d/cbuffer.hpp"
#include "d3d/blend.hpp"
#include "d3d/dwrite.h"
#include "d3d/texture.hpp"

#include "d3d/shader/shape_vs.h"
#include "d3d/shader/shape_ps.h"

#include "../include/suika/texture.h"
#include "../include/suika/vertex.h"
#include "../include/suika/pallet.h"

namespace suika {
	//std::unordered_map<string,d3d::texture::texture> textures;

	texture& texture::turned(const point<bool>& turn)& {
		_turn = turn;
		return static_cast<texture&>(*this);
	}
	texture texture::turned(const point<bool>& turn)&& {
		_turn = turn;
		return static_cast<texture&&>(std::move(*this));
	}

	void texture::draw() {
		/*std::vector<vertex::vertex_2d> vertices = {
			vertex::create_2d(suika::vector2<float>{x,y}, pallet::black, {0,0}),
			vertex::create_2d(suika::vector2<float>{x + w,y}, pallet::black, {1,0}),
			vertex::create_2d(suika::vector2<float>{x,y + h}, pallet::black, {0,1}),
			vertex::create_2d(suika::vector2<float>{x + w,y + h}, pallet::black, {1,1}),
		};
		suika::vertex::set(vertices, index, suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		suika::d3d::texture::set(tex);
		suika::d3d::pContext->DrawIndexed(static_cast<UINT>(index.size()), 0, 0);*/
	}
}