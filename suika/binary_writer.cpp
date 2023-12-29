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
#define _CRT_SECURE_NO_WARNINGS
#include <filesystem>

#include "../include/suika/binary_writer.h"
#include "../include/suika/filesystem.h"

namespace suika {
	namespace filesystem {
		void binary_writer::close() {
			if (_file != nullptr) {
				fclose(_file.get());
				_file.reset();
			}
		}

		binary_writer::binary_writer(path_type path) {
			_path = path;

			_file.reset(fopen(path.to_string().c_str(), "wb"));
		}

		binary_writer::binary_writer(binary_writer&& a) {
			a.close();
			_path = a._path;
			_file.reset(fopen(_path.to_string().c_str(), "wb"));
		}

		binary_writer::~binary_writer() {
			close();
		}

		void binary_writer::write(void* source, size_t size) {
			fwrite(source, size, 1, _file.get());
		}
	}
}
