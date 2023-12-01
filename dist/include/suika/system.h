// -----------------------------------------------------------
// 
// system
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

#include <chrono>

#include "string.h"

namespace suika {
	namespace sys {
		/// <summary>
		/// �t���[�����X�V����
		/// </summary>
		/// <returns></returns>
		bool update();

		/// <summary>
		/// ���t���[���Ńv���O�������I������
		/// </summary>
		void exit();

		/// <summary>
		/// �v���O�������w�莞�Ԓ�~����
		/// </summary>
		/// <param name="t">��~����</param>
		/// <remarks>�v���O�������ׂĂ̏�������~���܂��B</remarks>
		void sleep(std::chrono::nanoseconds t);

		/// <summary>
		/// �v���O�������w��܂Ŏ��Ԓ�~����
		/// </summary>
		/// <param name="t">�ĊJ����</param>
		/// <remarks>�v���O�������ׂĂ̏�������~���܂��B</remarks>
		void wait(std::chrono::system_clock::time_point t);

		/// <summary>
		/// �t���[�����[�g���擾
		/// </summary>
		/// <returns>���݂̃t���[�����[�g</returns>
		float fps();

		/// <summary>
		/// �O�̃t���[������̌o�ߎ��Ԃ��擾
		/// </summary>
		/// <returns>�o�ߎ���(�b)</returns>
		double delta();

		/// <summary>
		/// �O�̃t���[������̌o�ߎ��Ԃ��擾
		/// </summary>
		/// <returns>�o�ߎ���(�i�m�b)</returns>
		long long delta_nano();
	}
}
