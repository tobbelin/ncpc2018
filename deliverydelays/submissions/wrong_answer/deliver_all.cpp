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

ll dist[5100][5100],
   late[5100][5100],
   len[5100][5100];

ll mem[5100];

struct cmp {
    int cur;
    cmp(int _cur) : cur(_cur) {}
    bool operator()(const int &a, const int &b) {
        if (dist[cur][a] != dist[cur][b])
            return dist[cur][a] < dist[cur][b];
        return a < b;
    }
};

int main() {
    int m;
    cin >> n >> m;

    int pizza = 0;

    rep(i,0,m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back(ii(b,c));
        adj[b].push_back(ii(a,c));
    }

    rep(i,0,n) rep(j,0,n) dist[i][j] = DINF;
    rep(start,0,n) {
        cmp c(start);
        set<int, cmp> S(c);
        dist[start][start] = 0;
        S.insert(start);
        while (!S.empty()) {
            int cur = *S.begin();
            S.erase(S.begin());

            iter(it,adj[cur]) {
                int nxt = it->first;
                ll ndist = dist[start][cur] + it->second;
                if (ndist < dist[start][nxt]) {
                    S.erase(nxt);
                    dist[start][nxt] = ndist;
                    S.insert(nxt);
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

    ll res = 0;
    int at = 0;
    ll tm = order[p-1].second.second;
    for (int i = 0; i < p; i++) {
        tm += dist[at][order[i].first];
        at = order[i].first;
        res = max(res, tm - order[i].second.first);
    }

    cout << res << endl;

    return 0;
}

