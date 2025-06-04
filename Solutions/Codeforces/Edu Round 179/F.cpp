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

void solve() {
    int p, s; cin >> p >> s;
    vector<pair<int, int>> res;
    for (int c = 1; c <= 50001; c++) {
    	if (2 * s * c % p) continue;
    	int A = 2 * s * c / p;
    	int a = c / 2, b = c - a;
    	if (c - 1 <= A && A <= a * b) {
    		for (int i = 0; i < a; i++) res.pb({i, 0});
    		for (int i = 1; i < b; i++) res.pb({0, i});
    		int cur = A - (a + b - 1);
    		for (int i = 1; i < a; i++) {
    			for (int j = 1; j < b; j++) {
    				if (!cur) break;
    				res.pb({i, j});
    				cur--;
    			}
    			if (!cur) break;
    		}
    		break;
    	}
    }
    // construction if multiple components are allowed lol, I misread :(
    /*if (res.empty()) {
    	for (int A = 1; A <= 50000; A++) {
    		if (p * A % s) continue;
    		int P = p * A / s;
    		if (P % 2) continue;
    		if (2 * (A + 1) <= P && P <= 4 * A) {
    			int l = 1 + 2 * A - P / 2;
    			for (int i = 0; i < l; i++) {
    				res.pb({i, 0});
    			}
    			for (int i = l; i < A; i++) {
    				res.pb({l + 1 + 2 * (i - l), 0});
    			}
    			break;
    		}
    	}
    }*/
    if (res.empty()) {
    	cout << -1 << "\n";
    	return;
    }
    cout << sz(res) << "\n";
    for (auto &p : res) {
    	cout << p.first << " " << p.second << "\n";
    }
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