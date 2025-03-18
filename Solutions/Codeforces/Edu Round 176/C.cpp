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
    int N, M; cin >> N >> M;
    vector<int> a(M);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    for (int &i : a) i = min(i, N - 1);
    sort(all(a));
	int j = M;
	ll sum = 0, res = 0;
	for (int i = 0; i < M; i++) {
		while (j - 1 >= 0 && a[j - 1] + a[i] >= N) {
			j--;
			sum += a[j];
		}
		res += (ll)(a[i] - N + 1) * (M - j) + sum;
		if (j <= i) res -= a[i] - N + a[i] + 1;
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