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
#define _CRT_SECURE_NO_WARNINGS
#include <filesystem>

#include "../include/suika/binary_reader.h"
#include "../include/suika/filesystem.h"

namespace suika {
	namespace filesystem {
		void binary_reader::close() {
			if (_file != nullptr) {
				fclose(_file.get());
				_file.reset();
			}
		}

		binary_reader::binary_reader(path_type path) {
			_path = path;

			_file.reset(fopen(path.to_string().c_str(), "rb"));
		}

		binary_reader::binary_reader(binary_reader&& a) {
			a.close();
			_path = a._path;
			_file.reset(fopen(_path.to_string().c_str(), "rb"));
		}

		binary_reader::~binary_reader() {
			close();
		}

		void* binary_reader::read(size_t size) {
			void* buffer = malloc(size);
			fread(buffer, size, 1, _file.get());
			return buffer;
		}
	}
}
