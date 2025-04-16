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
	vector<int> a(N);
	for (int i = 0; i < a.size(); i++) cin >> a[i];
	vector<int> cmp;
	for (int i : a) cmp.pb(i);
	sort(all(cmp));
	for (int i = 0; i < N; i++) a[i] = lb(cmp, a[i]);
	vector<int> tree(N + 1, 0);
	ll res = 0;
	for (int i = N - 1; i >= 0; i--) {
		for (int j = a[i]; j > 0; j -= j & -j) res += tree[j];
		for (int j = a[i] + 1; j <= N; j += j & -j) tree[j]++;
	}
	cout << (1 - res % 2) << "\n";
}
 
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
