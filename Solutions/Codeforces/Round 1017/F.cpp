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
    int N, M, K; cin >> N >> M >> K;
    vector<vector<int>> mat(N, vector<int>(M));
    if (N % K == 0 || M % K == 0) {
    	for (int i = 0; i < N; i++) {
    		for (int j = 0; j < M; j++) {
    			mat[i][j] = (i + j) % K;
    		}
    	}
    } else {
    	int k1 = 1;
    	for (int i = 1; i <= N; i++) {
    		if (K % i == 0 && N % i == 0) k1 = i;
    	}
    	int k2 = K / k1;
    	for (int i = 0; i < N; i += k1) {
    		for (int j = 0; j < M; j += k2) {
    			for (int x = 0; x < k1; x++) {
    				for (int y = 0; y < k2; y++) {
    					mat[i + x][j + y] = x * k2 + y;
    				}
    			}
    		}
    	}
    }
    for (int j = 0; j < N; j++) {
    	for (int i = 0; i < sz(mat[j]); i++) {
    		cout << (mat[j][i] + 1) << (i == sz(mat[j]) - 1 ? "\n" : " ");
    	}
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