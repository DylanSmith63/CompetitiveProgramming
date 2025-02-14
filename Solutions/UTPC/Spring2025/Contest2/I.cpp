#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)
 
mt19937 rng;
 
int mod = 998244353;
 
void solve() {
    int N, K; cin >> N >> K;
    vector<int> a(N), b(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < N; i++) cin >> b[i];
    ll pre = 0, res = 0;
    vector<int> left(N, -1);
    int cur = -1;
    for (int i = 0; i < N; i++) {
        left[i] = cur;
        if (a[i] != b[i]) cur = i;
    }
    for (int i = N - 1; i >= 0; i--) {
        if (a[i] < b[i]) {
            res += (ll)(b[i] - a[i]) * (i - left[i]) % mod * (N - i) % mod;
            res %= mod;
            res += pre * (i - left[i]) % mod;
            res %= mod;
        }
        pre += (ll)(K - a[i]) * (N - i) % mod;
        pre %= mod;
    }
    cout << res << "\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
