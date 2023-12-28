// -----------------------------------------------------------
// 
// easing.
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

#include "math.h"

namespace suika {

	/// <summary>
	/// イージング関数群
	/// </summary>
	namespace ease {
		constexpr double in_sine(double t) {
			return 1 - math::cos((t * PI) / 2.0);
		}
		constexpr double out_sine(double t) {
			return math::sin((t * PI) / 2.0);
		}
		constexpr double in_out_sine(double t) {
			return -(math::cos(PI * t) - 1) / 2.0;
		}

		constexpr double in_quad(double t) {
			return t * t;
		}
		constexpr double out_quad(double t) {
			return t * (2 - t);
		}
		constexpr double in_out_quad(double t) {
			return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
		}

		constexpr double in_cubic(double t) {
			return t * t * t;
		}
		constexpr double out_cubic(double t) {
			return 1 - (1 - t) * (1 - t) * (1 - t);
		}
		constexpr double in_out_cubic(double t) {
			return t < 0.5 ? 4 * t * t * t : 1 - math::pow(-2 * t + 2, 3.0) / 2;
		}

		constexpr double in_quart(double t) {
			return t * t * t * t;
		}
		constexpr double out_quart(double t) {
			return 1 - math::pow(1 - t, 4);
		}
		constexpr double in_out_quart(double t) {
			return t < 0.5 ? 8 * t * t * t * t : 1 - math::pow(-2 * t + 2, 4.0) / 2;
		}

		constexpr double in_quint(double t) {
			return t * t * t * t * t;
		}
		constexpr double out_quint(double t) {
			return 1 - math::pow(1 - t, 5.0);
		}
		constexpr double in_out_quint(double t) {
			return t < 0.5 ? 16 * t * t * t * t * t : 1 - math::pow(-2.0 * t + 2, 5.0) / 2;
		}

		constexpr double in_expo(double t) {
			return t == 0 ? 0 : math::pow(2.0, 10 * t - 10);
		}
		constexpr double out_expo(double t) {
			return t == 1 ? 1 : 1 - math::pow(2.0, -10 * t);
		}
		constexpr double in_out_expo(double t) {
			return t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? math::pow(2.0, 20 * t - 10) / 2 : (2 - math::pow(2.0, -20 * t + 10)) / 2;
		}

		constexpr double in_circ(double t) {
			return 1 - math::sqrt(1 - math::pow(t, 2.0));
		}
		constexpr double out_circ(double t) {
			return math::sqrt(1 - math::pow(t - 1, 2.0));
		}
		constexpr double in_out_circ(double t) {
			return t < 0.5 ? (1 - math::sqrt(1 - math::pow(2.0 * t, 2))) / 2 : (math::sqrt(1 - math::pow(-2 * t + 2, 2.0)) + 1) / 2;
		}

		constexpr double in_back(double t) {
			return 2.70158 * t * t * t - 1.70158 * t * t;
		}
		constexpr double out_back(double t) {
			return 1 + 2.70158 * math::pow(t - 1, 3.0) + 1.70158 * math::pow(t - 1, 2.0);
		}
		constexpr double in_out_back(double t) {
			return t < 0.5 ? (math::pow(2 * t, 2.0) * ((2.5949095 + 1) * 2 * t - 2.5949095)) / 2 : (math::pow(2 * t - 2, 2.0) * ((2.5949095 + 1) * (t * 2 - 2) + 2.5949095) + 2) / 2;
		}

		constexpr double in_elastic(double t) {
			return t == 0 ? 0 : t == 1 ? 1 : -math::pow(2.0, 10 * t - 10) * sin((t * 10 - 10.75) * 2.0943951023931955);
		}
		constexpr double out_elastic(double t) {
			return t == 0 ? 0 : t == 1 ? 1 : math::pow(2.0, -10 * t) * sin((t * 10 - 0.75) * 2.0943951023931955) + 1;
		}
		constexpr double in_out_elastic(double t) {
			return t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? -(math::pow(2.0, 20 * t - 10) * sin((20 * t - 11.125) * 1.3962634015954637)) / 2 : (math::pow(2.0, -20 * t + 10) * sin((20 * t - 11.125) * 1.3962634015954637)) / 2 + 1;
		}

		constexpr double out_bounce(double t) {
			if (t < 1 / 2.75) {
				return 7.5625 * t * t;
			}
			if (t < 2 / 2.75) {
				return 7.5625 * (t -= 1.5 / 2.75) * t + 0.75;
			}
			if (t < 2.5 / 2.75) {
				return 7.5625 * (t -= 2.25 / 2.75) * t + 0.9375;
			}
			return 7.5625 * (t -= 2.625 / 2.75) * t + 0.984375;
		}
		constexpr double in_bounce(double t) {
			return 1 - out_bounce(1 - t);
		}
		constexpr double in_out_bounce(double t) {
			return t < 0.5 ? (1 - out_bounce(1 - 2 * t)) / 2 : (1 + out_bounce(2 * t - 1)) / 2;
		}
	}
}
