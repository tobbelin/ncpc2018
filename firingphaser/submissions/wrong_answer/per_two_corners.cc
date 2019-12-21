#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
    ll x, y;
    point(ll x=0, ll y=0): x(x), y(y) {}
    point operator-(const point &p) const { return point(x-p.x, y-p.y); }
    ll cross(const point &p) const { return x*p.y - y*p.x; }
    ll dot(const point &p) const { return x*p.x + y*p.y; }
    double norm() const { return sqrt(dot(*this)); }
};

struct room {
    vector<point> P;
};

void isect(point P1, point P2, point Q1, point Q2, vector<double> &R) {
    point dP = P2-P1, dQ = Q2-Q1;
    ll det = dP.cross(dQ);
    if (det == 0) return;
    ll s = dQ.cross(P1-Q1);
    ll t = dP.cross(P1-Q1);
    if (det < 0) s = -s, t = -t, det = -det;
    if (0 <= t && t <= det)
        R.push_back(1.0*s/det);
}

int best_pos(point P, point Q, const vector<room> &rooms, int L) {
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
            events.push_back(make_pair(a - 1e-9, -1));
            events.push_back(make_pair(b + shift + 1e-9, +1));
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

int main(void) {
    int r, l;
    scanf("%d%d", &r, &l);
    vector<room> rooms(r);
    for (int i = 0; i < r; ++i) {
        rooms[i].P.resize(4);
        for (int j = 0; j < 4; j += 2)
            scanf("%lld%lld", &rooms[i].P[j].x, &rooms[i].P[j].y);
        rooms[i].P[1].x = rooms[i].P[0].x;
        rooms[i].P[1].y = rooms[i].P[2].y;
        rooms[i].P[3].x = rooms[i].P[2].x;
        rooms[i].P[3].y = rooms[i].P[0].y;
    }
    int ans = 0;
    for (int r1 = 0; r1 < r; ++r1)
        for (int i1 = 0; i1 < 4; ++i1)
            for (int r2 = 0; r2 <= r1; ++r2)
                for (int i2 = 0; i2 < 4; ++i2) {
                    if (r1 == r2 && i1 == i2) continue;
                    ans = max(ans, best_pos(rooms[r1].P[i1], rooms[r2].P[i2], rooms, l));
                }
    printf("%d\n", ans);
    return 0;
}
