#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-9;

struct point {
    double x, y;
    point(double x=0, double y=0): x(x), y(y) {}
    point operator-(const point &p) const { return point(x-p.x, y-p.y); }
    point operator+(const point &p) const { return point(x+p.x, y+p.y); }
    point operator*(double c) const { return point(c*x, c*y); }
    double cross(const point &p) const { return x*p.y - y*p.x; }
    double dot(const point &p) const { return x*p.x + y*p.y; }
    double norm() const { return sqrt(dot(*this)); }
    double norm2() const { return dot(*this); }
};

struct room {
    vector<point> P;
};

void isect(point P1, point P2, point Q1, point Q2, vector<double> &R) {
    point dP = P2-P1, dQ = Q2-Q1;
    double det = dP.cross(dQ);
    if (det == 0) return;
    double s = dQ.cross(P1-Q1);
    double t = dP.cross(P1-Q1);
    if (det < 0) s = -s, t = -t, det = -det;
    if (-eps <= t/det && t/det <= 1 + eps)
        R.push_back(1.0*s/det);
}

double dist2(const point &P1, const point &P2, const point &Q) {
    const point dP = P2-P1;
    double t = dP.dot(Q-P1) / dP.dot(dP);
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    return ((P1-Q) + dP*t).norm2();
}

double dist2(const point &P1, const point &P2, const point &Q1, const point &Q2) {
    return min(min(dist2(P1, P2, Q1), dist2(P1, P2, Q2)),
               min(dist2(Q1, Q2, P1), dist2(Q1, Q2, P2)));
}

int best_extension(point P, point Q, const vector<room> &rooms, double L) {
    double shift = L / (P-Q).norm();
    vector<pair<double, int>> events;
    for (auto &R: rooms) {
        vector<double> I;
        for (int i = 0; i < 4; ++i) {
            isect(P, Q, R.P[i], R.P[(i+1)%4], I);
        }
        if (I.size() == 1) I.push_back(I.back());
        sort(I.begin(), I.end());
        if (!I.empty()) {
            double a = I.front(), b = I.back();
            events.push_back(make_pair(a - eps, -1));
            events.push_back(make_pair(b + shift + eps, +1));
        }
    }
    sort(events.begin(), events.end());
    int cur = 0, best = 0;
    for (auto &e: events) {
        cur -= e.second;
        best = max(best, cur);
    }
    return best;
}


struct polynomial {
  vector<double> c;
  polynomial(vector<double> c): c(c) {}

  double operator()(double x) const {
    double val = 0;
    for(int i = c.size(); --i >= 0; ) (val *= x) += c[i];
    return val;
  }

  void diff() {
    for (int i = 1; i < c.size(); ++i) c[i-1] = i*c[i];
    c.pop_back();
  }
};

void poly_roots(const polynomial& p, double xmin, double xmax,
		vector<double>& roots) {
  if (p.c.size() == 2) { roots.push_back(-p.c.front()/p.c.back()); }
  else {
    polynomial d = p;
    vector<double> droots = {xmax+1};
    d.diff();
    poly_roots(d, xmin, xmax, droots);
    sort(droots.begin(), droots.end());
    double lo = xmin, hi;
    for (double dr: droots) {
      double hi = dr;
      bool sign = p(lo) > 0;
      if (sign ^ p(hi) > 0) {
	while (hi - lo > eps) {
	  double m = (lo + hi) / 2, f = p(m);
	  (f <= 0 ^ sign ? lo : hi) = m;
	}
	roots.push_back((lo + hi) / 2);
      }
      lo = dr;
    }
  }
}

int best_slide(point P1, point P2, point Q1, point Q2, point R, const vector<room> &rooms, double L) {
  point dP = P2-P1, dQ = Q2-Q1;
  if (dP.cross(dQ) == 0) return 0;
  if (dP.y == 0) { swap(P1, Q1); swap(P2, Q2); swap(dP, dQ); }
  point RS(R.x - P1.x, R.y - Q1.y);
  polynomial p({-L*L*RS.x*RS.x, 2*L*L*RS.x, (RS.norm2()-L*L), -2*RS.x, 1});
  vector<double> X;
  poly_roots(p, min(Q1.x, Q2.x) - P1.x - eps, max(Q1.x, Q2.x) - P1.x + eps, X);
  int ans = 0;
  for (double x: X)
    ans = max(ans, best_extension(R, point(x + P1.x, Q1.y), rooms, L));
  return ans;
}


int main(void) {
    int r, l;
    scanf("%d%d", &r, &l);
    vector<room> rooms(r);
    for (int i = 0; i < r; ++i) {
        rooms[i].P.resize(4);
        for (int j = 0; j < 4; j += 2)
            scanf("%lf%lf", &rooms[i].P[j].x, &rooms[i].P[j].y);
        rooms[i].P[1].x = rooms[i].P[0].x;
        rooms[i].P[1].y = rooms[i].P[2].y;
        rooms[i].P[3].x = rooms[i].P[2].x;
        rooms[i].P[3].y = rooms[i].P[0].y;
    }
    int ans = 1;
    for (int r1 = 0; r1 < r; ++r1)
        for (int i1 = 0; i1 < 4; ++i1)
            for (int r2 = 0; r2 < r; ++r2)
                for (int i2 = 0; i2 < 4; ++i2) {
		    if (r1 == r2) continue;
		    ans = max(ans, best_extension(rooms[r1].P[i1], rooms[r2].P[i2], rooms, l));
		    for (int r3 = 0; r3 < r1; ++r3) {
		      for (int i3 = 0; i3 < 4; ++i3) {
			if (r3 == r2) continue;
			ans = max(ans, best_slide(rooms[r1].P[i1], rooms[r1].P[(i1+1)%4],
						  rooms[r3].P[i3], rooms[r3].P[(i3+1)%4],
						  rooms[r2].P[i2], rooms, l));
		      }
		    }
		    if (dist2(rooms[r1].P[i1], rooms[r1].P[(i1+1)%4],
			      rooms[r2].P[i2], rooms[r2].P[(i2+1)%4]) <= (l+eps)*(l+eps))
		      ans = max(ans, 2);
		}
    printf("%d\n", ans);
    return 0;
}
