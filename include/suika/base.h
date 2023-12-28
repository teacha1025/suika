// -----------------------------------------------------------
// 
// base class.
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

#include <string>

#include "def.h"
#include "string.h"

namespace suika {
	/// <summary>
	/// 内部的な実装
	/// </summary>
	namespace detail {
	/// <summary>
	/// 全クラスのベースクラス
	/// </summary>
		class ibase {
		public:
			constexpr ibase() {}

			string to_string() const {};
		};
	} // namespace detail
} // namespace suika
