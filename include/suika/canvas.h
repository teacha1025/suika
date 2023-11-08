#pragma once
#include "color.h"
#include "point.h"

namespace suika {
	struct canvas {
		using canvas_id = uint;
		canvas_id id;
		color bg_color;

		/// <summary>
		/// �L�����o�X���쐬����
		/// </summary>
		/// <param name="size">�L�����o�X�T�C�Y</param>
		/// <param name="top">�g�b�v���W</param>
		/// <param name="hWnd">�E�B���h�EID</param>
		/// <param name="bg">�h��Ԃ��̐F</param>
		canvas(const point<float>& size, const point<float>& top, HWND hWnd, const color& bg);

		/// <summary>
		/// �L�����o�X���N���A����
		/// </summary>
		void clear();

		/// <summary>
		/// �`���̃L�����o�X�ɐݒ肷��
		/// </summary>
		void set();

		/// <summary>
		/// �L�����o�X���E�B���h�E�ɓ]�ʂ���
		/// </summary>
		/// <param name="vsync">�������������邩</param>
		void present(bool vsync = false);
	};

	/// <summary>
	/// �L�����o�X���쐬����
	/// </summary>
	/// <param name="size">�L�����o�X�T�C�Y</param>
	/// <param name="top">�g�b�v���W</param>
	/// <param name="hWnd">�E�B���h�EID</param>
	/// <param name="fillcolor">�h��Ԃ��̐F</param>
	/// <returns>�쐬���ꂽ�L�����o�X</returns>
	std::shared_ptr<canvas> make_canvas(const point<float>& size, const point<float>& top, HWND hWnd, const color& fillcolor);
}