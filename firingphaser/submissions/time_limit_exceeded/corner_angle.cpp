#include <iostream>
#include <vector>
#include <complex>
#include <queue>
#include <algorithm>
#include <cmath>

#define point complex<double>
#define line pair<point, point>
#define room vector<point>
#define interval pair<double, double>

const double INF = 1<<30;
const double EPS = 0.000001;
const double STEP = 0.00001;
const double PI = 3.1415926535897;

using namespace std;


void line_abc_form(
        const line& l,
        double& A, double& B, double& C)
{
    A = imag(l.second)-imag(l.first);
    B = real(l.first)-real(l.second);
    C = A*real(l.first) + B*imag(l.first);
}


bool line_seg_contain(const point& p, const line& l)
{
    return abs(abs(l.first-p)+abs(p-l.second)-abs(l.first-l.second)) < EPS;
}


point find_intersection(const line& l1, const line& l2)
{
    double A1, B1, C1, A2, B2, C2;
    line_abc_form(l1, A1, B1, C1);
    line_abc_form(l2, A2, B2, C2);

    double det = A1*B2 - A2*B1;
    if (abs(det) < EPS) {
        if(line_seg_contain(l1.first, l2))
            return l1.first;
        else if(line_seg_contain(l1.second, l2))
            return l1.first;
        else if(line_seg_contain(l2.first, l1))
            return l2.first;
        else if(line_seg_contain(l2.second, l1))
            return l2.second;

        return NULL;
    }

    return point((B2*C1 - B1*C2)/det, (A1*C2 - A2*C1)/det);
}


int find_best_laser(
        const line& laser, 
        const vector<room>& rooms,
        const double& laser_len)
{
    point dir = laser.second-laser.first;
    point outside = laser.first + (20000000./norm(dir))*dir;

    vector<interval> intervals;
    for(room r: rooms) {
        line walls[] = {line(r[0], r[1]), line(r[0], r[2]),
                        line(r[1], r[3]), line(r[2], r[3])};

        double first = INF, last = -INF;
        for(line wall: walls) {
            point p = find_intersection(laser, wall);
            if(line_seg_contain(p, wall)) {
                first = min(first, abs(outside-p));
                last = max(last, abs(outside-p));
            }
        }

        if(first < INF)
            intervals.push_back(interval(first, last));
    }

    sort(intervals.begin(), intervals.end());

    priority_queue<double> active;
    int best = 0;
    for(interval ival: intervals) {
        double current = ival.first;
        active.push(-ival.second);

        while(!active.empty() && active.top()+current > laser_len-EPS)
            active.pop();

        best = max(best, int(active.size()));
    }

    return best;
}


int main()
{
    int R, laser_len;
    cin >> R >> laser_len;

    vector<room> rooms;
    for(int i = 0; i < R; ++i) {
        int lx, ly, ux, uy;
        cin >> lx >> ly >> ux >> uy;
        
        room r;
        r.push_back(point(lx, ly));
        r.push_back(point(ux, ly));
        r.push_back(point(lx, uy));
        r.push_back(point(ux, uy));

        rooms.push_back(r);
    }

    int ans = 0;
    for(int i = 0; i < 4*R; ++i) {
        for(double theta = 0; theta < 2*PI; theta += STEP) {
            point dir(cos(theta), sin(theta));
            int opt = find_best_laser(line(rooms[i/4][i%4], rooms[i/4][i%4]+dir),
                                      rooms, laser_len);

            ans = max(ans, opt);
        }
    }

    cout << ans << endl;

    return 0;
}
