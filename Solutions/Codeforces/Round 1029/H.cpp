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

struct state {
	int left, right, both, sum, cnt;
	state() {}
	state(int v) {
		left = right = both = max(0, v);
		cnt = 1;
		sum = v;
	}
};
state merge(state a, state b) {
	state res;
	res.cnt = a.cnt + b.cnt;
	res.sum = a.sum + b.sum;
	res.left = max(a.left, a.sum + b.left);
	res.right = max(a.right + b.sum, b.right);
	res.both = max(a.both, b.both);
	res.both = max(res.both, a.right + b.left);
	return res;
}

struct segtree {
	struct node {
		state s;
		int left, right;
	};
	int N;
	vector<node> tree;
	int construct(int l, int r) {
		if (l == r) {
			tree.pb({state(-1), 0, 0});
			return sz(tree) - 1;
		}
		int cur = sz(tree);
		tree.pb({state(0), 0, 0});
		int left = construct(l, (l + r) / 2);
		int right = construct((l + r) / 2 + 1, r); 
		tree[cur].left = left;
		tree[cur].right = right;
		tree[cur].s = merge(tree[tree[cur].left].s, tree[tree[cur].right].s);
		return cur;
	}
	segtree(int _N) : N(_N) {
		construct(0, N - 1);
	}
	void update(int P, int K, int i, int l, int r) {
		if (r < P || P < l) return;
		if (l == r) {
			tree[i].s = state(tree[i].s.sum + K);
			return;
		}
		update(P, K, tree[i].left, l, (l + r) / 2);
		update(P, K, tree[i].right, (l + r) / 2 + 1, r);
		tree[i].s = merge(tree[tree[i].left].s, tree[tree[i].right].s);
	}
	void update(int P, int K) {
		update(P, K, 0, 0, N - 1);
	}
	int query() {
		return tree[0].s.both;
	}
};

vector<int> solve2(int N, int Q, vector<int> a, vector<pair<int, int>> queries) {
	vector<vector<vector<int>>> changes(N);
	for (int i = 0; i < N; i++) {
		changes[a[i]].pb({0, i, 1});
	}
	for (int q = 0; q < Q; q++) {
		int i = queries[q].first, k = queries[q].second;
		changes[a[i]].pb({q, i, -1});
		a[i] = k;
		changes[a[i]].pb({q, i, 1});
	}
	segtree st(N);
	map<int, int> reset;
	vector<vector<pair<int, int>>> change(Q);
	for (int x = 0; x < N; x++) {
		for (int i = 0; i < sz(changes[x]); i++) {
			int q = changes[x][i][0], p = changes[x][i][1], k = changes[x][i][2];
			st.update(p, k * 2);
			reset[p] += k * 2;
			if (i == sz(changes[x]) - 1 || changes[x][i][0] != changes[x][i + 1][0]) {
				int mx = st.query() / 2;
				change[q].pb({x, mx});
			}
		}
		for (auto &p : reset) {
			st.update(p.first, -p.second);
		}
		reset.clear();
	}
	int M = 1; while (M < N) M <<= 1;
	vector<int> tree(M * 2, INT_MIN);
	auto update = [&](int i, int k) {
		i += M;
		tree[i] = k;
		i >>= 1;
		while (i) {
			tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
			i >>= 1;
		}
	};
	auto query = [&]() {
		return tree[1];
	};
	vector<int> res;
	for (int q = 0; q < Q; q++) {
		for (auto &p : change[q]) {
			int i = p.first, k = p.second;
			update(i, k);
		}
		res.pb(query());
	}
	return res;
}

void solve() {
	int N, Q; cin >> N >> Q;
	vector<int> a(N);
	for (int i = 0; i < a.size(); i++) cin >> a[i], a[i]--;
	vector<pair<int, int>> queries(Q);
	for (int q = 0; q < Q; q++) {
		int i, k; cin >> i >> k; i--; k--;
		queries[q] = {i, k};
	}
	vector<int> res = solve2(N, Q, a, queries);
	for (int i = 0; i < sz(res); i++) {
		cout << res[i] << (i == sz(res) - 1 ? "\n" : " ");
	}
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    int T; cin >> T;
    for (int t = 0; t < T; t++) solve();

    return 0;
}