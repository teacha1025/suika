#include "d3d/vs.hpp"
#include "d3d/ps.hpp"
#include "d3d/cbuffer.hpp"
#include "d3d/blend.hpp"
#include "d3d/dwrite.h"
#include "d3d/texture.hpp"
#include "d3d/vertex.h"

#include "../include/suika/shader.h"
#include "../include/suika/texture.h"
#include "../include/suika/vertex.h"
#include "../include/suika/palette.h"

static const std::vector<suika::uint16> index =
{
	0, 1, 2,
	2, 1, 3,
};

namespace suika {
	//std::unordered_map<string,d3d::texture::texture> textures;

	std::vector<suika::vertex::vertex_2d> texture::create_vertex() {
		return {
				vertex::create_2d({0.f,0.f},{0,0,0,0.5f},{_turn.x ? 1 : 0,_turn.y ? 1 : 0}),
				vertex::create_2d({this->_size.x,0.f},{0,0,0,0.5f},{_turn.x ? 0 : 1,_turn.y ? 1 : 0}),
				vertex::create_2d({0.f,this->_size.y},{0,0,0,0.5f},{_turn.x ? 1 : 0,_turn.y ? 0 : 1}),
				vertex::create_2d({this->_size.x,this->_size.y},{0,0,0,0.5f},{_turn.x ? 0 : 1,_turn.y ? 0 : 1}),
		};
	}

	texture& texture::turned(const point<bool>& turn)& {
		_turn = turn;
		return static_cast<texture&>(*this);
	}
	texture texture::turned(const point<bool>& turn)&& {
		_turn = turn;
		return static_cast<texture&&>(std::move(*this));
	}

	point<bool> texture::turn() const {
		return _turn;
	}
	point<float> texture::size() const {
		return _size;
	}

	void texture::draw() {
		d3d::vertex::set_ins_mode(d3d::vertex::ins_type::texture);
		set_vs(this->_shaders.vs);
		set_ps(this->_shaders.ps);
		suika::d3d::blend::blends[_blend].set();
		suika::d3d::vertex::set_index(index, (D3D11_PRIMITIVE_TOPOLOGY)suika::PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		suika::d3d::texture::set(_tex);
		d3d::vertex::set_vertex_instance(create_vertex());
		d3d::vertex::add_index(this->_center, this->_transition - this->_center, this->_rotation, this->_extend, { 0,0,0,0 }, { 0,0 });
	}
}