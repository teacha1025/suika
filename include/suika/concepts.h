// -----------------------------------------------------------
// 
// template concept.
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

#include <concepts>

#include "def.h"
#include "base.h"

namespace suika {
	namespace concepts {
		/// <summary>
		/// ベースクラスを継承しているか
		/// </summary>
		template<class T>
		concept is_based =
			requires(T t) {
			t.to_string();
		};

		/// <summary>
		/// 数値型
		/// </summary>
		template<typename T>
		concept numbers = std::is_arithmetic_v<T>;

		/// <summary>
		/// 文字列型
		/// </summary>
		template<class T>
		concept string = std::is_convertible_v<T, std::string_view>;

		/// <summary>
		/// トリビアルコピー可能
		/// </summary>
		template <class Type>
		concept trivially = std::is_trivially_copyable_v<Type>;

		/// <summary>
		/// 列挙型
		/// </summary>
		template<class T>
		concept enum_elements = std::is_enum_v<T>;
	}
}
