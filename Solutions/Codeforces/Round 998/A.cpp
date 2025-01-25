#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

void solve() {
    int a1, a2, a4, a5; cin >> a1 >> a2 >> a4 >> a5;
    vector<int> ops = {a1 + a2, a5 - a4, a4 - a2};
    int res = 0;
    for (int a3 : ops) {
    	int cnt = 0;
    	if (a1 + a2 == a3) cnt++;
    	if (a2 + a3 == a4) cnt++;
    	if (a3 + a4 == a5) cnt++;
    	res = max(res, cnt);
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