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
    int Q; cin >> Q;
    vector<int> a(Q * 2);
    int l = Q, r = Q - 1;
    ll cur = 0, sum = 0;
    auto addRight = [&](int k) {
    	a[++r] = k;
		sum += k;
		cur += (ll)k * (r - l + 1);
    };
    auto addLeft = [&](int k) {
    	a[--l] = k;
		sum += k;
		cur += sum;
    };
    auto remRight = [&]() {
    	int k = a[r--];
    	cur -= (ll)k * (r - l + 2);
    	sum -= k;
    	return k;
    };
    auto remLeft = [&]() {
    	int k = a[l++];
    	cur -= sum;
    	sum -= k;
    	return k;
    };
    bool rev = 0;
    for (int q = 0; q < Q; q++) {
    	int type; cin >> type;
    	if (type == 1) {
    		if (rev) {
    			int k = remLeft();
    			addRight(k);
    		} else {
    			int k = remRight();
    			addLeft(k);
    		}
    	} else if (type == 2) {
    		rev = !rev;
    	} else {
    		int k; cin >> k;
    		if (rev) {
    			addLeft(k);
    		} else {
    			addRight(k);
    		}
    	}
    	ll res = rev ? (ll)sum * (r - l + 2) - cur : cur;
    	cout << res << "\n";
    }
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