#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)
 
mt19937 rng;
 
void solve() {
	int N, M; cin >> N >> M;
	vector<pair<int, int>> birds;
	vector<int> cmp;
	for (int i = 0; i < N; i++) {
		int l, h; cin >> l >> h;
		birds.pb({l, h});
		cmp.pb(h);
	}
	vector<pair<int, int>> winds;
	for (int i = 0; i < M; i++) {
		int a, w; cin >> a >> w;
		winds.pb({a, w});
		cmp.pb(a);
	}
	sort(all(cmp));
	for (int i = 0; i < N; i++) {
		birds[i].second = lb(cmp, birds[i].second);
	}
	vector<ll> pre(sz(cmp), 0);
	for (int i = 0; i < M; i++) {
		winds[i].first = lb(cmp, winds[i].first);
		pre[winds[i].first] += winds[i].second;
	}
	for (int i = 1; i < sz(pre); i++) pre[i] += pre[i - 1];
	auto sumRange = [&](int l, int r) {
		if (r < 0) return 0LL;
		return pre[r] - (l == 0 ? 0LL : pre[l - 1]);
	};
	for (int i = 0; i < N; i++) {
		ll p = birds[i].first + sumRange(0, birds[i].second - 1) * 2;
		p += sumRange(birds[i].second, birds[i].second);
		cout << p << (i == N - 1 ? "\n" : " ");
	}
}
 
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
