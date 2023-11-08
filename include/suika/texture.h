/**
* @file texture.h
* @brief �e�N�X�`���֌W
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_TEXTURE
#define _SK_TEXTURE
#include "def.h"
#include "base.h"
#include "draw.h"
#include "vertex.h"
#include "point.h"
#include "../../suika/d3d/texture.hpp"

namespace suika {
	/// <summary>
	/// �e�N�X�`���`��Ɋւ���N���X
	/// </summary>
	class texture : public detail::ishape<texture> {
	private:
		point<bool> _turn;
		point<float> _size = { 64,64 };
		string path;
		d3d::texture::texture _tex;
	protected:
		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// �e�N�X�`�����쐬
		/// </summary>
		/// <param name="path">�e�N�X�`���̃p�X</param>
		texture(string path) :path(path) {
			_tex = d3d::texture::texture(path);
			_size = _tex.size;
			_shaders = { TEXTURE_VERTEX, TEXTURE_PIXEL };
		}

		/// <summary>
		/// �e�N�X�`���𔽓]������
		/// </summary>
		/// <param name="turn">�e�����̔��]</param>
		virtual texture turned(const point<bool>& turn)&&;
		/// <summary>
		/// �e�N�X�`���𔽓]������
		/// </summary>
		/// <param name="turn">�e�����̔��]</param>
		virtual texture& turned(const point<bool>& turn)&;

		/// <summary>
		/// �e�N�X�`�����]���擾
		/// </summary>
		/// <param name="turn">�e�����̔��]</param>
		point<bool> turn() const;
		/// <summary>
		/// �e�N�X�`���̑傫�����擾
		/// </summary>
		/// <returns>�e�N�X�`���̑傫��</returns>
		point<float> size() const;
		/// <summary>
		/// �e�N�X�`����`�悷��
		/// </summary>
		virtual void draw() override;
	};
}
#endif