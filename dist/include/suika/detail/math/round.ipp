// -----------------------------------------------------------
// 
// math function:round
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
		template<std::floating_point T>
		constexpr inline T round(T x) {
			return static_cast<T>((int64)(x+T(x>T(0)?T(0.5):T(-0.5))));
		}

		template<std::integral T>
		constexpr inline T round(T x) {
			return x;
		}
	} // namespace math
} // namespace suika