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
    int N, M; cin >> N >> M;
    vector<vector<pair<int, int>>> adj(N), adjR(N);
    for (int i = 0; i < M; i++) {
        int u, v, k; cin >> u >> v >> k;
        u--; v--;
        adj[u].pb({v, k});
        adjR[v].pb({u, k});
    }
    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push({0, {0, 0}});
    pq.push({0, {1, 0}});
    int mx = 0, bad = 0;
    set<int> vis, visR;
    while (!pq.empty()) {
        int k = -pq.top().first, type = pq.top().second.first, u = pq.top().second.second;
        pq.pop();
        if (k > mx) {
            if (bad) {
                cout << "NO\n";
                return;
            }
            mx = k;
        }
        if (!type) {
            if (!vis.count(u)) {
                vis.insert(u);
                if (!visR.count(u)) bad++;
                for (auto &e : adj[u]) {
                    int v = e.first, k2 = e.second;
                    pq.push({-k2, {0, v}});
                }
            }
        } else {
            if (!visR.count(u)) {
                visR.insert(u);
                if (vis.count(u)) bad--;
                for (auto &e : adjR[u]) {
                    int v = e.first, k2 = e.second;
                    pq.push({-k2, {1, v}});
                }
            }
        }
    }
    if (bad) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
