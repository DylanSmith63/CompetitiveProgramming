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
 
bool check(vector<int> &a, ll K, int x) {
    vector<int> tree((sz(a) + 1) * 2, 0);
    int pre = sz(a) + 1;
    ll tot = 0;
    for (int i = 0; i < sz(a); i++) {
        for (int j = pre; j < sz(tree); j += j & -j) tree[j]++;
        pre += a[i] <= x ? 1 : -1;
        for (int j = pre - 1; j; j -= j & -j) tot += tree[j];
    }
    return tot >= K;
}
 
int search(vector<int> &a, ll K, int l, int r) {
    if (l > r) return -1;
    int mid = (l + r) / 2;
    if (check(a, K, mid)) {
        int m = search(a, K, l, mid - 1);
        if (m == -1) return mid;
        return m;
    }
    return search(a, K, mid + 1, r);
}
 
void solve() {
    int N; ll K; cin >> N >> K;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    cout << search(a, K, 1, 1000000000) << "\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
