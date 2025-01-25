#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

void solve() {
    int N, M1, M2; cin >> N >> M1 >> M2;
    vector<pair<int, int>> edges;
    for (int i = 0; i < M1; i++) {
    	int u, v; cin >> u >> v; u--; v--;
    	edges.pb({u, v});
    }
    vector<vector<int>> adj(N);
    for (int i = 0; i < M2; i++) {
    	int u, v; cin >> u >> v; u--; v--;
    	adj[u].pb(v);
    	adj[v].pb(u);
    }
    vector<int> group(N, -1);
    queue<int> q;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
    	if (group[i] >= 0) continue;
    	group[i] = i;
    	q.push(i);
    	while (!q.empty()) {
    		int u = q.front(); q.pop();
    		for (int v : adj[u]) {
    			if (group[v] >= 0) continue;
    			group[v] = i;
    			q.push(v);
    		}
    	}
    	cnt++;
    }
    vector<vector<int>> adj2(N);
    int res = 0;
    for (auto &e : edges) {
    	int u = e.first, v = e.second;
    	if (group[u] != group[v]) res++;
    	else {
    		adj2[u].pb(v);
    		adj2[v].pb(u);
    	}
    }
    vector<int> group2(N, -1);
    int cnt2 = 0;
    for (int i = 0; i < N; i++) {
    	if (group2[i] >= 0) continue;
    	group2[i] = i;
    	q.push(i);
    	while (!q.empty()) {
    		int u = q.front(); q.pop();
    		for (int v : adj2[u]) {
    			if (group2[v] >= 0) continue;
    			group2[v] = i;
    			q.push(v);
    		}
    	}
    	cnt2++;
    }
    res += cnt2 - cnt;
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