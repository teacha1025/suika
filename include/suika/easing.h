#pragma once
#include "math.h"

namespace suika {
	namespace ease {
		double in_sine(double t);
		double out_sine(double t);
		double in_out_sine(double t);

		double in_quad(double t);
		double out_quad(double t);
		double in_out_quad(double t);

		double in_cubic(double t);
		double out_cubic(double t);
		double in_out_cubic(double t);

		double in_quart(double t);
		double out_quart(double t);
		double in_out_quart(double t);

		double in_quint(double t);
		double out_quint(double t);
		double in_out_quint(double t);

		double in_expo(double t);
		double out_expo(double t);
		double in_out_expo(double t);

		double in_circ(double t);
		double out_circ(double t);
		double in_out_circ(double t);

		double in_back(double t);
		double out_back(double t);
		double in_out_back(double t);

		double in_elastic(double t);
		double out_elastic(double t);
		double in_out_elastic(double t);

		double out_bounce(double t);
		double in_bounce(double t);
		double in_out_bounce(double t);
	}
}