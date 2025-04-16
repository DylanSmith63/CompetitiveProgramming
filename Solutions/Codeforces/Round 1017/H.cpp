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

vector<vector<int>> pos;
void solve() {
	int N, Q; cin >> N >> Q;
	vector<int> a(N);
	for (int i = 0; i < a.size(); i++) cin >> a[i];
	vector<vector<vector<int>>> queries(N);
	vector<int> prev(Q);
	for (int q = 0; q < Q; q++) {
		int k, l, r; cin >> k >> l >> r; l--; r--;
		queries[l].pb({k, r, q});
		prev[q] = l;
	}
	vector<ll> res(Q, 0);
	for (int i = N - 1; i >= 0; i--) {
		pos[a[i]].pb(i);
	}

	auto getDivisors = [&](int n) {
		vector<int> res;
		for (int i = 1; i * i <= n; i++) {
			if (n % i == 0) {
				res.pb(i);
				if (i != n / i) res.pb(n / i);
			}
		}
		return res;
	};

	for (int i = 0; i < N; i++) {
		while (!queries[i].empty()) {
			auto q = queries[i].back(); queries[i].pop_back();
			int mn = N;
			for (int k : getDivisors(q[0])) {
				if (!pos[k].empty() && pos[k].back() < mn) {
					mn = pos[k].back();
				}
			}
			if (mn > q[1]) {
				res[q[2]] += (ll)(q[1] - prev[q[2]] + 1) * q[0];
				continue;
			}
			res[q[2]] += (ll)q[0] * (mn - prev[q[2]]);
			prev[q[2]] = mn;
			queries[mn].pb({q[0] / a[mn], q[1], q[2]});
		}
		pos[a[i]].pop_back();
	}
	for (ll i : res) cout << i << "\n";
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    pos = vector<vector<int>>(100001);
    int T; cin >> T;
    for (int t = 0; t < T; t++) solve();

    return 0;
}