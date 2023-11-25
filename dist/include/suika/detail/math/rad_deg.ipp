// -----------------------------------------------------------
// 
// math function:abs
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

#include "../../def.h"
#include "../../concepts.h"

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace {

}
namespace suika {
	namespace math {
		template<concepts::numbers T>
		constexpr double radian(T x) {
			return x * PI / 180.0;
		}

		template<concepts::numbers T>
		constexpr double degree(T x) {
			return x * 180.0 / PI;
		}
	} // namespace math
} // namespace suika