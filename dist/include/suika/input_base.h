// -----------------------------------------------------------
// 
// user input device base class.
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
#include "def.h"
#include "base.h"

namespace suika {
	enum class input_state {
		press,
		release,
		up,
		down
	};

	/// <summary>
	/// デバイス入力
	/// </summary>
	class input_base : public detail::ibase {
	protected:
		unsigned int _code = 0;
		unsigned int _press_count = 0;
		input_state _state = input_state::release;

		string _device_name;
	public:
		/// <summary>
		/// 押された時間の取得
		/// </summary>
		/// <returns>キーやボタンが押されたフレーム数</returns>
		virtual unsigned int count() const {
			return _press_count;
		}

		/// <summary>
		/// 押されているかどうかの取得
		/// </summary>
		/// <returns>押されているかどうか</returns>
		virtual bool press() const {
			return _state == input_state::press || _state == input_state::down;
		}

		/// <summary>
		/// 離されているのかどうかの取得
		/// </summary>
		/// <returns>離されているかどうか</returns>
		virtual bool release() const {
			return _state == input_state::release;
		}

		/// <summary>
		/// 離されたかどうかの取得
		/// </summary>
		/// <returns>離された瞬間かどうか</returns>
		virtual bool up() const {
			return _state == input_state::up;
		}

		/// <summary>
		/// 押されたかどうかの取得
		/// </summary>
		/// <returns>押された瞬間かどうか</returns>
		virtual bool down() const {
			return _state == input_state::down;
		}

		/// <summary>
		/// 名前を取得
		/// </summary>
		/// <returns>キーの名前やマウスのボタンの名前</returns>
		virtual string to_string() const {
			return _device_name;
		}

		virtual void update() = 0;
	};
}