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
    vector<int> b(N), w(N), v(N);
    for (int i = 0; i < N; i++) cin >> b[i];
    for (int i = 0; i < N; i++) cin >> w[i];
    for (int i = 0; i < N; i++) cin >> v[i];
    vector<ll> sum(K + 1, 0);
    for (int i = 0; i < N; i++) {
        int l = b[i], r = K - w[i];
        if (l > r) continue;
        sum[l] += v[i];
        sum[r + 1] -= v[i];
    }
    ll res = 0;
    for (int i = 0; i <= K; i++) {
        if (i > 0) sum[i] += sum[i - 1];
        res = max(res, sum[i]);
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