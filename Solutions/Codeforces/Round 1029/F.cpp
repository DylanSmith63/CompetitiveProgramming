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

int mod = 1e9+7;

void solve() {
    int N; cin >> N;
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
    	int u, v; cin >> u >> v; u--; v--;
    	adj[u].pb(v);
    	adj[v].pb(u);
    }
    queue<int> q; q.push(0);
    vector<int> depth(N, 0);
    while (!q.empty()) {
    	int u = q.front(); q.pop();
    	for (int v : adj[u]) {
    		adj[v].erase(find(all(adj[v]), u));
    		depth[v] = depth[u] + 1;
    		q.push(v);
    	}
    }
    vector<int> leaves;
    for (int i = 0; i < N; i++) {
    	if (adj[i].empty()) leaves.pb(i);
    }
    if (sz(leaves) >= 3) {
    	cout << 0 << "\n";
    	return;
    }
    if (sz(leaves) == 1) {
    	int res = 1;
    	for (int i = 0; i < N; i++) {
    		res = (res + res) % mod;
    	}
    	cout << res << "\n";
    	return;
    }
    int D, A, B;
    for (int i = 0; i < N; i++) {
    	if (sz(adj[i]) == 2) D = depth[i];
    }
    A = depth[leaves[0]] - D;
    B = depth[leaves[1]] - D;
    int res = 0;
    if (A == B) {
    	res = 2;
    } else {
    	if (B > A) swap(A, B);
    	int cur = 1;
    	for (int i = 0; i <= A - B; i++) {
    		if (i >= A - B - 1) {
    			res = (res + cur) % mod;
    		}
    		cur = cur * 2 % mod;
    	}
    }
    for (int i = 0; i <= D; i++) res = res * 2 % mod;
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