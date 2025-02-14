#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

void solve() {
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    vector<int> x(N, 0);
    for (int t = 0; t < 32; t++) {
        for (int i = 0; i < N; i++) {
            if (a[i] < 0) continue;
            int n  = (a[i] + 1) / 2;
            x[i] += n;
            a[i] -= n * 2;
            a[(i + 1) % N] += n;
        }
    }
    for (int i : a) if (i != 0) {
        cout << "-1\n";
        return;
    }
    int mn = INT_MAX;
    for (int i : x) mn = min(mn, i);
    ll res = 0;
    for (int i : x) res += i - mn;
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }

    return 0;
}