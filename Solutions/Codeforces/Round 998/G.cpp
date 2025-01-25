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
    vector<int> a(N), b(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i], a[i]--;
    for (int i = 0; i < b.size(); i++) cin >> b[i], b[i]--;
    vector<int> v(N);
	for (int i = 0; i < N; i++) v[i] = i;
    vector<int> pos(N);
	for (int i = 0; i < N; i++) pos[i] = i;
    auto op = [&](int i, int j) {
		assert(i != j);
		swap(a[i], b[j]);
		swap(a[j], b[i]);
		int a = v[i], b = v[j];
		swap(v[i], v[j]);
		swap(pos[a], pos[b]);
	};
    vector<pair<int, int>> srt;
	for (int i = 0; i < N; i++) {
		srt.pb({min(a[i], b[i]), i});
	}
	sort(all(srt));
	int cur = 0;
	for (int i = 0; i < N; i++) {
		int j = pos[srt[i].second];
		if (j != i) op(j, i);
	}
	int prev = -1;
	int numSwaps = 0;
	bool good = 0;
	for (int i = 0; i < N; i++) {
		if (i > 0) {
			if (a[i] < a[i - 1] || b[i] < b[i - 1]) {
				swap(a[i], b[i]);
				numSwaps++;
				if (a[i] < a[i - 1] || b[i] < b[i - 1]) {
					cout << "NO\n";
					return;
				}
			}
		}
		if (max(a[i], b[i]) == (i + 1) * 2 - 1) {
			int l = i - prev;
			if (l % 2 == 1) good = 1;
			prev = i;
		}
	}
	if (good || numSwaps % 2 == 0) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
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