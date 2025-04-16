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
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    vector<int> tree(N + 1, 0);
    int cnt = 0;
    ll res = 0;
    for (int i : a) {
        res += (ll)cnt * i;
        for (int j = i; j; j -= j & -j) res -= (ll)tree[j] * i;
        for (int j = i; j <= sz(a); j += j & -j) tree[j]++;
        cnt++;
    }
    reverse(all(a));
    fill(all(tree), 0);
    for (int i : a) {
        for (int j = i; j; j -= j & -j) res += (ll)tree[j] * i;
        for (int j = i; j <= sz(a); j += j & -j) tree[j]++;
    }
    cout << res << "\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
