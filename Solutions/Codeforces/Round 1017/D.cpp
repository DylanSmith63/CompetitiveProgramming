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

vector<int> getV(string s) {
	vector<int> v;
	for (int i = 0; i < sz(s); i++) {
		int j = i;
		while (j + 1 < sz(s) && s[j + 1] == s[j]) j++;
		v.pb(j - i + 1);
		i = j;
	}
	return v;
}

void solve() {
    string s, t; cin >> s >> t;
    if (s[0] != t[0]) {
    	cout << "NO\n";
    	return;
    }
    vector<int> v1 = getV(s), v2 = getV(t);
    if (sz(v1) != sz(v2)) {
    	cout << "NO\n";
    	return;
    }
    for (int i = 0; i < sz(v1); i++) {
    	if (v2[i] < v1[i] || v2[i] > v1[i] * 2) {
    		cout << "NO\n";
    		return;
    	}
    }
    cout << "YES\n";
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