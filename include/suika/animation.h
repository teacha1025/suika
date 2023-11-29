// -----------------------------------------------------------
// 
// animation
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
	/// �A�j���[�V�������Đ�����N���X
	/// </summary>
	class animation : public detail::ishape<animation> {
	protected:
		point<bool> _turn;
		point<float> _size = { 64,64 }, _draw_size = { 64,64 }, _region_lt = { 0,0 }, _region_rb = { 1,1 };
		point<uint> _div = { 1,1 };
		std::vector<uint> _pattern;
		std::vector<double> _interval;
		double dt = 0;
		uint _index = 0;
		string _path;

		point<float> _uv_lt = { 0,0 }, _uv_rb = { 1,1 };
		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		/// <summary>
		/// �e�N�X�`�����쐬
		/// </summary>
		/// <param name="_path">�e�N�X�`���̃p�X</param>
		animation(string path, const point<uint>& div);

		/// <summary>
		/// �e�N�X�`�����쐬
		/// </summary>
		/// <param name="_path">�e�N�X�`���̃p�X</param>
		animation(string path, const point<uint>& div, const point<float>& region_lt, const point<float>& region_rb);

		/// <summary>
		/// �e�N�X�`���𔽓]������
		/// </summary>
		/// <param name="turn">�e�����̔��]</param>
		virtual animation turned(const point<bool>& turn)&&;

		/// <summary>
		/// �e�N�X�`���𔽓]������
		/// </summary>
		/// <param name="turn">�e�����̔��]</param>
		virtual animation& turned(const point<bool>& turn)&;

		virtual animation patterned(const std::vector<uint>& pattern, const std::vector<double>& interval)&&;

		virtual animation& patterned(const std::vector<uint>& pattern, const std::vector<double>& interval)&;

		virtual animation patterned(const std::vector<uint>& pattern, double interval = 1)&&;

		virtual animation& patterned(const std::vector<uint>& pattern, double interval = 1)&;

		virtual animation updated(double t)&&;

		virtual animation& updated(double t)&;

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
