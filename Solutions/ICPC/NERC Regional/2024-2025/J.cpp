#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

void solve() {
    int N; cin >> N;
    ll cur = 0;
    for (int i = 0; i < N; i++) {
        string type; cin >> type;
        int n; cin >> n;
        if (type == "P") cur += n;
        else {
            if (cur < n) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            cur -= min(cur, (ll)n);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}