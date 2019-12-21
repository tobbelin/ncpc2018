#include <iostream>
#include <vector>
#include <complex>
#include <queue>
#include <algorithm>

#define point complex<double>
#define line pair<point, point>
#define room vector<point>
#define interval pair<double, double>

double INF = 1<<30;
double EPS = 0.000001;
double STEP = 0.01;

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


double point_line_seg_distance(const point& p, const line& l)
{
    double A, B, C;
    line_abc_form(l, A, B, C);
    
    double x = (B*(B*real(p)-A*imag(p))+A*C)/(A*A + B*B);
    double y = (A*(-B*real(p)+A*imag(p))+B*C)/(A*A + B*B);

    double x1 = real(l.first);
    double x2 = real(l.second);
    double y1 = imag(l.first);
    double y2 = imag(l.second);

    if(min(x1, x2) <= x <= max(x1, x2) && min(y1, y1) <= y <= max(y1, y2))
        return abs(p-point(x, y));

    return min(abs(p-l.first), abs(p-l.second));
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

        return point(-INF, -INF);
    }

    return point((B2*C1 - B1*C2)/det, (A1*C2 - A2*C1)/det);
}


vector<line> gen_walls(const vector<room>& rooms)
{
    vector<line> walls;
    for (room r : rooms) {
        walls.push_back(line(r[0], r[1]));
        walls.push_back(line(r[0], r[2]));
        walls.push_back(line(r[1], r[3]));
        walls.push_back(line(r[2], r[3]));
    }

    return walls;
}


vector<line> gen_walls(const room& r)
{
    return gen_walls(vector<room>(1, r));
}


double beam_score(const point& start, const point& aim,
                  const room& r, const int& laser_len)
{
    if(abs(start-aim) > laser_len+EPS)
        return INF+abs(start-aim);

    double best_score = INF;
    vector<line> walls = gen_walls(r);
    const line laser(aim, aim+(start-aim)/abs(start-aim)*double(laser_len));
    for(line wall : walls) {
        double score = 0;

        point x = find_intersection(laser, wall);

        if(real(x) == -INF)
            continue;

        double ld1 = abs(laser.first-x);
        double ld2 = abs(laser.second-x);
        if(max(ld1, ld2) > laser_len)
            score += min(ld1, ld2);

        double wd1 = abs(wall.first-x);
        double wd2 = abs(wall.second-x);
        if(max(wd1, wd2) > abs(wall.first-wall.second))
            score += min(wd1, wd2);

        best_score = min(best_score, score);
    }

    return best_score;
}


point find_point_score_zero(const point& corner, const line& wall,
                            const room& r, const int& laser_len)
{
    point start = wall.first, end = wall.second;

    while(abs(start-end) > EPS) {
        point step = (end-start)/3.;
        point mid1 = start+step;
        point mid2 = mid1+step;

        double score1 = beam_score(corner, mid1, r, laser_len);
        double score2 = beam_score(corner, mid2, r, laser_len);

        if(score1 > score2)
            start = mid1;
        else
            end = mid2;
    }

    return (start+end)/2.;
}


point find_first_zero(point start, point end,
                      const point& corner, const line& wall,
                      const room& r, const int& laser_len)
{
    while(abs(start-end) > EPS) {
        point mid = (start+end)/2.;

        if(beam_score(corner, mid, r, laser_len) < EPS)
            end = mid;
        else
            start = mid;
    }

    return (start+end)/2.;
}



vector< pair<double, double> > find_intersection_intervals(const point& corner,
                                                           const line& wall,
                                                           const vector<room>& rooms,
                                                           const int& laser_len)
{
    vector< pair<double, double> > intervals;

    for(const room& r : rooms) {
        point zero_point = find_point_score_zero(corner, wall, r, laser_len);

        if(beam_score(corner, zero_point, r, laser_len) > EPS)
            continue;

        point first = find_first_zero(wall.first,  zero_point, corner, wall, r, laser_len);
        point last  = find_first_zero(wall.second, zero_point, corner, wall, r, laser_len);
       
        intervals.push_back(pair<double, double>(abs(wall.first-first), abs(wall.first-last)));
    }

    return intervals;
}


int find_max_interval_intersection(vector< pair<double, double> >& intervals, const int& laser_len)
{
    sort(intervals.begin(), intervals.end());

    priority_queue<double> active;
    int best = 0;
    for(interval ival: intervals) {
        double current = ival.first;
        active.push(-ival.second);

        while(!active.empty() && -active.top() < current+EPS)
            active.pop();

        best = max(best, int(active.size()));
    }

    return best;
}


int solve_case(const point& corner, const line& wall,
               const vector<room>& rooms, const int& laser_len)
{
    if(point_line_seg_distance(corner, wall) > laser_len+10*EPS)
        return 0;

    vector< pair<double, double> > intervals = find_intersection_intervals(corner, wall, rooms, laser_len);
    return find_max_interval_intersection(intervals, laser_len);
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
    vector<line> walls = gen_walls(rooms);
    for(int i = 0; i < 4*R; ++i) {
        for(int k = 0; k < 4*R; ++k) {
            int opt = solve_case(rooms[i/4][i%4], walls[k], rooms, laser_len);
            ans = max(ans, opt);
        }
    }

    cout << ans << endl;

    return 0;
}
