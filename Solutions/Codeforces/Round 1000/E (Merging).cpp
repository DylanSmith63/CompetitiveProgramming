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
    vector<int> cnt(N, 0);
    vector<ll> sum(N, 0);
    vector<vector<int>> distFreq(N);
    ll res = 0;
    for (int u : srt) {
    	for (int v : adj[u]) {
    		if (sz(distFreq[u]) < sz(distFreq[v])) {
    			swap(distFreq[u], distFreq[v]);
    			swap(cnt[u], cnt[v]);
    			swap(sum[u], sum[v]);
    		}
    		int curCnt = 0;
    		ll curSum = 0;
    		for (int i = 0; i < sz(distFreq[v]); i++) {
    			curCnt += distFreq[u][sz(distFreq[u]) - 1 - i];
    			curSum += (ll)distFreq[u][sz(distFreq[u]) - 1 - i] * (depth[u] + 1 + i);
    			int curCnt2 = cnt[u] - curCnt;
    			ll curSum2 = sum[u] - curSum;
    			int k = distFreq[v][sz(distFreq[v]) - 1 - i];
    			res -= (ll)k * curCnt * (1 + i);
    			res += (ll)k * (curSum - (ll)curCnt * depth[u]);
    			res -= (ll)k * (curSum2 - (ll)curCnt2 * depth[u]);
    			res += (ll)k * curCnt2 * (1 + i);
    		}
    		res += (ll)cnt[u] * (sum[v] - (ll)cnt[v] * depth[u]) + (sum[u] - (ll)cnt[u] * depth[u]) * cnt[v];
    		res -= (ll)cnt[u] * cnt[v];
    		for (int i = 0; i < sz(distFreq[v]); i++) {
    			distFreq[u][sz(distFreq[u]) - 1 - i] += distFreq[v][sz(distFreq[v]) - 1 - i];
    		}
    		cnt[u] += cnt[v];
    		sum[u] += sum[v];
    	}
    	cnt[u]++;
    	sum[u] += depth[u];
    	distFreq[u].pb(1);
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