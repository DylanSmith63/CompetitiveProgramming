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
 
void solve() {
    int N, D; cin >> N >> D;
    vector<pair<int, int>> points;
    for (int i = 0; i < N; i++) {
        int x, p; cin >> x >> p;
        points.pb({x, p});
    }
    sort(all(points));
    vector<ll> dp(N, 0);
    int j = 0;
    ll mx = 0, res = 0;
    for (int i = 0; i < N; i++) {
        while (points[i].first - points[j].first >= D) mx = max(mx, dp[j++]);
        dp[i] = mx + points[i].second;
        res = max(res, dp[i]);
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
