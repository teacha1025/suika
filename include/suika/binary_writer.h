// -----------------------------------------------------------
// 
// binary writer
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
#include <fstream>

#include "def.h"
#include "concepts.h"
#include "string.h"
#include "filesystem.h"

namespace suika {
	/// <summary>
/// �t�@�C������Ɋւ���֐��A�N���X�Q
/// </summary>
	namespace filesystem {
		/// <summary>
		/// �o�C�i���f�[�^�̏�����
		/// </summary>
		class binary_writer {
		private:
			path_type _path;

			std::unique_ptr<FILE, detail::file_deleter> _file;

			void close();
		public:
			/// <summary>
			/// ���C�^�[���쐬
			/// </summary>
			/// <param name="path">�������ރt�@�C���̃p�X</param>
			binary_writer(path_type path);
			binary_writer(const binary_writer&) = delete;

			/// <summary>
			///	���[�u�R���X�g���N�^
			/// </summary>
			/// <param name="writer">���[�u��</param>
			binary_writer(binary_writer&& writer);

			/// <summary>
			/// �f�X�g���N�^
			/// </summary>
			~binary_writer();

			/// <summary>
			/// �o�C�i������������
			/// </summary>
			/// <param name="source">�������ރf�[�^�ւ̃|�C���^</param>
			/// <param name="size">�������ރT�C�Y</param>
			void write(void* source, size_t size);

			/// <summary>
			/// �o�C�i������������
			/// </summary>
			/// <typeparam name="T">�g���r�A���R�s�[�\�ȃf�[�^�^</typeparam>
			/// <param name="source">�������ރf�[�^</param>
			template<concepts::trivially T>
			void write(T source) {
				write(&source, sizeof(T));
			}
		};
	}
} // namespace suika