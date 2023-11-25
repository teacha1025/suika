/**
* @file collision_2d.h
* @brief 2ŽŸŒ³“–‚½‚è”»’èŠÖŒW
*/
#if _MSC_VER > 1000
#pragma once
#endif
#ifndef _DX_COLLISION_2D_IPP
#define _DX_COLLISION_2D_IPP
#include "../concepts.h"
#include "../point.h"
#include "../vector.h"

#include "../rect_2d.h"
#include "../circle_2d.h"
#include "../line_2d.h"
#include "../polygon.h"

#include "../math.h"

#ifndef CR
#define CR(type) const type&
#endif
namespace dx_engine {
	template<concepts::numbers T>
	bool inline collision(CR(point<T>) p1, CR(point<T>) p2) {
		return p1 == p2;
	}

	template<concepts::numbers T>
	bool inline collision(CR(point<T>) p, CR(line) l) {
		auto tr = [](const vector3<double>& v) {
			return point<double>(v.x, v.y);
		};
		const auto lp = l.tops();
		if (lp.empty()) {
			return false;
		}
		if (lp.size() == 1u) {
			return p == tr(lp.at(0));
		}
		for (size_t i = 0u; i < lp.size() - 1u; i++) {
			point<line::position_type> ab = tr(lp.at(i + 1u) - lp.at(i)), ap = p - tr(lp.at(i));
			line::position_type        s_ab = vector::size(ab), s_ap = vector::size(ap);
			if (vector::dot(ab, ap) == s_ab * s_ap) {
				if (s_ab >= s_ap) {
					return true;
				}
			}
		}

		return false;
	}

	template<concepts::numbers T>
	bool inline collision(CR(point<T>) p, CR(circle) c) {
		return vector::size_square(p - c.position()) <= (double)(c.size() * c.size()) ? true : false;
	}

	template<concepts::numbers T>
	bool inline collision(CR(point<T>) p, CR(rect) r) {
		auto tr = [](const vector3<double>& v) {
			return point<double>(v.x, v.y);
		};
		const auto t = r.tops();
		const point<double> a = tr(t[0]), b = tr(t[1]), c = tr(t[3]), d = tr(t[2]);
		const point<double> _p  = { static_cast<double>(p.x), static_cast<double>(p.y) };
		if (
			vector::cross(b - a, _p - a) > 0 &&
			vector::cross(c - b, _p - b) > 0 &&
			vector::cross(d - c, _p - c) > 0 &&
			vector::cross(a - d, _p - d) > 0) {
			return true;
		}
		return false;
	}

	template<concepts::numbers T>
	bool inline collision(CR(point<T>) pt, CR(polygon) pl) {
		auto tr = [](const vector3<double>& v) {
			return point<double>(v.x, v.y);
		};
		size_t                     cross = 0;
		const point<double>       s   = { 10000, 10000 };
		const auto                 plp = pl.tops();
		const auto                 n     = plp.size();
		std::vector<point<double>> p(n);
		for (size_t i = 0ULL; i < n; i++) {
			p[i] = tr(plp[i]);
		}

		const auto ps = s - pt;
		for (size_t i = 0ULL; i < n; i++) {
			const auto a = p[i], b = p[(i + 1) % n];
			const auto pa = a - pt, pb = b - pt;
			if (vector::cross(ps, pa) * vector::cross(ps, pb) > 0) {
				continue;
			}
			const auto ab = b - a, ap = pt - a, as = s - a;
			if (vector::cross(ab, ap) * vector::cross(ab, as) > 0) {
				continue;
			}
			cross++;
		}
		return cross & 1;
	}

	template<concepts::numbers T>
	bool inline collision(CR(line) l, CR(point<T>) p) {
		return collision(p, l);
	}

	template<concepts::numbers T>
	bool inline collision(CR(circle) c, CR(point<T>) p) {
		return collision(p, c);
	}

	template<concepts::numbers T>
	bool inline collision(CR(rect) r, CR(point<T>) p) {
		return collision(p, r);
	}

	template<concepts::numbers T>
	bool inline collision(CR(polygon) pl, CR(point<T>) pt) {
		return collision(pt, pl);
	}
}
#endif