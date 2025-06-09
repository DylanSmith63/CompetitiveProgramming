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
    ll sum = 0;
    for (int i : a) sum += i;
    if (sum % ((ll)N * (N + 1) / 2)) {
    	cout << "NO\n";
    	return;
    }
    ll K = sum / ((ll)N * (N + 1) / 2);
    if ((ll)K * N - a[0] < 0 || ((ll)K * N - a[0]) % (N - 1)) {
    	cout << "NO\n";
    	return;
    }
    ll x = ((ll)K * N - a[0]) / (N - 1);
    if (x < 0 || x > K) {
    	cout << "NO\n";
    	return;
    }
    for (int i = 0; i < N; i++) {
    	if ((ll)x * (i + 1) + (ll)(K - x) * (N - i) != a[i]) {
    		cout << "NO\n";
    		return;
    	}
    }
    cout << "YES\n";
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