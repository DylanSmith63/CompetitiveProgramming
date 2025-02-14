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
    vector<int> a(N), b(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    for (int i = 0; i < b.size(); i++) cin >> b[i];
    vector<int> res(N);
    for (int i = N - 1; i >= 0; i--) {
        res[i] = min(K, a[i] / b[i]);
        K -= res[i];
    }
    if (K) fill(all(res), 0);
    for (int i = 0; i < sz(res); i++) {
        cout << res[i] << (i == sz(res) - 1 ? "\n" : " ");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}