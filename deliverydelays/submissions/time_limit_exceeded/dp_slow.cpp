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
const ll DINF = 1000000000000000000;

int n;
vii adj[5100];
int p;
vector<pair<int,ii> > order;
int pizza;

ll dist[5100][5100];

map<pair<int,ll> ,ll> mem;
ll earliest_back(int done, ll lateness) {
    if (done == -1) {
        return 0;
    }

    pair<int,ll> st(done, lateness);
    if (mem.find(st) != mem.end())
        return mem[st];

    ll mn = DINF;
    for (int group_start = 0; group_start <= done; group_start++) {

        ll now = earliest_back(group_start - 1, lateness);
        if (now == DINF) break;
        bool ok = true;

        int at = pizza;
        now = max(now, (ll)order[done].second.second);
        for (int i = group_start; i <= done; i++) {
            int v = order[i].first;
            now += dist[at][v];
            at = v;
            if (now - order[i].second.first > lateness) {
                ok = false;
                break;
            }
        }
        if (ok) {
            now += dist[at][pizza];
            at = pizza;
            mn = min(mn, now);
        }
    }

    return mem[st] = mn;
}

int main() {
    int m;
    cin >> n >> m;

    pizza = 0;

    rep(i,0,m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back(ii(b,c));
        adj[b].push_back(ii(a,c));
    }

    rep(i,0,n) rep(j,0,n) dist[i][j] = DINF;
    rep(start,0,n) {
        set<pair<ll,int> > S;
        dist[start][start] = 0;
        S.insert(make_pair(0, start));
        while (!S.empty()) {
            pair<ll,int> cur = *S.begin();
            S.erase(S.begin());

            iter(it,adj[cur.second]) {
                int nxt = it->first;
                ll ndist = cur.first + it->second;
                if (ndist < dist[start][nxt]) {
                    S.erase(make_pair(dist[start][nxt], nxt));
                    dist[start][nxt] = ndist;
                    S.insert(make_pair(dist[start][nxt], nxt));
                }
            }
        }
    }
    rep(i,0,n) rep(j,0,n) assert(dist[i][j] != DINF);

    cin >> p;
    rep(i,0,p) {
        int v, s, t;
        cin >> s >> v >> t;
        v--;
        order.push_back(make_pair(v, ii(s,t)));
    }

    ll lo = 0,
        hi = 1000000000000000000LL,
        res = -1;
    while (lo <= hi) {
        ll lateness = (lo+hi)/2;
        mem.clear();
        if (earliest_back(p-1, lateness) != DINF) {
            res = lateness;
            hi = lateness - 1;
        } else {
            lo = lateness + 1;
        }
    }

    assert(res != -1);
    cout << res << endl;

    return 0;
}

