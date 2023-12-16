// -----------------------------------------------------------
// 
// binary reader
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
		/// �o�C�i���̓ǂݍ���
		/// </summary>
		class binary_reader {
		private:
			path_type _path;

			std::unique_ptr<FILE, detail::file_deleter> _file;

			void close();
		public:
			/// <summary>
			/// ���[�_�[���쐬
			/// </summary>
			/// <param name="path">�t�@�C���̃p�X</param>
			binary_reader(path_type path);
			binary_reader(const binary_reader&) = delete;
			/// <summary>
			/// ���[�u�R���X�g���N�^
			/// </summary>
			/// <param name=""></param>
			binary_reader(binary_reader&&);
			/// <summary>
			/// �f�X�g���N�^
			/// </summary>
			~binary_reader();

			/// <summary>
			/// �o�C�i����ǂݍ���
			/// </summary>
			/// <param name="size">�ǂݍ��ރT�C�Y</param>
			/// <returns>�ǂݍ��񂾃o�C�i���f�[�^</returns>
			void* read(size_t size);

			/// <summary>
			/// �o�C�i����ǂݍ���
			/// </summary>
			/// <typeparam name="T">�g���r�A���R�s�[�\�ȃf�[�^�^</typeparam>
			/// <returns>�ǂݍ��񂾃f�[�^</returns>
			template<concepts::trivially T>
			T read() {
				return *static_cast<T*>(read(sizeof(T)));
			}
		};
	}
} // namespace suika