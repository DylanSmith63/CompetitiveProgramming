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

vector<ll> pre;
void prec() {
	pre = vector<ll>(1000001, 1);
	for (int i = 1; i <= 1000000; i++) {
		int n = 8 * i - 4;
		pre[i] = (ll)(mPow(2, n) - n + mod) % mod * pre[i - 1] % mod;
	}
}

void solve() {
    int N, M; cin >> N >> M;
    if (N > M) swap(N, M);
    ll res = pre[N] % mod * mPow(2, (ll)(N * 2 - 1) * (M - N) * 2 % (mod - 1)) % mod;
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