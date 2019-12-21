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
typedef unsigned long long ull;
const int INF = 2147483647;

int main() {
    int n;
    ull s;
    cin >> n >> s;
    vector<pair<ull, string> > arr;
    rep(i,0,n) {
        string t;
        ull b;
        cin >> t >> b;
        arr.push_back(make_pair(b, t));
    }
    sort(arr.rbegin(), arr.rend());

    vector<string> found;
    rep(i,0,n) {
        if (s >= arr[i].first) {
            s -= arr[i].first;
            found.push_back(arr[i].second);
        }
    }

    if (s != 0) {
        cout << 0 << endl;
    } else {
        cout << size(found) << endl;
        iter(it,found) {
            cout << *it << endl;
        }
    }

    return 0;
}

