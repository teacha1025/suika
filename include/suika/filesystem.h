// -----------------------------------------------------------
// 
// filesystem
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

#include <memory>
#include <vector>

#include "def.h"
#include "string.h"

namespace suika {
	namespace detail {
		struct file_deleter {
			void operator()(FILE* file) const noexcept {
				if (file != nullptr)
					fclose(file);
			}
		};
	}

	/// <summary>
	/// �t�@�C������Ɋւ���֐��A�N���X�Q
	/// </summary>
	namespace filesystem {
		/// <summary>
		/// �G���R�[�h�̎��
		/// </summary>
		enum class encode {
			//! Shift-JIS�����R�[�h(cp932)
			shift_jis,
			//! UTF-8(BOM����)
			utf8,
			//! UTF16(LE)
			utf16,
			//utf32,
		};

		enum class new_line {
			//! CRLF
			crlf,
			//! LF
			lf,
			//! CR
			cr,
		};

		/// <summary>
		/// �t�@�C�������݂��邩���擾
		/// </summary>
		/// <param name="path">�t�@�C���̃p�X</param>
		/// <returns>���݂��邩�ǂ���</returns>
		bool exists(path_type path);

		/// <summary>
		/// ���݂̃f�B���N�g�����擾
		/// </summary>
		/// <returns>���s�t�@�C��������f�B���N�g���ւ̃p�X</returns>
		path_type current_path();

		/// <summary>
		/// �f�B���N�g�����̗v�f��񋓂���
		/// </summary>
		/// <param name="path">�f�B���N�g���̃p�X</param>
		/// <returns>�f�B���N�g�����̃t�@�C���A�t�H���_��</returns>
		std::vector<path_type> enumerate_files(path_type path);
	}
} // namespace suika