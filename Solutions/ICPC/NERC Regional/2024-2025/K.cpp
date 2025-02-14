#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

void solve() {
    int N, a, b; cin >> N >> a >> b;
    int a1 = 1, b1 = 1;
    for (int i = 1; i <= N; i++) {
        if (gcd(i, a) == 1) a1 = i;
        if (gcd(i, b) == 1) b1 = i;
    }
    vector<vector<int>> dp(N - a1 + 1, vector<int>(N - b1 + 1, INT_MAX));
    dp[0][0] = a1 - 1 + b1 - 1;
    for (int i = a1; i <= N; i++) {
        for (int j = b1; j <= N; j++) {
            if (i > a1) dp[i - a1][j - b1] = min(dp[i - a1][j - b1], dp[i - 1 - a1][j - b1] + gcd(j, b));
            if (j > b1) dp[i - a1][j - b1] = min(dp[i - a1][j - b1], dp[i - a1][j - 1 - b1] + gcd(i, a));
        }
    }
    int res = dp[N - a1][N - b1];
    for (int i = 1; i <= N; i++) res += gcd(i, a) + gcd(i, b);
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}