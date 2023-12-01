// -----------------------------------------------------------
// 
// canvas.
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
		void clear() const;

		/// <summary>
		/// �`���̃L�����o�X�ɐݒ肷��
		/// </summary>
		void set() const;

		/// <summary>
		/// �L�����o�X���E�B���h�E�ɓ]�ʂ���
		/// </summary>
		/// <param name="vsync">�������������邩</param>
		void present(bool vsync = false) const;
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