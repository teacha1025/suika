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
	namespace filesystem {
		
		class binary_writer {
		private:
			path_type _path;

			std::unique_ptr<FILE, detail::file_deleter> _file;

			void close();
		public:
			binary_writer(path_type path);
			binary_writer(const binary_writer&) = delete;
			binary_writer(binary_writer&&);
			~binary_writer();

			void write(void* source, size_t size);

			template<concepts::trivially T>
			void write(T source) {
				write(&source, sizeof(T));
			}
		};
	}
} // namespace suika