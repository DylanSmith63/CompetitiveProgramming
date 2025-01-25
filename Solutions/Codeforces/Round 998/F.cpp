#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

int mod = 998244353;

ll exGCD(ll a, ll b, ll &x, ll &y) {
    if (a == 0) { x = 0; y = 1; return b; }
    ll g = exGCD(b % a, a, x, y);
    ll t = x; x = y - b / a * x; y = t;
    return g;
}

int mInv(int n) {
	ll x, y, g = exGCD(n, mod, x, y);
	if (g != 1) return 0;
	return (x % mod + mod) % mod;
}

vector<int> factArr = {1}, factInvArr = {1};
int fact(int n) {
    while (sz(factArr) <= n)
        factArr.pb((int)((ll)factArr[sz(factArr) - 1] * sz(factArr) % mod));
    return factArr[n];
}

int factInv(int n) {
    fact(n);
    while (sz(factInvArr) <= n)
        factInvArr.pb(mInv(factArr[sz(factInvArr)]));
    return factInvArr[n];
}

int choose(int n, int k) {
	if (k < 0 || k > n) return 0;
    return (int)((ll)fact(n) * factInv(k) % mod * factInv(n - k) % mod);
}

void solve() {
    int K, N; cin >> K >> N;
    vector dp(18, vector<int>(K + 1, 0));
    dp[0][1] = 1;
    vector<ll> binoms(19, 1);
    for (int i = 1; i <= 18; i++) {
    	binoms[i] = binoms[i - 1] * (N + 2 - i) % mod * mInv(i) % mod;
    }
    for (int i = 1; i <= K; i++) {
    	for (int j = i * 2; j <= K; j += i) {
    		for (int k = 0; k + 1 < 18; k++) {
    			dp[k + 1][j] += dp[k][i];
    			if (dp[k + 1][j] >= mod) dp[k + 1][j] -= mod;
    		}
    	}
    	ll res = 0;
    	for (int k = 0; k < 18; k++) {
    		if (k <= N) {
    			res += binoms[k + 1] * dp[k][i] % mod;
    			if (res >= mod) res -= mod;
    		}
    	}
    	if (i == 1) {
    		res--;
    		if (res < 0) res += mod;
    	}
    	cout << res << (i == K ? "\n" : " ");
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