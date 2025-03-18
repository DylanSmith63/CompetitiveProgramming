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

int mod = 998244353;

int mPow(int n, int p) {
    int res = 1, pow = n;
    while (p > 0) {
        if ((p & 1) == 1)
            res = (int)((ll)res * pow % mod);
        pow = (int)((ll)pow * pow % mod);
        p >>= 1;
    }
    return res;
}

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

void solve() {
    ll N, M, A, B; cin >> N >> M >> A >> B; A++; B++;
    vector dp(61, vector(2, vector(2, vector<ll>(2, 0))));
    dp[60][0][0][0] = 1;
    for (int i = 59; i >= 0; i--) {
    	for (int lA = 0; lA <= 1; lA++) {
    		for (int lB = 0; lB <= 1; lB++) {
    			for (int xgz = 0; xgz <= 1; xgz++) {
    				for (int d1 = 0; d1 <= 1; d1++) {
    					for (int d2 = 0; d2 <= 1; d2++) {
    						for (int dx = 0; dx <= 1; dx++) {
    							int lA2 = lA; if ((A & 1LL << i) && !d1) lA2 = 1;
		    					int lB2 = lB; if ((B & 1LL << i) && !d2) lB2 = 1;
		    					int xgz2 = xgz; if (dx) xgz2 = 1;
		    					if (!lA && !(A & 1LL << i) && d1) continue;
		    					if (!lB && !(B & 1LL << i) && d2) continue;
		    					if (!xgz && dx && !(d1 && d2)) continue;
		    					dp[i][lA2][lB2][xgz2] += dp[i + 1][lA][lB][xgz];
		    					dp[i][lA2][lB2][xgz2] %= mod;
    						}
    					}
    				}
    			}
    		}
    	}
    }
    A--; B--;
    ll res = (ll)(A + 1) * (B + 1) % mod;
    res += (ll)(A + 1) * (B + 1) % mod * B % mod * mInv(2) % mod * (mPow(2, M) - 2 + mod) % mod;
    res += (ll)(B + 1) * (A + 1) % mod * A % mod * mInv(2) % mod * (mPow(2, N) - 2 + mod) % mod;
    res += dp[0][1][1][1] * (mPow(2, N) - 2 + mod) % mod * (mPow(2, M) - 2 + mod) % mod;
    res %= mod;
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