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

struct SegTree {
	struct node {
		int sum = 0;
		int left = 0, right = 0;
	};
	vector<node> tree;
	int N, rt;
	SegTree(int _N) : N(_N), rt(0) {
		tree.pb({});
	}
	void push(int i) {
		if (!tree[i].left) {
			tree[i].left = sz(tree);
			tree.pb({});
			tree[i].right = sz(tree);
			tree.pb({});
		}
	}
	// returns new root
	int addRange(int L, int R, int K, int i, int l, int r) {
		if (r < L || R < l) return i;
		int nxt = sz(tree);
		tree.pb(tree[i]);
		if (L <= l && r <= R) {
			tree[nxt].sum += K;
			return nxt;
		}
		tree[nxt].left = addRange(L, R, K, tree[nxt].left, l, (l + r) / 2);
		tree[nxt].right = addRange(L, R, K, tree[nxt].right, (l + r) / 2 + 1, r);
		return nxt;
	}
	void addRange(int L, int R, int K) {
		rt = addRange(L, R, K, rt, 0, N - 1);
	}
	int queryPoint(int P, int i, int l, int r) {
		if (r < P || P < l) return 0;
		int res = tree[i].sum;
		if (l < r) {
			res += queryPoint(P, tree[i].left, l, (l + r) / 2);
			res += queryPoint(P, tree[i].right, (l + r) / 2 + 1, r);
		}
		return res;
	}
	int queryPoint(int P) {
		return queryPoint(P, rt, 0, N - 1);
	}
};

void solve() {
	int N; cin >> N;
	vector<int> a(N);
	for (int i = 0; i < a.size(); i++) cin >> a[i], a[i]--;
	vector<int> pos(N);
	for (int i = 0; i < N; i++) pos[a[i]] = i;
	set<int> up, down;
	for (int i = 0; i < N; i++) up.insert(i);
	vector<vector<int>> rects;
	for (int v = 0; v < N; v++) {
		int i = pos[v];
		up.erase(i);
		down.insert(i);
		int j = up.empty() || *prev(up.end()) < i ? N : *up.lower_bound(i);
		int x = up.empty() || *up.begin() > i ? -1 : *prev(up.lower_bound(i));
		if (j < N) {
			int k = down.empty() || *prev(down.end()) < j ? N : *down.lower_bound(j);
			rects.pb({x + 1, j - 1, j, k - 1});
		}
		if (x >= 0) {
			int y = down.empty() || *down.begin() > x ? -1 : *prev(down.lower_bound(x));
			rects.pb({y + 1, x, x + 1, j - 1});
		}
	}
	vector<vector<vector<int>>> changes(N);
	for (auto &r : rects) {
		changes[r[0]].pb({r[2], r[3], 1});
		if (r[1] + 1 < N) changes[r[1] + 1].pb({r[2], r[3], -1});
	}
	SegTree st(N);
	vector<int> rts(N);
	for (int i = 0; i < N; i++) {
		for (auto &p : changes[i]) {
			int l = p[0], r = p[1], k = p[2];
			st.addRange(l, r, k);
		}
		rts[i] = st.rt;
	}
	int Q; cin >> Q;
	for (int q = 0; q < Q; q++) {
		int l, r; cin >> l >> r; l--; r--;
		int res = st.queryPoint(r, rts[l], 0, N - 1);
		cout << (res ? "YES" : "NO") << "\n";
		if (q % 10 == 9) cout.flush();
	}
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}