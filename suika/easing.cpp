#include <cmath>
#include "../include/suika/def.h"
//#include "../include/suika/math.h"

namespace suika {
	namespace ease {
		define c1 = 1.70158;
		define c2 = c1 * 1.525;
		define c3 = c1 + 1;
		define c4 = (2 * PI) / 3;
		define c5 = (2 * PI) / 4.5;
		define n1 = 7.5625;
		define d1 = 2.75;
		double in_sine(double t) {
			return 1 - cos((t * PI) / 2.0);
		}
		double out_sine(double t) {
			return sin((t * PI) / 2.0);
		}
		double in_out_sine(double t) {
			return -(cos(PI * t) - 1) / 2.0;
		}

		double in_quad(double t) {
			return t * t;
		}
		double out_quad(double t) {
			return t * (2 - t);
		}
		double in_out_quad(double t) {
			return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
		}

		double in_cubic(double t) {
			return t * t * t;
		}
		double out_cubic(double t) {
			return 1 - (1 - t) * (1 - t) * (1 - t);
		}
		double in_out_cubic(double t) {
			return t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3.0) / 2;
		}

		double in_quart(double t) {
			return t * t * t * t;
		}
		double out_quart(double t) {
			return 1 - pow(1 - t, 4);
		}
		double in_out_quart(double t) {
			return t < 0.5 ? 8 * t * t * t * t : 1 - pow(-2 * t + 2, 4.0) / 2;
		}

		double in_quint(double t) {
			return t * t * t * t * t;
		}
		double out_quint(double t) {
			return 1 - pow(1 - t, 5.0);
		}
		double in_out_quint(double t) {
			return t < 0.5 ? 16 * t * t * t * t * t : 1 - pow(-2.0 * t + 2, 5.0) / 2;
		}

		double in_expo(double t) {
			return t == 0 ? 0 : pow(2.0, 10 * t - 10);
		}
		double out_expo(double t) {
			return t == 1 ? 1 : 1 - pow(2.0, -10 * t);
		}
		double in_out_expo(double t) {
			return t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? pow(2.0, 20 * t - 10) / 2 : (2 - pow(2.0, -20 * t + 10)) / 2;
		}

		double in_circ(double t) {
			return 1 - sqrt(1 - pow(t, 2.0));
		}
		double out_circ(double t) {
			return sqrt(1 - pow(t - 1, 2.0));
		}
		double in_out_circ(double t) {
			return t < 0.5 ? (1 - sqrt(1 - pow(2.0 * t, 2))) / 2 : (sqrt(1 - pow(-2 * t + 2, 2.0)) + 1) / 2;
		}

		double in_back(double t) {
			return c3 * t * t * t - c1 * t * t;
		}
		double out_back(double t) {
			return 1 + c3 * pow(t - 1, 3.0) + c1 * pow(t - 1, 2.0);
		}
		double in_out_back(double t) {
			return t < 0.5 ? (pow(2 * t, 2.0) * ((c2 + 1) * 2 * t - c2)) / 2 : (pow(2 * t - 2, 2.0) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2;
		}

		double in_elastic(double t) {
			return t == 0 ? 0 : t == 1 ? 1 : -pow(2.0, 10 * t - 10) * sin((t * 10 - 10.75) * c4);
		}
		double out_elastic(double t) {
			return t == 0 ? 0 : t == 1 ? 1 : pow(2.0, -10 * t) * sin((t * 10 - 0.75) * c4) + 1;
		}
		double in_out_elastic(double t) {
			return t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? -(pow(2.0, 20 * t - 10) * sin((20 * t - 11.125) * c5)) / 2 : (pow(2, -20 * t + 10) * sin((20 * t - 11.125) * c5)) / 2 + 1;
		}


		double out_bounce(double t) {
			if (t < 1 / d1) {
				return n1 * t * t;
			}
			if (t < 2 / d1) {
				return n1 * (t -= 1.5 / d1) * t + 0.75;
			}
			if (t < 2.5 / d1) {
				return n1 * (t -= 2.25 / d1) * t + 0.9375;
			}
			return n1 * (t -= 2.625 / d1) * t + 0.984375;
		}
		double in_bounce(double t) {
			return 1 - out_bounce(1 - t);
		}
		double in_out_bounce(double t) {
			return t < 0.5 ? (1 - out_bounce(1 - 2 * t)) / 2 : (1 + out_bounce(2 * t - 1)) / 2;
		}
	}
}