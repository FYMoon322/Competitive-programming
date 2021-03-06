#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cmath>
using namespace std;
typedef long long ll;
typedef double ld;

const int INF = 1e9, MOD = 1e9 + 7, Q = 38;
const ld eps = 1e-16;
const ll ll_INF = 1e18;


struct Point {
	ld x, y;

	void init(ld x1, ld y1) {
		x = x1;
		y = y1;
	}

	bool eq(Point b) {
		return x == b.x && y == b.y;
	}
};

struct Vector {
	ld x, y;

	void init(ld x1, ld y1, ld x2, ld y2) {
		x = x2 - x1;
		y = y2 - y1;
	}

	void init(Point a, Point b) {
		x = b.x - a.x;
		y = b.y - a.y;
	}

	ld len() {
		return sqrt(x * x + y * y);
	}
};

ld skal(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y;
}

ld vec(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}


struct Line {
	ld A, B, C;
	ld k, b;

	void init(ld A1, ld B1, ld C1) {
		A = A1;
		B = B1;
		C = C1;
		if (B == 0) {
			k = b = 0;
		}
		else {
			k = -A / B;
			b = -C / B;
		}
	}

	void init(ld k1, ld b1) {
		k = k1;
		b = b1;
	}

	ld get_y(ld x) {
		return k * x + b;
	}

	Vector napr() {
		Vector a;
		a.x = B;
		a.y = -A;
		return a;
	}

	bool check(Point a) {
		return A * a.x + B * a.y + C == 0;
	}
};

Point ins_lines(Line a, Line b) {
	Point c;
	c.x = (b.b - a.b) / (a.k - b.k);
	c.y = a.get_y(c.x);
	return c;
}

bool paral_lines(Line a, Line b) {
	Vector v1 = a.napr(), v2 = b.napr();
	return (vec(v1, v2) == 0.0);
}

ld dist_point_line(Line l, Point a) {
//	Point p, q;
//	p.x = 1;
//	q.x = 0;
//	p.y = l.get_y(1);
//	q.y = l.get_y(0);
//	Vector v1, v2;
//	v1.init(p, q);
//	v2.init(p, a);
//	return abs(vec(v2, v1)) / v1.len();
	return abs(l.A * a.x + l.B * a.y + l.C) / sqrt(l.A * l.A + l.B * l.B);
}

void polozh_lines(Line q, Line p) {
	if (paral_lines(q, p)) {
		if (p.B == 0 && q.B == 0) {
			cout << abs(p.C / p.A - q.C / q.A);
		}
		else {
			Point a;
			a.x = 1;
			a.y = q.get_y(1);
			cout << dist_point_line(p, a) << " ";
		}
	}
	else {
		if (p.B == 0) {
			cout << -p.C / p.A << " " << q.get_y(-p.C / p.A);
		}
		else if (q.B == 0) {
			cout << -q.C / q.A << " " << p.get_y(-q.C / q.A);
		}
		else {
			Point ans = ins_lines(p, q);
			cout << ans.x << " " << ans.y;
		}
	}
}


struct Segment {
	Point a, b;

	void init(Point a1, Point b1) {
		a = a1;
		b = b1;
	}

	Line get_line() {
		Line l;
		l.init(a.y - b.y, b.x - a.x, a.x * b.y - a.y * b.x);
		return l;
	}
};


bool ins_segment_point(Segment s, Point c) {
	Vector ac, ab, bc, ba;
	ac.init(s.a, c);
	ab.init(s.a, s.b);
	ba.init(s.b, s.a);
	bc.init(s.b, c);
	return vec(ac, ab) == 0 && vec(ba, bc) == 0 && skal(ac, ab) >= 0 && skal(ba, bc) >= 0;
}


bool ins_segment_line(Segment s, Line l) {
	Point c, d;
	if (l.B != 0) {
		c.x = 0;
		c.y = l.get_y(0);
		d.x = 2;
		d.y = l.get_y(2);
	}
	else {
		c.x = l.C / l.A;
		c.y = 0;
		d.x = l.C / l.A;
		d.y = 2;
	}
	Vector ca, cb, cd;
	ca.init(c, s.a);
	cb.init(c, s.b);
	cd.init(c, d);
	ld a = vec(cd, ca), b = vec(cd, cb);
	if (abs(a) < eps){
		a = 0;
	}
	if (abs(b) < eps){
		b = 0;
	}
	return a * b <= 0;
}


void solve() {
	Segment p, q;
	Point a, b;
	ld x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	a.init(x1, y1);
	b.init(x2, y2);
	p.init(a, b);
	cin >> x1 >> y1 >> x2 >> y2;
	a.init(x1, y1);
	b.init(x2, y2);
	q.init(a, b);
	Line l_q = q.get_line(), l_p = p.get_line();
	if (ins_segment_line(p, l_q) && ins_segment_line(q, l_p)) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}
	/*
	if (paral_lines(l_q, l_p)) {
		cout << "NO";
	}
	else {
		Point ans;
		if (l_p.B == 0) {
			ans.x = -l_p.C / l_p.A; ans.y = l_q.get_y(-l_p.C / l_p.A);
		}
		else if (l_q.B == 0) {
			ans.x = -l_q.C / l_q.A; ans.y = l_p.get_y(-l_q.C / l_q.A);
		}
		else {
			ans = ins_lines(l_p, l_q);
		}
		if (ins_segment_point(p, ans) && ins_segment_point(q, ans)) {
			cout << "YES";
		}
		else {
			cout << "NO";
		}
	}
	*/
}


int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);
	int t;
//	cin >> t;
	t = 1;
	while (t--) {
		cout << fixed;
		cout.precision(9);
		solve();
	}
	return 0;
}
