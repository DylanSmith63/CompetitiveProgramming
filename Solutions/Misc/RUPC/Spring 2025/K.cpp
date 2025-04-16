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

struct node {
	int pos, nxt;
};

void solve() {
    int N, M, S; cin >> N >> M >> S; S--;
    vector<vector<int>> adj(N);
    for (int i = 0; i < N; i++) {
    	int K; cin >> K;
    	for (int j = 0; j < K; j++) {
    		int v; cin >> v; v--;
    		adj[i].pb(v);
    	}
    }
    vector<int> cur(N, 0);
    queue<int> q;
    q.push(0);
    vector<node> list;
    list.pb({S, 0});
    while (!q.empty()) {
    	int u = q.front(); q.pop();
    	int n = list[u].pos;
    	int tmp = list[u].nxt;
    	int prev = u;
    	while (cur[n] < sz(adj[n])) {
    		int nxt = adj[n][cur[n]];
    		cur[n]++;
    		if (cur[nxt] == 0) q.push(sz(list));
    		list[prev].nxt = sz(list);
    		list.pb({nxt, -1});
    		prev = sz(list) - 1;
    		n = nxt;
    	}
    	list[prev].nxt = tmp;
    }
    assert(sz(list) == M * 2 + 1);
    int u = 0;
    vector<bool> vis(N, 0);
    vector<int> res(N, -1);
    for (int i = 0; i < M * 2; i++) {
    	int p = list[u].pos;
    	if (!vis[p]) {
    		vis[p] = 1;
    		for (int j = 0; j < sz(adj[p]); j++) {
    			if (adj[p][j] == list[list[u].nxt].pos) res[p] = j;
    		}
    	}
    	u = list[u].nxt;
    }
    cout << (S + 1) << " ";
    for (int i = 0; i < sz(res); i++) {
    	cout << (adj[i][res[i]] + 1) << (i == sz(res) - 1 ? "\n" : " ");
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