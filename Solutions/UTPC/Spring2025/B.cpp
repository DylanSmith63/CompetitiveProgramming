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
    vector<string> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    auto cmp = [&](const string &a, const string &b) {
        return sz(a) < sz(b);
    };
    sort(all(a), cmp);
    for (int i = 1; i < N; i++) {
        if (a[i].substr(sz(a[i]) - sz(a[0])) != a[0]) {
            cout << "Not found\n";
            return;
        }
    }
    cout << a[0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}