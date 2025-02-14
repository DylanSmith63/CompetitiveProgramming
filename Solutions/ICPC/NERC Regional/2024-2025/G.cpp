#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

void solve() {
    int n; cin >> n;
    auto query = [&](string s) {
        cout << "1 " << s << "\n";
        cout.flush();
        int k; cin >> k;
        return k;
    };
    int o = query("1"), zo = query("01"), oo = query("11");
    int res = zo + oo == o ? 0 : 1;
    cout << "0 1 " << res << "\n";
    cout.flush();
    int pass; cin >> pass;
    assert(pass == 1);
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