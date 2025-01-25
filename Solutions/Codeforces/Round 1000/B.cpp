#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

void solve() {
    int N, L, R; cin >> N >> L >> R; L--; R--;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    vector<int> left, right, middle;
	for (int i = 0; i < N; i++) {
		if (i < L) left.pb(a[i]);
		else if (i <= R) middle.pb(a[i]);
		else right.pb(a[i]);
	}
	sort(all(left));
	sort(all(right));
	sort(all(middle));
	reverse(all(middle));
	ll minDif = 0, difLeft = 0, difRight = 0;
	for (int i = 0; i < sz(middle); i++) {
		difLeft -= middle[i];
		difRight -= middle[i];
		if (i < sz(left)) {
			difLeft += left[i];
			minDif = min(minDif, difLeft);
		}
		if (i < sz(right)) {
			difRight += right[i];
			minDif = min(minDif, difRight);
		}
	}
	ll res = minDif;
	for (int i = L; i <= R; i++) res += a[i];
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