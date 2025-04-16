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

ll intSqrt(ll N) {
    ll res = sqrt(N);
    if (res * res > N) res--;
    if ((res + 1) * (res + 1) <= N) res++;
    return res;
}

void solve() {
    int N; cin >> N;
    vector<string> res;
    for (int i = 0; i < 30; i++) {
    	if (N & 1 << i) {
    		if (i % 2 == 0) res.pb("A" + to_string(intSqrt(1 << i)));
    		else res.pb("B" + to_string(intSqrt(1 << i - 1)));
    	}
    }
    cout << sz(res);
    for (string s : res) cout << " " << s;
    cout << "\n";
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