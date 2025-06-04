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
    int N, Q; cin >> N >> Q;
    string s; cin >> s;
    vector<string> ops;
    for (int q = 0; q < Q; q++) {
    	string a, b; cin >> a >> b;
    	ops.pb(a + b);
    }
    set<int> ba, ca, bc, cb;
    for (int i = 0; i < Q; i++) {
    	if (ops[i][0] == 'a') continue;
    	if (ops[i][0] == ops[i][1]) continue;
    	if (ops[i] == "bc") bc.insert(i);
    	else if (ops[i] == "cb") cb.insert(i);
    	else if (ops[i] == "ba") ba.insert(i);
    	else ca.insert(i);
    }
    for (int i = 0; i < N; i++) {
    	if (s[i] == 'b') {
    		if (!ba.empty()) {
    			ba.erase(*ba.begin());
    			s[i] = 'a';
    		} else if (!bc.empty()) {
    			int t = *bc.begin();
    			if (!ca.empty() && t < *prev(ca.end())) {
    				bc.erase(t);
    				ca.erase(*ca.lower_bound(t));
    				s[i] = 'a';
    			}
    		}
    	} else if (s[i] == 'c') {
    		if (!ca.empty()) {
    			ca.erase(*ca.begin());
    			s[i] = 'a';
    		} else if (!cb.empty()) {
    			int t = *cb.begin();
    			if (!ba.empty() && t < *prev(ba.end())) {
    				cb.erase(t);
    				ba.erase(*ba.lower_bound(t));
    				s[i] = 'a';
    			} else {
    				t = *prev(cb.end());
    				cb.erase(t);
    				s[i] = 'b';
    			}
    		}
    	}
    }
    cout << s << "\n";
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