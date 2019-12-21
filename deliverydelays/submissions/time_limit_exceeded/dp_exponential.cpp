#include <bits/stdc++.h>
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 1000000000;

int dist[100][100];

int n;

vector<pair<int,ii> > del;
bool del_cmp(const pair<int,ii> &a, const pair<int,ii> &b) {
    return a.second.first < b.second.first;
}

map<pair<ii,ii>, int> mem;

int dp(int at, int t, int done, int have) {
    pair<ii,ii> st(ii(at,t), ii(done,have));
    if (mem.find(st) != mem.end())
        return mem[st];

    if (done == (1<<size(del))-1) {
        return 0;
    }

    int res = INF;

    // go to the pizza place
    if (at != 0) {
        res = min(res, dp(0, t + dist[at][0], done, have));
    }

    // wait for a pizza to be ready
    if (at == 0) {
        rep(i,0,size(del)) {
            if (t < del[i].second.second) {
                res = min(res, dp(at, del[i].second.second, done, have));
            }
        }
    }

    // put pizza in car
    if (at == 0) {
        rep(i,0,size(del)) {
            if (t >= del[i].second.second && (((done | have) & (1<<i))) == 0) {
                res = min(res, dp(at, t, done, have | (1<<i)));
            }
        }
    }

    // deliver next pizza
    rep(i,0,size(del)) {
        if (have & (1<<i)) {
            int nat = del[i].first;
            int nt = t + dist[at][nat];

            res = min(res, max(nt - del[i].second.first, dp(nat, nt, done ^ (1<<i), have ^ (1<<i))));
        }

        if (~done & (1<<i)) {
            // we cannot deliver later orders until this one has been delivered
            break;
        }
    }

    return mem[st] = res;
}

int main() {
    int m;
    cin >> n >> m;

    rep(i,0,n) {
        rep(j,0,n) {
            dist[i][j] = i == j ? 0 : INF;
        }
    }

    rep(i,0,m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    rep(k,0,n) {
        rep(i,0,n) {
            rep(j,0,n) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    rep(i,0,n) {
        rep(j,0,n) {
            assert(dist[i][j] != INF);
        }
    }

    int qs;
    cin >> qs;

    rep(q,0,qs) {
        int u, s, t;
        // cin >> u >> s >> t;
        cin >> s >> u >> t;
        u--;
        del.push_back(make_pair(u, ii(s,t)));
    }

    sort(del.begin(), del.end(), del_cmp);
    rep(i,0,size(del)) {
        assert(del[i].second.first <= del[i].second.second);
    }
    rep(i,0,size(del)-1) {
        assert(del[i].second.first < del[i+1].second.first);
        assert(del[i].second.second < del[i+1].second.second);
    }

    cout << dp(0, 0, 0, 0) << endl;

    return 0;
}

