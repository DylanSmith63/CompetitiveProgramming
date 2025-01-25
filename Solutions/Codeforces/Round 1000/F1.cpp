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

int catalan(int n, int k = 0) {
    return (ll)choose(2 * n + k, n) * (k + 1) % mod * mInv(n + k + 1) % mod;
}

void solve() {
    int N; cin >> N;
    vector<int> v(N + 1, 0);
    vector<pair<int, int>> ranges;
    auto comp = [&](int i, int MX) {
    	int l = ranges[i].first, r = ranges[i].second;
    	v[i] = 0;
    	vector<int> dif((N + 1) * 2 + 1, 0);
    	for (int j = 0; j <= MX; j++) {
    		if (j == i) continue;
    		if (ranges[j].first > l && ranges[j].second < r) {
    			dif[ranges[j].first]++;
    			dif[ranges[j].second + 1]--;
    		}
    	}
    	int res = 0;
    	int cur = 0;
    	for (int i = l + 1; i <= r - 1; i++) {
    		cur += dif[i];
    		if (cur == 0) res++;
    	}
    	return res / 2;
    };
    v[0] = N;
    ranges.pb({0, N * 2 + 1});
    ll ways = catalan(N);
    vector<ll> res = {ways};
    for (int i = 1; i <= N; i++) {
    	int l, r; cin >> l >> r;
    	ranges.pb({l, r});
    	v[i] = comp(i, i);
    	ways *= catalan(v[i]);
    	ways %= mod;
    	int mn = -1;
    	for (int j = 0; j < i; j++) {
    		if (ranges[j].first < l && ranges[j].second > r) {
    			if (mn == -1 || ranges[j].second < ranges[mn].second) mn = j;
    		}
    	}
    	if (mn >= 0) {
    		ways *= mInv(catalan(v[mn]));
    		ways %= mod;
    		v[mn] = comp(mn, i);
    		ways *= catalan(v[mn]);
    		ways %= mod;
    	}
    	res.pb(ways);
    }
    for (int i = 0; i < sz(res); i++) {
    	cout << res[i] << (i == sz(res) - 1 ? "\n" : " ");
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