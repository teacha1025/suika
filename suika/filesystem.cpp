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

#include <filesystem>

#include "../include/suika/filesystem.h"

namespace suika {
	namespace filesystem {
		bool exists(path_type path) {
			return std::filesystem::exists(path.to_wstring());
		}

		path_type current_path() {
			return string(std::filesystem::current_path());
		}

		std::vector<path_type> enumerate_files(path_type path) {
			std::filesystem::directory_iterator itr(path.to_wstring());
			std::vector<path_type> files;
			for (auto& p : itr) {
				files.push_back(string(p.path().wstring()));
			}
			return files;
		}
	}
}
