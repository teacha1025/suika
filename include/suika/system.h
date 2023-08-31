/**
* @file system.h
* @brief �V�X�e���֌W
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _SK_SYSTEM
#define _SK_SYSTEM
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
	}
}

#endif