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

int mod = 1e9+7;

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
    int N, K; cin >> N >> K;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    ll res = 0;
    for (int i : a) res += i, res %= mod;
    res *= mInv(N);
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