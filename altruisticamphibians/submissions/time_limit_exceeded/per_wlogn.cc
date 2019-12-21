#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

struct frog {
  ll l, w, h;

  bool operator<(const frog &f) {
    return w > f.w;
  }   
};

int main(void) {
  int n, d;
  scanf("%d%d", &n, &d);
  vector<frog> frogs(n);
  for (auto &f: frogs)
    scanf("%lld%lld%lld", &f.l, &f.w, &f.h);
  sort(frogs.begin(), frogs.end());
  set<pll> aid;
  aid.insert(pll(1LL<<50, 0));
  aid.insert(pll(0, 1LL<<50));
  int ans = 0;
  for (auto &f: frogs) {
    bool ok = false;
    for (auto it = aid.lower_bound(pll(f.w+1, -1)); it != aid.end(); ++it) {
      ok |= it->second + f.l > d;
      auto jt0 = aid.insert(pll(min(it->first - f.w, f.w), it->second + f.h)).first, jt1 = jt0--;
      while (jt0->second <= jt1->second) aid.erase(jt0--);
      ++jt0; ++jt1;
      while (jt0->second <= jt1->second) aid.erase(jt0--);
      if (it->first >= 2*f.w) break;
    }
    ans += ok;
  }
  fprintf(stderr, "aids: %d\n", aid.size());
  printf("%d\n", ans);
}
