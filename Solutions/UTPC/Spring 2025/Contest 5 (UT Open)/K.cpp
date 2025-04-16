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
    vector<int> a(N), b(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    for (int i = 0; i < b.size(); i++) cin >> b[i];
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    queue<int> q; q.push(0);
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
    vector<pair<int, int>> dp(N, {0, 0});
    for (int u : srt) {
        if (depth[u] % 2 == 0) {
            for (int v : adj[u]) {
                if (dp[v].first > dp[u].first || dp[v].first == dp[u].first && dp[v].second > dp[u].second) {
                    dp[u] = dp[v];
                }
            }
        } else {
            for (int v : adj[u]) {
                if (dp[v].second > dp[u].second || dp[v].second == dp[u].second && dp[v].first > dp[u].first) {
                    dp[u] = dp[v];
                }
            }
        }
        if (a[u]) dp[u].first++;
        if (b[u]) dp[u].second++;
    }
    cout << dp[0].first << " " << dp[0].second << "\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
