#include <bits/stdc++.h>
#include "../geometry/point.hpp"
using namespace std;

struct monotonic_dp_hull {
	long long prev_x = LLONG_MIN, prev_y = 1;
	deque<Pll> points;

	void add(const Pll &p) {
		assert(points.empty() || p.x >= points.back().x);

		if (!points.empty() && p.x == points.back().x) {
			if (p.y <= points.back().y) return;
			points.pop_back();
		}
		while (size() >= 2 &&
			   ((points.back() - p).cross(points[size() - 2] - points.back())) <= 0)
			points.pop_back();
		points.push_back(p);
	}

	void add(long long m, long long b) { add(Point(m, b)); }

	long long query(long long x, long long y = 1) {
		assert(size() > 0);
		assert(prev_x == LLONG_MIN || x * prev_y >= prev_x * y);
		prev_x = x, prev_y = y;
		// The while condition is equivalent to dot(x, points[1]) >= dot(x, points[0])
		while (size() >= 2 &&
		       x * (points[1].x - points[0].x) >= (points[0].y - points[1].y) * y)
			points.pop_front();
		return points[0].x * x + points[0].y * y;
	}

	void clear() {
		points.clear();
		prev_x = LLONG_MIN, prev_y = 1;
	}

	int size() const { return points.size(); }
};
