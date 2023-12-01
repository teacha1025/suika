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
#include "rect.h"

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
		bool _is_loop = true, _is_finished = false;

		point<float> _uv_lt = { 0,0 }, _uv_rb = { 1,1 };
		virtual std::vector<suika::vertex::vertex_2d> create_vertex() override;
	public:
		animation() = default;

		/// <summary>
		/// �e�N�X�`�����쐬
		/// </summary>
		/// <param name="path">�e�N�X�`���̃p�X</param>
		/// <param name="div">������</param>
		animation(string path, const point<uint>& div);

		/// <summary>
		/// �e�N�X�`�����쐬
		/// </summary>
		/// <param name="path">�e�N�X�`���̃p�X</param>
		/// <param name="div">������</param>
		/// <param name="region_lt">�e�N�X�`���̗̈�̍���</param>
		/// <param name="region_rb">�e�N�X�`���̗̈�̉E��</param>
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

		/// <summary>
		/// �A�j���[�V�����̃p�^�[����ݒ肷��
		/// </summary>
		/// <param name="pattern">�p�^�[���̎������z��</param>
		/// <param name="interval">�؂�ւ��̊Ԋu���������z��</param>
		/// <param name="loop">�A�j���[�V�������J��Ԃ���</param>
		virtual animation patterned(const std::vector<uint>& pattern, const std::vector<double>& interval, bool loop = true)&&;

		/// <summary>
		/// �A�j���[�V�����̃p�^�[����ݒ肷��
		/// </summary>
		/// <param name="pattern">�p�^�[���̎������z��</param>
		/// <param name="interval">�؂�ւ��̊Ԋu���������z��</param>
		/// <param name="loop">�A�j���[�V�������J��Ԃ���</param>
		virtual animation& patterned(const std::vector<uint>& pattern, const std::vector<double>& interval, bool loop = true)&;

		/// <summary>
		/// �A�j���[�V�����̃p�^�[����ݒ肷��
		/// </summary>
		/// <param name="pattern">�p�^�[���̎������z��</param>
		/// <param name="interval">�؂�ւ��̊Ԋu</param>
		/// <param name="loop">�A�j���[�V�������J��Ԃ���</param>
		virtual animation patterned(const std::vector<uint>& pattern, double interval = 1, bool loop = true)&&;

		/// <summary>
		/// �A�j���[�V�����̃p�^�[����ݒ肷��
		/// </summary>
		/// <param name="pattern">�p�^�[���̎������z��</param>
		/// <param name="interval">�؂�ւ��̊Ԋu</param>
		/// <param name="loop">�A�j���[�V�������J��Ԃ���</param>
		virtual animation& patterned(const std::vector<uint>& pattern, double interval = 1, bool loop = true)&;

		/// <summary>
		/// �A�j���[�V�������X�V����
		/// </summary>
		/// <param name="t">�ω�����</param>
		virtual void updated(double t);

		/// <summary>
		/// �A�j���[�V�����̃C���f�b�N�X��ݒ肷��
		/// </summary>
		/// <param name="index">�C���f�b�N�X</param>
		virtual void indexed(uint index);

		/// <summary>
		/// �Đ����̃A�j���[�V�����̃C���f�b�N�X���擾
		/// </summary>
		/// <returns>�C���f�b�N�X</returns>
		virtual uint index() const;

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
		/// �A�j���[�V�����̍Đ����I���������擾
		/// </summary>
		/// <returns>�A�j���[�V�����̍Đ����I��������</returns>
		bool finished() const;

		/// <summary>
		/// �e�N�X�`���̗̈��������`���擾����
		/// </summary>
		/// <returns>�e�N�X�`���̗̈��������`</returns>
		rect rect() const;

		/// <summary>
		/// �e�N�X�`����`�悷��
		/// </summary>
		virtual void draw() override;
	};
}
