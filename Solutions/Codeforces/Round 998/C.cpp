#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

void solve() {
  	int N, K; cin >> N >> K;
  	vector<int> a(N);
  	for (int i = 0; i < a.size(); i++) cin >> a[i];
  	map<int, int> freq;
  	for (int i : a) freq[i]++;
  	int res = 0;
  	for (auto &p : freq) {
  		if (p.first < K - p.first) {
  			res += min(p.second, freq[K - p.first]);
  		} else if (p.first == K - p.first) {
  			res += p.second / 2;
  		}
  	}
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