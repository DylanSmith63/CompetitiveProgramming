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
    int N, X; cin >> N >> X;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    int l = N, r = -1;
    for (int i = 0; i < N; i++) {
    	if (a[i]) {
    		l = min(l, i);
    		r = max(r, i);
    	}
    }
    bool res = r == -1 || r - l + 1 <= X;
    cout << (res ? "YES" : "NO") << "\n";
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