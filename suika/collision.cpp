#include "../include/suika/collision.h"
#include "../include/suika/vector.h"

namespace suika {
	namespace detail {
		bool collision(const point<double>& a, const circle& b) {
			return vector::size_square(a - (b.position() - b.offset())) <= pow(b.radius()*b.extend().x, 2);
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
			if(a.extend().x == a.extend().y && b.extend().x == b.extend().y)
				return vector::size_square((a.position() - a.offset()) - (b.position() - b.offset())) <= pow((a.radius()*a.extend().x) + (b.radius() * b.extend().x), 2);
			else {
				const auto _a = double2(a.position() - a.offset());
				const auto _b = double2(b.position() - b.offset());
				const auto _c = _a - _b;
				const auto _d = vector::set_length(_c, 1.0);
				const auto _e = vector::set_length(_d, a.radius());
				const auto _f = vector::set_length(_d, b.radius());
				const auto _g = _b + _e;
				const auto _h = _a - _f;
				return vector::size_square(_g - _h) <= pow(a.radius() + b.radius(), 2);
			}
		}
		bool collision(const circle& a, const line& b) {
			if (collision(a, b.A()) || collision(a, b.B()))
				return true;
			const auto c = double2(a.position() - a.offset());
			const auto r = a.radius() * a.extend().x;
			const auto _a = double2(b.B() - b.A());
			const auto _b = double2((a.position() - a.offset()) - b.A());
			const auto _c = double2((a.position() - a.offset()) - b.B());
			const auto na = vector::set_length(_a, 1.0);
			const auto sb = vector::cross( _b, na);
			if (abs(sb) <= r) {
				if (vector::dot(_a, _b) * vector::dot(_a, _c) <= 0.0) {
					return true;
				}
				if (vector::size_square(_b) < pow(r, 2) ||
					vector::size_square(_c) < pow(r, 2))
					return true;
			}
			return false;
		}
		bool collision(const circle& a, const rect& b) {
			return collision(a.position() - a.offset(), b) ||
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
			if (vector::cross(AB, AC) * vector::cross(AB, AD) > 0 || vector::cross(CD, CA) * vector::cross(CD, CB) > 0) {
				return false;
			}
			return true;
		}
		bool collision(const line& a, const rect& b) {
			return detail::collision(a.A(), b) || detail::collision(a.B(), b) ||
				collision(a, b.top()) ||
				collision(a, b.right()) ||
				collision(a, b.left()) ||
				collision(a, b.bottom());
		}
		bool collision(const rect& a, const rect& b) {
			return collision(b.top(), a) ||
				   collision(b.right(), a) ||
				   collision(b.bottom(), a) ||
				   collision(b.left(), a) ||
				   collision(a.top(), b) ||
				   collision(a.right(), b) ||
				   collision(a.bottom(), b) ||
				   collision(a.left(), b);
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
