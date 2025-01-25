#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

void solve() {
    int N, M; cin >> N >> M;
    vector<vector<int>> mat(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < M; j++) {
    		cin >> mat[i][j];
    	}
    }
    for (int i = 0; i < N; i++) {
    	for (int j = 1; j < M; j++) {
    		if (mat[i][j] % N != mat[i][0] % N) {
    			cout << "-1" << "\n";
    			return;
    		}
    	}
    }
    vector<int> res(N);
    for (int i = 0; i < N; i++) {
    	res[mat[i][0] % N] = i;
    }
    for (int i = 0; i < sz(res); i++) {
    	cout << (res[i] + 1) << (i == sz(res) - 1 ? "\n" : " ");
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