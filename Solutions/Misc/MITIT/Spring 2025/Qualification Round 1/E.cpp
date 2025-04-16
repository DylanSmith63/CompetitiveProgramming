#include <bits/stdc++.h>
 
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

mt19937 rng;

vector<int> move(string s) {
    string t = s;
    sort(all(t));
    int m = 0;
    while (t[m] == '0') m++;
    int zL = 0, oR = sz(s) - 1;
    while (zL < sz(s) && s[zL] == '0') zL++;
    while (oR >= 0 && s[oR] == '1') oR--;
    for (int d = 0; d < sz(s); d++) {
        assert(m + d < sz(s) && m - 1 - d >= 0);
        if (s[m - 1 - d] != t[m - 1 - d] && s[m + d] != t[m + d] && zL == m - 1 - d && oR == m + d) return {};
        if (s[m - 1 - d] != t[m - 1 - d] && s[m + d] != t[m + d]) {
            vector<int> res;
            for (int i = 0; i < sz(s); i++) {
                if (i < m - 1 - d || i > m + d) res.pb(i);
            }
            return res;
        }
        if (s[m - 1 - d] != t[m - 1 - d]) {
            vector<int> res;
            for (int i = 0; i < sz(s); i++) {
                if (i >= m - 1 - d && i < m + d) continue;
                res.pb(i);
            }
            return res;
        }
        if (s[m + d] != t[m + d]) {
            vector<int> res;
            for (int i = 0; i < sz(s); i++) {
                if (i > m - 1 - d && i <= m + d) continue;
                res.pb(i);
            }
            return res;
        }
    }
    return {};
}

bool sorted(string s) {
    string t = s;
    sort(all(t));
    return s == t;
}

void solve() {
    string s;
    bool firstMove = 1;
    do {
        cin >> s;
        assert(s != "-1");
        if (sorted(s)) break;
        if (move(s).empty()) {
            cout << "Second\n";
            cout.flush();
            firstMove = 0;
            cin >> s;
            assert(s != "-1");
        }
        if (firstMove) {
            cout << "First\n";
            cout.flush();
            firstMove = 0;
        }
        if (sorted(s)) break;
        vector<int> v = move(s);
        assert(!v.empty());
        cout << sz(v);
        for (int i : v) cout << " " << (i + 1);
        cout << "\n";
        cout.flush();
    } while (!sorted(s));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }

    return 0;
}