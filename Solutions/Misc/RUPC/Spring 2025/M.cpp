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
    string s; cin >> s;
    string res = "";
    for (int j = 0; j < sz(s); j++) {
    	for (int t = 0; t < 2; t++) {
    		for (int i = 9; i >= 0; i--) {
	    		if (i == s[j] - '0') continue;
	    		res += (char)('0' + i);
	    	}
    	}
    	if (j < sz(s) - 1) res += s[j];
    }
    cout << res << "\n";
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