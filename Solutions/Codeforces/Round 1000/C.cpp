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
    vector<pair<int, int>> srt;
    for (int i = 0; i < N; i++) {
    	srt.pb({sz(adj[i]), i});
    }
    sort(all(srt));
    reverse(all(srt));
    int res = INT_MIN;
    for (int u = 0; u < N; u++) {
    	int comps = sz(adj[u]);
    	int mx = INT_MIN;
    	set<int> st; st.insert(u);
    	for (int v : adj[u]) {
    		st.insert(v);
    		mx = max(mx, sz(adj[v]) - 2);
    	}
    	int first = 0;
    	while (first < N && st.count(srt[first].second)) first++;
    	if (first < N) mx = max(mx, srt[first].first - 1);
    	res = max(res, comps + mx);
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