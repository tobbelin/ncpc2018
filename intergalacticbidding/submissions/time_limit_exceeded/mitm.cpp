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
const int INF = 2147483647;

struct big_integer {
    vector<char> d;
    void clean() {
        while (!d.empty() && d.back() == 0) {
            d.pop_back();
        }
    }
    big_integer(string s) {
        for (int i = size(s)-1; i >= 0; i--) {
            d.push_back(s[i] - '0');
        }
        clean();
    }
    big_integer(vector<char> _d) : d(_d) {
        clean();
    }
    bool operator <(const big_integer &other) const {
        if (size(d) != size(other.d)) {
            return size(d) < size(other.d);
        }
        for (int i = size(d)-1; i >= 0; i--) {
            if (d[i] != other.d[i]) {
                return d[i] < other.d[i];
            }
        }
        return false;
    }
    bool operator <=(const big_integer &other) const {
        return !(other < *this);
    }
    big_integer operator +(const big_integer &other) {
        vector<char> res;
        int carry = 0;
        for (int i = 0; i < size(d) || i < size(other.d) || carry; i++) {
            int here = carry;
            if (i < size(d)) here += d[i];
            if (i < size(other.d)) here += other.d[i];
            carry = 0;
            if (here >= 10) {
                here -= 10;
                carry = 1;
            }
            res.push_back(here);
        }
        assert(carry == 0);
        return big_integer(res);
    }
    big_integer operator -(const big_integer &other) {
        // NOTE: This assumes that other <= *this. This will always be the case in our main algorithm.
        assert(size(d) >= size(other.d));

        vector<char> res;
        int carry = 0;
        for (int i = 0; i < size(d); i++) {
            int here = d[i] - carry;
            carry = 0;
            if (i < size(other.d)) {
                here -= other.d[i];
            }
            if (here < 0) {
                here += 10;
                carry = 1;
            }
            res.push_back(here);
        }
        assert(carry == 0);
        return big_integer(res);
    }
};

big_integer read_big_integer() {
    string s;
    cin >> s;
    return big_integer(s);
}

int main() {
    int n;
    cin >> n;
    big_integer s = read_big_integer();

    vector<big_integer> bets;
    vector<string> names;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        big_integer bet = read_big_integer();
        if (bet <= s) {
            bets.push_back(bet);
            names.push_back(name);
        }
    }

    int l = size(bets)/2,
        r = size(names) - l;

    map<big_integer, set<int> > L;
    for (int g = 0; g < (1<<l); g++) {
        vi here;
        big_integer sm("0");
        for (int i = 0; i < l; i++) {
            if (g & (1<<i)) {
                here.push_back(i);
                sm = sm + bets[i];
            }
        }
        if (L.find(sm) == L.end()) {
            L[sm] = set<int>();
        }
        for (int i = 0; i < size(here); i++) {
            L[sm].insert(here[i]);
        }
    }

    set<int> res;
    for (int g = 0; g < (1<<r); g++) {
        vi here;
        big_integer sm("0");
        for (int i = 0; i < r; i++) {
            if (g & (1<<i)) {
                here.push_back(l + i);
                sm = sm + bets[l + i];
            }
        }
        if (sm <= s) {
            if (L.find(s - sm) != L.end()) {
                set<int> rest = L[s - sm];
                for (auto x : rest) {
                    res.insert(x);
                }
                for (auto x : here) {
                    res.insert(x);
                }
            }
        }
    }

    cout << size(res) << endl;
    for (auto x : res) {
        cout << names[x] << endl;
    }

    return 0;
}

