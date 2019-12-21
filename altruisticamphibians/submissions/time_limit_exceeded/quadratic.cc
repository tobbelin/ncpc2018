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
  vector<pll> aid;
  aid.push_back(pll(1LL<<50, 0));
  int ans = 0;
  for (auto &f: frogs) {
    bool ok = false;
    for (int i = aid.size()-1; i >= 0; --i)
      if (aid[i].first > f.w) {
	aid.push_back(pll(min(aid[i].first-f.w, f.w), aid[i].second+f.h));
	if (aid[i].second + f.l > d)
	  ok = true;
      }
    ans += ok;
    
    sort(aid.begin(), aid.end());
    int r = 0;
    for (int i = 0; i < aid.size(); ++i) {
      if (aid[i].second < aid[r].second) ++r;
      aid[r] = aid[i];
    }
    aid.resize(r+1);
  }
  fprintf(stderr, "aids: %d\n", aid.size());
  printf("%d\n", ans);
}
