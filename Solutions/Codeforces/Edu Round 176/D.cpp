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

vector<vector<ll>> dp;
void prec() {
	dp = vector(60, vector<ll>(60, LLONG_MAX));
	dp[0][0] = 0;
	auto nxt = dp;
	for (int k = 1; k <= 60; k++) {
		nxt = dp;
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				if (dp[i][j] == LLONG_MAX) continue;
				int i2 = min(59, i + k), j2 = min(59, j + k);
				nxt[i2][j] = min(nxt[i2][j], dp[i][j] + (1LL << k));
				nxt[i][j2] = min(nxt[i][j2], dp[i][j] + (1LL << k));
			}
		}
		swap(dp, nxt);
	}
}

void solve() {
    ll x, y; cin >> x >> y;
    ll res = LLONG_MAX;
    for (int i = 0; i < 60; i++) {
    	for (int j = 0; j < 60; j++) {
    		if ((x >> i) == (y >> j)) res = min(res, dp[i][j]);
    	}
    }
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    
    prec();
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }

    return 0;
}