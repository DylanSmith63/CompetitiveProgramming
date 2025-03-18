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
    int N, K; cin >> N >> K;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    if (K >= 2) {
    	sort(all(a));
    	reverse(all(a));
    	ll res = 0;
    	for (int i = 0; i < K + 1; i++) res += a[i];
    	cout << res << "\n";
    } else {
    	ll res = 0;
    	for (int i = 0; i < N - 1; i++) res = max(res, (ll)a[i] + a[N - 1]);
    	for (int i = 1; i < N; i++) res = max(res, (ll)a[0] + a[i]);
    	cout << res << "\n";
    }
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