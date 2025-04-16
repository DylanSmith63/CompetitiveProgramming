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

bool check(vector<int> x, vector<int> lengths) {
	vector<int> p;
	int cur = 0;
	for (int i : lengths) {
		for (int j = 0; j < i; j++) {
			p.pb(cur++);
		}
		cur++;
	}
	assert(sz(p) == sz(x));
	for (int i = 0; i < sz(p); i++) {
		if (x[i] < p[i]) return 0;
	}
	return 1;
}

void solve() {
    int N; cin >> N;
    vector<int> x(N);
    for (int i = 0; i < N; i++) cin >> x[i];
    if (N % 2 == 1) {
    	cout << "NO\n";
    	return;
    }
    bool res;
    if (N % 4 == 2) {
    	res = check(x, {1, N / 2, N / 2 - 1});
    } else {
    	res = check(x, {1, N / 2 - 1, N / 2 - 1, 1});
    }
    if (res) cout << "YES\n";
    else cout << "NO\n";
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