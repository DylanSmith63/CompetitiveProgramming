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
 
void solve() {
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    vector<int> dp(100'001, 0), nxt = dp;
    dp[0] = 1;
    int checked = 0;
    for (int i = 0; i < N && (i + 1) * (i + 1) < 100'000; i++) {
        nxt = dp;
        for (int j = 0; j + a[i] <= (i + 1) * (i + 1); j++) {
            nxt[j + a[i]] += dp[j];
            if (nxt[j + a[i]] >= mod) nxt[j + a[i]] -= mod;
        }
        checked++;
        swap(dp, nxt);
    }
    int res = 0;
    for (int i : dp) res += i, res %= mod;
    for (int i = 0; i < N - checked; i++) res = res * 2 % mod;
    cout << res << "\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
