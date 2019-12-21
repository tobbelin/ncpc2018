#include <bits/stdc++.h>

const int MAX_V = 9;    // max health plus 1
double ans[43046721] = {}; // MAX_V ** MAX_MINIONS
int n, m, d;

int main(void) {
    scanf("%d%d%d", &n, &m, &d);
    int Goal = 0, H[10], totH = 0;
    for (int i = 0; i < n+m; ++i) {
        scanf("%d", &H[i]);
        Goal = MAX_V*Goal + H[i];
        totH += H[i];
    }
    int OPPMASK = 1;
    for (int i = 0; i < m; ++i)
        OPPMASK *= MAX_V;
    for (int X = 0; X <= Goal; ++X) {
        int left = 0;
        for (int i = n+m-1, XX = X; i >= 0; --i, XX /= MAX_V)
            left += XX % MAX_V;
        if (totH - left > d)
            ans[X] = 0.0;
        else if (X % OPPMASK == 0)
            ans[X] = 1.0;
        else {
            int v = int(ans[X]/10);
            ans[X] = fmod(ans[X], 10) / v;
        }
        for (int Y = 1, XX = X, i = n+m-1; i >= 0; --i, Y *= MAX_V, XX /= MAX_V)
            if (XX % MAX_V < H[i])
                ans[X + Y] += 10 + ans[X];
    }
    printf("%.9lf\n", ans[Goal]);
    return 0;
}
