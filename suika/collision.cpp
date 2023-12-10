#include "../include/suika/collision.h"
#include "../include/suika/vector.h"

namespace suika {
	namespace detail {
		bool collision(const point<double>& a, const circle& b) {
			return vector::size_square(a - (b.position() - b.center())) <= b.radius() * b.radius();
		}
		bool collision(const point<double>& a, const line& b) {
			const auto _a = double2(b.B() - b.A());
			const auto _b = a - b.A();
			const auto al = vector::size(_a);
			const auto bl = vector::size(_b);
			const auto ab = al * bl;
			return vector::dot(_a, _b) == ab || al > bl;
		}
		bool collision(const point<double>& a, const rect& b) {
			const auto A = double2(b.top().A());
			const auto B = double2(b.left().A());
			const auto C = double2(b.bottom().A());
			const auto D = double2(b.right().A());
			if (vector::cross(B - A, a - A) < 0 &&
				vector::cross(C - B, a - B) < 0 &&
				vector::cross(D - C, a - C) < 0 &&
				vector::cross(A - D, a - D) < 0) {
				return true;
			}
			return false;
		}
	}
	namespace collision_2d {
		bool collision(const circle& a, const circle& b) {
			return vector::size_square((a.position() - a.center()) - (b.position() - b.center())) <= pow(a.radius() + b.radius(), 2);
		}
		bool collision(const circle& a, const line& b) {
			if (collision(a, b.A()) || collision(a, b.B()))
				return true;
			const auto _a = double2(b.B() - b.A());
			const auto _b = double2((a.position() - a.center()) - b.A());
			const auto _c = double2((a.position() - a.center()) - b.B());
			const auto na = vector::set_length(_a, 1.0);
			const auto sb = vector::dot(na, _b);
			if (abs(sb) <= a.radius()) {
				const auto d1 = vector::dot(_a, _b);
				const auto d2 = vector::dot(_a, _c);
				if (d1 * d2 <= 0.0) {
					return true;
				}
				if (vector::size_square(_b) < pow(a.radius(), 2) ||
					vector::size_square(_c) < pow(a.radius(), 2))
					return true;
			}
			return false;
		}
		bool collision(const circle& a, const rect& b) {
			return collision(a.position() - a.center(), b) ||
				collision(a, b.top()) ||
				collision(a, b.right()) ||
				collision(a, b.bottom()) ||
				collision(a, b.left());
		}
		bool collision(const line& a, const line& b) {
			const auto AB = a.B() - a.A();
			const auto AC = b.A() - a.A();
			const auto AD = b.B() - a.A();
			const auto CA = a.A() - b.A();
			const auto CB = a.B() - b.A();
			const auto CD = b.B() - b.A();
			if (vector::cross(AB, AC) * vector::cross(AB, AD) > 0) {
				return false;
			}
			if (vector::cross(CD, CA) * vector::cross(CD, CB) > 0) {
				return false;
			}
			return true;
		}
		bool collision(const line& a, const rect& b) {
			return collision(b, a.A()) || collision(b, a.B()) ||
				collision(a, b.top()) ||
				collision(a, b.right()) ||
				collision(a, b.left()) ||
				collision(a, b.bottom());
		}
		bool collision(const rect& a, const rect& b) {
			return collision(a, b.top()) ||
				collision(a, b.right()) ||
				collision(a, b.bottom()) ||
				collision(a, b.left()) ||
				collision(b, a.top()) ||
				collision(b, a.right()) ||
				collision(b, a.bottom()) ||
				collision(b, a.left());
		}
		bool collision(const line& a, const circle& b) {
			return collision(b, a);
		}
		bool collision(const rect& a, const circle& b) {
			return collision(b, a);
		}
		bool collision(const rect& a, const line& b) {
			return collision(b, a);
		}
	}
}