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

struct segtree {
	bitset<1 << 21> tree;
	void update(int i) {
		i += 1 << 20;
		while (i) {
			tree[i] = !tree[i];
			i >>= 1;
		}
	}
	int query(int l, int r) {
		int res = 0;
		l += 1 << 20; r += 1 << 20;
		while (l <= r) {
			if (l % 2 == 1) {
				res ^= tree[l];
				l >>= 1;
				l++;
			} else {
				l >>= 1;
			}
			if (r % 2 == 0) {
				res ^= tree[r];
				r >>= 1;
				r--;
			} else {
				r >>= 1;
			}
		}
		return res;
	}
};

void solve() {
	int N, Q; cin >> N >> Q;
	vector<segtree> trees(20);
	set<int> st;
	int sum = 0;
	auto add = [&](int n) {
		sum ^= n;
		for (int i = 0; i < 20; i++)
			trees[i].update(n & ((1 << i + 1) - 1));
		st.insert(n);
	};
	auto rem = [&](int n) {
		sum ^= n;
		for (int i = 0; i < 20; i++)
			trees[i].update(n & ((1 << i + 1) - 1));
		st.erase(n);
	};
	auto query = [&](int t) {
		int res = sum;
		if (sz(st) % 2) res ^= t;
		for (int i = 0; i < 20; i++)
			if (trees[i].query(max(0, (1 << i + 1) - (t & ((1 << i + 1) - 1))), (1 << 20) - 1))
				res ^= 1 << i + 1;
		return res;
	};
	for (int i = 0; i < N; i++) {
		int n; cin >> n;
		add(n);
	}
	for (int q = 0; q < Q; q++) {
		int type; cin >> type;
		if (type == 1) {
			int x; cin >> x;
			if (st.count(x)) rem(x);
			else add(x);
		} else {
			int t; cin >> t;
			cout << query(t) << "\n";
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}