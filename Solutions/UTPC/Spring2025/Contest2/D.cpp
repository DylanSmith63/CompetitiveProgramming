#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

void solve() {
    int N, K; cin >> N >> K;
    vector dp(2, vector<int>(K + 1, 0)), nxt = dp;
    for (int i = 0; i < N; i++) {
        int w, v; cin >> w >> v;
        nxt = dp;
        for (int i = 0; i + w <= K; i++) {
            nxt[0][i + w] = max(nxt[0][i + w], dp[0][i] + v);
            nxt[1][i + w] = max(nxt[1][i + w], dp[1][i] + v);
        }
        for (int i = 0; i <= K; i++) {
            nxt[1][i] = max(nxt[1][i], dp[0][i] + v);
        }
        swap(dp, nxt);
    }
    int res = 0;
    for (auto &r : dp) for (int i : r) res = max(res, i);
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}