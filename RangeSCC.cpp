struct SCC {
	int N, M, time, nComps;
	vector<vector<pair<int, int>>> adj;
	vector<int> disc, low, comp;
	vector<int> tree; // Segment tree
	stack<int> st;
	void update(int i, int k) {
		int n = i + M;
		tree[n] = k;
		n >>= 1;
		while (n > 0)
			tree[n] = min(tree[n * 2], tree[n * 2 + 1]), n >>= 1;
	}
	int query(int l, int r) {
		l += M; r += M;
		int mn = N;
		while (l <= r) {
			if (l % 2 == 1) {
				mn = min(mn, tree[l]);
				l >>= 1;
				l++;
			} else l >>= 1;
			if (r % 2 == 0) {
				mn = min(mn, tree[r]);
				r >>= 1;
				r--;
			} else r >>= 1;
		}
		return mn;
	}
	void dfs(int u) {
		low[u] = disc[u] = time++;
		update(u, disc[u]);
		st.push(u);
		for (pair<int, int> p : adj[u]) {
			int v;
			while ((v = ~query(p.first, p.second)) >= 0) {
				dfs(v), low[u] = min(low[u], low[v]); // Tree edges
			}
			low[u] = min(low[u], ~v); // Back edges
		}
		if (low[u] == disc[u]) { // Fill component
			while (st.top() != u)
				comp[st.top()] = nComps, update(st.top(), N), st.pop();
			comp[u] = nComps; st.pop();
			update(u, N);
			nComps++;
		}
	}
	vector<int> find(vector<vector<pair<int, int>>> &adj2) {
		adj = adj2;
		N = sz(adj);
		M = 1; while (M < N) M <<= 1;
		tree = vector<int>(M * 2, N);
		disc = vector<int>(N);
		low = vector<int>(N);
		comp = vector<int>(N);
		time = 0; nComps = 0;
		for (int i = 0; i < N; i++) update(i, ~i);
		for (int i = 0; i < sz(adj); i++)
			if (query(i, i) < 0) dfs(i);
		return comp;
	}
};