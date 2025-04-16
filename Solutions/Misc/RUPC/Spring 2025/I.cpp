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
	ll a, b, n; cin >> a >> b >> n;
	if (n <= 2 * (b - 1) + a) {
		cout << "Alice\n";
		return;
	}
	if (min(2 * b, n - 2 * a + 1) <= (n - a + 1) / 2) {
		cout << "Bob\n";
		return;
	}
	cout << "Alice\n";
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