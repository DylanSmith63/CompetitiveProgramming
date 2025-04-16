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
    int N, M, K; cin >> N >> M >> K;
    vector<int> x(K);
    for (int i = 0; i < K; i++) cin >> x[i], x[i]--;
    set<pair<int, int>> st;
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v; u--; v--;
        if (u > v) swap(u, v);
        st.insert({u, v});
    }
    vector<pair<int, int>> add;
    for (int i = 0; i < K; i++) {
        if (i == 0 && x[i] == 0) continue;
        int u = i == 0 ? 0 : x[i - 1], v = x[i];
        if (u > v) swap(u, v);
        if (!st.count({u, v})) {
            add.pb({u, v});
            st.insert({u, v});
        }
    }
    vector<vector<int>> adj(N);
    for (auto &p : st) {
        int u = p.first, v = p.second;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    queue<int> q; q.push(0);
    vector<bool> vis(N, 0);
    vis[0] = 1;
    vector<int> dist(N, 0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (vis[v]) continue;
            dist[v] = dist[u] + 1;
            vis[v] = 1;
            q.push(v);
        }
    }
    for (int i = 1; i < K; i++) {
        if (dist[x[i - 1]] >= dist[x[i]]) {
            cout << -1 << "\n";
            return;
        }
    }
    cout << sz(add) << "\n";
    for (auto &p : add) {
        cout << (p.first + 1) << " " << (p.second + 1) << "\n";
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