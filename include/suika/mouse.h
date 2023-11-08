#pragma once
#include "point.h"
#include "window.h"
#include "input_base.h"

namespace suika {
	namespace detail {
		class _mouse : public input_base {
		public:
			_mouse(unsigned int code, string name);
			_mouse() {}
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
		extern detail::_mouse Left;

		/// <summary>
		/// ���{�^��
		/// </summary>
		extern detail::_mouse Middle;

		/// <summary>
		/// �E�{�^��
		/// </summary>
		extern detail::_mouse Right;

		extern detail::_mouse Button4;
		extern detail::_mouse Button5;
		extern detail::_mouse Button6;
		extern detail::_mouse Button7;
		extern detail::_mouse Button8;

		/// <summary>
		/// �}�E�X�J�[�\���̈ʒu���擾
		/// </summary>
		/// <returns>�J�[�\���̈ʒu</returns>
		point<int> position(window::id id = window::default_id);

		/// <summary>
		/// �}�E�X�J�[�\���̈ʒu��ݒ�
		/// </summary>
		/// <param name="p">�J�[�\���̈ʒu</param>
		void position(const point<int>& p);

		point<int> delta_position(window::id id = window::default_id);

		int wheel();
	}
}