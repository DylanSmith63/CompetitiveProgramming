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
    vector<int> a(N), b(M);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    for (int i = 0; i < b.size(); i++) cin >> b[i];
    sort(all(a));
	sort(all(b));
	vector<ll> pA = {0}, pB = {0};
	for (int i = 0; i < N - 1 - i; i++) pA.pb(a[N - 1 - i] - a[i]);
	for (int i = 0; i < M - 1 - i; i++) pB.pb(b[M - 1 - i] - b[i]);
	for (int i = 1; i < sz(pA); i++) pA[i] += pA[i - 1];
	for (int i = 1; i < sz(pB); i++) pB[i] += pB[i - 1];
	auto f = [&](int x, int y) {
		return pA[x] + pB[y];
	};
	vector<ll> res;
	for (int k = 1; k <= N; k++) {
		int l = max(0, 2 * k - M), r = min(k, N - k);
		if (l > r) break;
		while (l < r) {
			int m = (l + r) / 2;
			if (f(m, k - m) > f(m + 1, k - (m + 1))) r = m;
			else l = m + 1;
		}
		res.pb(f(l, k - l));
	}
	cout << sz(res) << "\n";
	for (int i = 0; i < sz(res); i++) {
		cout << res[i] << (i == sz(res) - 1 ? "\n" : " ");
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