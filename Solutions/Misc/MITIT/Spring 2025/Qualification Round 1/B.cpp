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
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    sort(all(a));
    vector<int> left(N, INT_MAX), right(N, INT_MAX);
    for (int i = 1; i < N; i++) {
        left[i] = min(a[i] - a[i - 1], left[i - 1]);
    }
    for (int i = N - 2; i >= 0; i--) {
        right[i] = min(a[i + 1] - a[i], right[i + 1]);
    }
    int res = INT_MAX;
    for (int i = 2; i < N - 1; i++) {
        res = min(res, left[i - 1] + right[i]);
    }
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