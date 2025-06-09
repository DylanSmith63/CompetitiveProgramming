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
    vector<int> a(N), b(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    for (int i = 0; i < b.size(); i++) cin >> b[i];
    set<int> st;
    for (int i = N - 1; i >= 0; i--) {
    	if (i + 2 < N) {
    		st.insert(a[i + 2]);
    		st.insert(b[i + 2]);
    	}
    	if (a[i] == b[i] || st.count(a[i]) || st.count(b[i]) || i + 1 < N && (a[i + 1] == a[i] || b[i + 1] == b[i])) {
    		cout << (i + 1) << "\n";
    		return;
    	}
    }
    cout << 0 << "\n";
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