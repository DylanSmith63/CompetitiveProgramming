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

int find(vector<int> &group, int i) {
	return group[i] == i ? i : group[i] = find(group, group[i]);
}

void solve() {
    int N, M; cin >> N >> M;
    vector<vector<int>> edges;
    for (int i = 0; i < M; i++) {
    	int u, v, k; cin >> u >> v >> k; u--; v--;
    	edges.pb({k, u, v});
    }
    sort(all(edges));
    vector<int> group(N); iota(all(group), 0);
    vector<int> mn(N, INT_MAX);
    int res = INT_MAX;
    for (auto &e : edges) {
    	int k = e[0], u = e[1], v = e[2];
    	int g1 = find(group, u), g2 = find(group, v);
    	if (g1 != g2) {
    		group[g1] = g2;
    		mn[g2] = min(mn[g2], mn[g1]);
    	}
    	mn[g2] = min(mn[g2], k);
    	int gA = find(group, 0), gB = find(group, N - 1);
    	if (gA == gB) {
    		res = min(res, k + mn[gA]);
    	}
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