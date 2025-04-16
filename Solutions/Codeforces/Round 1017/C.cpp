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
    vector<vector<int>> mat(N, vector<int>(N));
    vector<bool> vis(N * 2 + 1, 0);
    vector<int> res;
    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < N; j++) {
    		cin >> mat[i][j];
    		if (i == 0 || j == N - 1) res.pb(mat[i][j]);
    		vis[mat[i][j]] = 1;
    	}
    }
    for (int i = 1; i <= N * 2; i++) {
    	if (!vis[i]) {
    		reverse(all(res));
    		res.pb(i);
    		reverse(all(res));
    	}
    }
    for (int i = 0; i < sz(res); i++) {
    	cout << res[i] << (i == sz(res) - 1 ? "\n" : " ");
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