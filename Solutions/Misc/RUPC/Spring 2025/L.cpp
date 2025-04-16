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

vector<vector<int>> getGroups(vector<int> a) {
	int N = sz(a);
	vector<vector<int>> groups;
	vector<bool> vis(N, 0);
	for (int i = 0; i < N; i++) {
		if (vis[i]) continue;
		int cur = i;
		vector<int> v;
		while (!vis[cur]) {
			vis[cur] = 1;
			v.pb(cur);
			cur = a[cur];
		}
		groups.pb(v);
	}
	vector<pair<int, int>> srt;
	for (int i = 0; i < sz(groups); i++) srt.pb({sz(groups[i]), i});
	sort(all(srt));
	vector<vector<int>> res;
	for (int i = 0; i < sz(srt); i++) res.pb(groups[srt[i].second]);
	return res;
}

void solve() {
    int N; cin >> N;
    vector<int> ba(N), ab(N);
    for (int i = 0; i < ba.size(); i++) cin >> ba[i], ba[i]--;
    for (int i = 0; i < ab.size(); i++) cin >> ab[i], ab[i]--;
    vector<vector<int>> groups1 = getGroups(ab), groups2 = getGroups(ba);
	if (sz(groups1) != sz(groups2)) {
		cout << "NO\n";
		return;
	}
	vector<int> a(N), b(N);
	for (int i = 0; i < sz(groups1); i++) {
		if (sz(groups1[i]) != sz(groups2[i])) {
			cout << "NO\n";
			return;
		}
		for (int j = 0; j < sz(groups1[i]); j++) {
			a[groups1[i][j]] = groups2[i][j];
			b[groups2[i][j]] = groups1[i][(j + 1) % sz(groups1[i])];
		}
	}
	for (int i = 0; i < N; i++) {
		assert(a[b[i]] == ba[i]);
		assert(b[a[i]] == ab[i]);
	}
	cout << "YES\n";
	for (int i = 0; i < sz(a); i++) {
		cout << (a[i] + 1) << (i == sz(a) - 1 ? "\n" : " ");
	}
	for (int i = 0; i < sz(b); i++) {
		cout << (b[i] + 1) << (i == sz(b) - 1 ? "\n" : " ");
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