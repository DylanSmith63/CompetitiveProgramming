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
	string res;
	string ops = "ACGT.";
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		if (i == 0) res = s;
		else {
			for (int i = 0; i < sz(s); i++) {
				if (s[i] == '.') continue;
				res[i] = s[i];
			}
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
