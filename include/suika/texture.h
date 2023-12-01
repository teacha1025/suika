// -----------------------------------------------------------
// 
// texture
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

#pragma once

#include "def.h"
#include "base.h"
#include "draw.h"
#include "vertex.h"
#include "point.h"

namespace suika {
	/// <summary>
	/// �e�N�X�`���`��Ɋւ���N���X
	/// </summary>
	class texture : public detail::ishape<texture> {
	protected:
		point<bool> _turn;
		point<float> _size = { 64,64 }, _draw_size = { 64,64 };
		string _path;

		point<float> _uv_lt = { 0,0 }, _uv_rb = { 1,1 };
		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// �e�N�X�`�����쐬
		/// </summary>
		/// <param name="path">�e�N�X�`���̃p�X</param>
		texture(string path);

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
		/// �e�N�X�`����UV���W��ݒ肷��
		/// </summary>
		/// <param name="lt">����</param>
		/// <param name="rb">�E��</param>
		virtual texture uv(const point<float>& lt, const point<float>& rb)&&;

		/// <summary>
		/// �e�N�X�`����UV���W��ݒ肷��
		/// </summary>
		/// <param name="lt">����</param>
		/// <param name="rb">�E��</param>
		virtual texture& uv(const point<float>& lt, const point<float>& rb)&;

		/// <summary>
		/// �e�N�X�`�����]���擾
		/// </summary>
		/// <returns>�e�����̔��]</returns>
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
