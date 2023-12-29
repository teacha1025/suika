// -----------------------------------------------------------
// 
// suika exception.
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

#include "string.h"

namespace suika {
	/// <summary>
	/// 例外クラス
	/// </summary>
	class exception {
	private:
		string message;

	public:
		/// <summary>
		/// 例外を作成
		/// </summary>
		/// <param name="message">例外のメッセージ</param>
		exception(std::string message) : message(message) {}

		/// <summary>
		/// 例外のメッセージを取得
		/// </summary>
		/// <returns>メッセージ</returns>
		string what() const {
			return message;
		}
	};
}
