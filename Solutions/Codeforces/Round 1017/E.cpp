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
    vector<int> freq(30, 0);
    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < 30; j++) {
    		if (a[i] & 1 << j) freq[j]++;
    	}
    }
    ll res = 0;
    for (int i = 0; i < N; i++) {
    	ll sum = 0;
    	for (int j = 0; j < 30; j++) {
    		if (a[i] & 1 << j) {
    			sum += (ll)(1 << j) * (N - freq[j]);
    		} else {
    			sum += (ll)(1 << j) * freq[j];
    		}
    	}
    	res = max(res, sum);
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