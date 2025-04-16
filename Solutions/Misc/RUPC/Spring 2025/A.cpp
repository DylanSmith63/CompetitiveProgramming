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

void solve() {
	int N; cin >> N;
	vector<int> res;
	for (int i = 0; i < 1 << N; i++) {
		if (__builtin_popcount(i) % 2 == 0) res.pb(i);
	}
	cout << sz(res) << "\n";
	for (int i : res) {
		string s;
		for (int j = N - 1; j >= 0; j--) {
			if (i & 1 << j) s += '1';
			else s += '0';
		}
		cout << s << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}