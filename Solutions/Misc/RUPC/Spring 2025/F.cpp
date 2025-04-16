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

pair<int, int> part(vector<vector<int>> adj, int K) {
	int N = sz(adj);
	vector<int> inCnt(N, 0);
	for (int u = 0; u < N; u++) {
		for (int v : adj[u]) inCnt[v]++;
	}
	queue<int> q;
	for (int u = 0; u < N; u++) {
		if (!inCnt[u]) q.push(u);
	}
	vector<int> mx(N, 0);
	int cnt = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		cnt++;
		for (int v : adj[u]) {
			mx[v] = max(mx[v], mx[u] + 1);
			if (!--inCnt[v]) q.push(v);
		}
	}
	if (cnt < N) return {-1, -1};
	pair<int, int> res = {0, 0};
	for (int i = 0; i < K; i++) res.first = max(res.first, mx[i]);
	for (int i = K; i < K * 2; i++) res.second = max(res.second, mx[i]);
	return res;
}

void solve() {
	int N, M; cin >> N >> M;
	vector<vector<int>> adj(N * 2 + M * 2);
	for (int i = 0; i < M; i++) {
		int u, v; string type; cin >> u >> v >> type; u--; v--;
		if (type == "R") {
			adj[N * 2 + i].pb(v);
			adj[N + v].pb(N * 2 + M + i);
			adj[N * 2 + M + i].pb(u);
			adj[N + u].pb(N * 2 + i);
		} else {
			adj[N * 2 + i].pb(N + v);
			adj[v].pb(N * 2 + M + i);
			adj[N * 2 + M + i].pb(N + u);
			adj[u].pb(N * 2 + i);
		}
	}
	pair<int, int> p = part(adj, N);
	if (p.first == -1) {
		cout << -1 << "\n";
		return;
	}
	p.first /= 2;
	p.second /= 2;
	int res;
	if (p.first != p.second && max(p.first, p.second) % 2 == 1) res = max(p.first, p.second);
	else res = max(p.first, p.second) + 1;
	string s = "";
	for (int i = 0; i < res; i++) s += i % 2 == 0 ? "R" : "B";
	if (p.first == res) {
		for (auto &c : s) {
			if (c == 'R') c = 'B';
			else c = 'R';
		}
	}
	cout << s << "\n";
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    int T; cin >> T;
    for (int t = 0; t < T; t++) solve();

    return 0;
}