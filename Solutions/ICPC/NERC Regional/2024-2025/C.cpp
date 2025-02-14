#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

void solve() {
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    sort(all(a));
    vector<int> pairs;
    for (int i = 0; i < N; i++) {
        int j = i;
        while (j + 1 < N && a[j + 1] == a[j]) j++;
        for (int k = 0; k < (j - i + 1) / 2; k++) pairs.pb(a[i]);
        i = j;
    }
    if (sz(pairs) < 4) {
        cout << "NO\n";
        return;
    }
    int x1 = pairs[0], x2 = pairs[sz(pairs) - 2], y1 = pairs[1], y2 = pairs[sz(pairs) - 1];
    cout << "YES\n";
    cout << x1 << " " << y1 << " " << x1 << " " << y2 << " " << x2 << " " << y1 << " " << x2 << " " << y2 << "\n";
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