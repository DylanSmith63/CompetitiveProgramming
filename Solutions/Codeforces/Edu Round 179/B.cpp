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
    int N, Q; cin >> N >> Q;
    vector<int> fib(N);
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < N; i++) fib[i] = fib[i - 2] + fib[i - 1];
    int len1 = fib[N - 1] + fib[N - 2], len2 = fib[N - 1];
	string res = "";
	for (int q = 0; q < Q; q++) {
		int x, y, z; cin >> x >> y >> z;
		vector<int> v = {x, y, z};
		sort(all(v));
		if (v[0] >= len2 && v[2] >= len1) {
			res += "1";
		} else {
			res += "0";
		}
	}
	cout << res << "\n";
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