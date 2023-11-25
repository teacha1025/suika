// -----------------------------------------------------------
// 
// mouse.
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

#include "point.h"
#include "window.h"
#include "input_base.h"

namespace suika {
	/// <summary>
	/// �����I�Ȏ���
	/// </summary>
	namespace detail {
		/// <summary>
		/// �}�E�X
		/// </summary>
		class mouse : public input_base {
		public:
			/// <summary>
			/// �}�E�X�L�[�̍쐬
			/// </summary>
			/// <param name="code">�}�E�X�R�[�h</param>
			/// <param name="name">�}�E�X�̖��O</param>
			mouse(unsigned int code, string name);

			/// <summary>
			/// �f�t�H���g����
			/// </summary>
			mouse() {}

			/// <summary>
			/// �}�E�X�̍X�V
			/// </summary>
			void update();
		};
	}
	/// <summary>
	/// �L�[���͂̒�`�y�ъ֐�
	/// </summary>
	namespace mouse {
		/// <summary>
		/// ���{�^��
		/// </summary>
		extern detail::mouse Left;

		/// <summary>
		/// ���{�^��
		/// </summary>
		extern detail::mouse Middle;

		/// <summary>
		/// �E�{�^��
		/// </summary>
		extern detail::mouse Right;

		extern detail::mouse Button4;
		extern detail::mouse Button5;
		extern detail::mouse Button6;
		extern detail::mouse Button7;
		extern detail::mouse Button8;

		/// <summary>
		/// �J�[�\���̎��
		/// </summary>
		enum cursor {
			//! �W��
			icon,
			//! �W��
			arrow,
			//! ��������
			up_arrow,
			//! I�}�[�N
			ibeam,
			//! �\��
			cross,
			//! �l�����w
			hand,
			//! �֎~
			no,
			//! �㉺���
			resize_NS,
			//! ���E���
			resize_WE,
			//! �E��ƍ������
			resize_NWSE,
			//! ����ƉE�����
			resize_NESW,
			//! �\�����
			resize_all,
			//! �w���v
			help,
			//! �s���}�[�N
			pin,
			//! �l
			person,
			//! ���邮��(�����v)
			wait,
			//! ���Ƃ��邮��
			appstarting
		};

		/// <summary>
		/// �}�E�X�J�[�\���̈ʒu���擾
		/// </summary>
		/// <param name="id">�E�B���h�E��ID</param>
		/// <returns>�J�[�\���̈ʒu</returns>
		point<int> position(window::id id = window::default_id);

		/// <summary>
		/// �}�E�X�J�[�\���̈ʒu��ݒ�
		/// </summary>
		/// <param name="p">�ʒu</param>
		/// <param name="id">�E�B���h�EID</param>
		/// <param name="flag">�E�B���h�E���A�N�e�B�u�̎������J�[�\����ݒ肷��</param>
		void position(const point<int>& p, window::id id = window::default_id, bool flag = true);

		/// <summary>
		/// �J�[�\���ړ��ʂ��擾
		/// </summary>
		/// <param name="id">�E�B���h�EID</param>
		/// <returns>�P�t���[���̃J�[�\���ړ���</returns>
		point<int> delta_position(window::id id = window::default_id);

		/// <summary>
		/// �z�C�[����]�ʂ��擾
		/// </summary>
		/// <returns>�P�t���[���̃z�C�[����]��</returns>
		int wheel();

		/// <summary>
		/// �J�[�\���̌����ڂ�ύX����
		/// </summary>
		/// <param name="style">�J�[�\���̎��</param>
		void style(cursor style);
	}
}