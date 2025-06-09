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
    vector<int> dp(N + 1, 0), dpMx(N + 1, 0);
	priority_queue<pair<int, int>> pq;
	map<int, int> last;
    for (int i = 0; i < N; i++) {
    	last[a[i]] = i;
    	pq.push({-i, a[i]});
    	while (-pq.top().first != last[pq.top().second]) pq.pop();
    	int l = -pq.top().first;
    	dp[i + 1] = dpMx[l] + 1;
    	dpMx[i + 1] = max(dpMx[i], dp[i + 1]);
    }
    cout << dp[N] << "\n";
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