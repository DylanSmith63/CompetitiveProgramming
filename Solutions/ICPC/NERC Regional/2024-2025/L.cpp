#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

// 25 25
// 21 25 (<= 1)
// 18 25 (<= 1)
// 18 21 21
// 18 18 21 (<= 1)
// 18 18 18

void solve() {
    int N; cin >> N;
    int res = INT_MAX;
    for (int x = 0; x <= 1; x++) {
        for (int y = 0; y <= 1; y++) {
            for (int z = 0; z <= 1; z++) {
                int a = N, b = N, c = N;
                a = max(0, a - y - z * 2);
                b = max(0, b - x - z);
                c = max(0, c - x - y);
                int cost = x + y + z;
                cost += (c + 1) / 2;
                cost += (b + 1) / 2;
                a = max(0, a - (b + 1) / 2);
                cost += (a + 2) / 3;
                res = min(res, cost);
            }
        }
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