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
    sort(all(a));
    int j = 0;
    ll res = 0;
    for (int i = 0; i <= N; i++) {
        while (j < N && a[j] < i) j++;
        if (j < N) {
            res += (ll)i * (a[j] - i);
            a[j] = i;
            j++;
        } else {
            ll sum = 0, sumT = (ll)i * (i - 1) / 2;
            for (int i : a) sum += i;
            res += (ll)i * (sum - sumT);
            for (int k = i - 1; k > 0; k--) {
                res += (k + 1) + (ll)k * (k - 1);
            }
            break;
        }
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
