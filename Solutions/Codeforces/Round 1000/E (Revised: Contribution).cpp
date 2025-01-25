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
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
    	int u, v; cin >> u >> v; u--; v--;
    	adj[u].pb(v);
    	adj[v].pb(u);
    }
   	queue<int> q;
   	q.push(0);
   	vector<int> srt;
   	vector<int> depth(N, 0);
   	while (!q.empty()) {
   		int u = q.front(); q.pop();
   		srt.pb(u);
   		for (int v : adj[u]) {
   			adj[v].erase(find(all(adj[v]), u));
   			depth[v] = depth[u] + 1;
   			q.push(v);
   		}
   	}
   	reverse(all(srt));
   	vector<int> cnt(N, 1);
   	ll res = 0;
   	int tot = 0;
   	for (int u : srt) {
   		ll pairs = 0;
   		for (int v : adj[u]) {
   			cnt[u] += cnt[v];
   			pairs -= (ll)cnt[v] * cnt[v];
   		}
   		pairs += (ll)(cnt[u] - 1) * (cnt[u] - 1);
   		pairs /= 2;
   		res += (ll)(tot - cnt[u] + 1) * depth[u] * 2;
   		res -= (ll)depth[u] * pairs * 2;
   		res -= pairs;
   		tot++;
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