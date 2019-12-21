#include <bits/stdc++.h>

const int MAX_V = 9;    // max health plus 1
double ans[43046721] = {}; // MAX_V ** MAX_MINIONS
int n, m, d, OPPMASK;

double Ans(int X, int d) {
    if (X % OPPMASK == 0) return 1.0;
    if (!d) return 0.0;
    double &res = ans[X];
    if (res == 0) {
        int l = 0;
        for (int Y = 1, XX = X, i = n+m; i >= 0; --i, Y *= MAX_V, XX /= MAX_V)
            if (XX % MAX_V) {
                res += Ans(X - Y, d - 1);
                ++l;
            }
        res = res/l + 1;
    }
    return res-1;
}

int main(void) {
    scanf("%d%d%d", &n, &m, &d);
    int X = 0;
    for (int i = 0; i < n+m; ++i) {
        int h; scanf("%d", &h);
        X = MAX_V*X + h;
    }
    OPPMASK = 1;
    for (int i = 0; i < m; ++i)
        OPPMASK *= MAX_V;
    printf("%.9lf\n", Ans(X, d));
    return 0;
}
