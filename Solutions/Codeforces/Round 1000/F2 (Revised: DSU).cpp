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

int find(vector<int> &group, int i) {
	return group[i] == i ? i : group[i] = find(group, group[i]);
}

void solve() {
    int N; cin >> N;
    vector<pair<int, int>> ranges;
    ranges.pb({0, N * 2 + 1});
    for (int i = 1; i <= N; i++) {
    	int l, r; cin >> l >> r;
    	ranges.pb({l, r});
    }
    vector<char> s((N + 1) * 2, ' ');
    vector<int> idx(sz(s), -1);
    for (int i = 0; i <= N; i++) {
    	s[ranges[i].first] = '(';
    	s[ranges[i].second] = ')';
    	idx[ranges[i].first] = i;
    }
    vector<int> par(N + 1, -1);
    stack<int> st;
    for (int i = 0; i < sz(s); i++) {
    	if (s[i] == '(') {
    		if (i > 0) par[idx[i]] = st.top();
    		st.push(idx[i]);
    	} else st.pop();
    }
    vector<int> group(N + 1);
    for (int i = 0; i <= N; i++) group[i] = i;
    ll ways = 1;
	vector<int> space(N + 1, 0);
	vector<ll> res = {1};
    for (int i = N; i >= 1; i--) {
    	int p = find(group, par[i]);
    	ways *= mInv(catalan(space[i]));
    	ways %= mod;
    	ways *= mInv(catalan(space[p]));
    	ways %= mod;
    	space[p] += space[i] + 1;
    	ways *= catalan(space[p]);
    	ways %= mod;
    	group[i] = p;
    	res.pb(ways);
    }
    reverse(all(res));
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