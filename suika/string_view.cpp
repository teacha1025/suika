// -----------------------------------------------------------
// 
// string_view
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

#include <string>
#include <string_view>
#include <array>
#include <Windows.h>

#include "../include/suika/def.h"
#include "../include/suika/string_view.h"
#include "../include/suika/codecvt.h"
#include "../include/suika/except.h"

namespace suika {
	string_view::str string_view::to_string() const {
		return suika::to_string(_str);
	}

	string_view::wstr string_view::to_wstring() const {
		return suika::to_wstring(_str);
	}

	string_view::utf8 string_view::to_u8string() const {
		return suika::to_u8string(_str);
	}

	string_view::utf16 string_view::to_u16string() const {
		return suika::to_u16string(_str);
	}

	string_view::utf32 string_view::to_u32string() const {
		return suika::to_u32string(_str);
	}
}
