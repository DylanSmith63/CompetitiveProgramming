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
 
int mod = 1000000007;
 
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
    ll N; cin >> N;
    vector<ll> divs;
    for (ll i = 1; i * i <= N; i++) {
        if (N % i == 0) {
            divs.pb(i);
            if (i < N / i) divs.pb(N / i);
        }
    }
    sort(all(divs));
    vector<ll> sum(sz(divs), 0);
    int inv2 = mInv(2);
    ll res = 0;
    for (int i = sz(divs) - 1; i >= 0; i--) {
        sum[i] = N / divs[i] % mod * ((N / divs[i] + 1) % mod) % mod * inv2 % mod * (divs[i] % mod) % mod;
        for (int j = i + 1; j < sz(divs); j++) {
            if (divs[j] % divs[i] == 0) {
                sum[i] -= sum[j];
                if (sum[i] < 0) sum[i] += mod;
            }
        }
        res += sum[i] * mInv(divs[i] % mod) % mod;
        if (res >= mod) res -= mod;
    }
    res *= N % mod;
    res %= mod;
    cout << res << "\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
