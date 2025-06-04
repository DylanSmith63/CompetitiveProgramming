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
    int N, M; cin >> N >> M;
    vector<int> a(M);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    sort(all(a));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 6; j++) {
			if (j % 2 == 0) {
				if (i < N / 2) {
					cout << a[i];
				} else {
					cout << a[M - 1 - (i - N / 2)];
				}
			} else {
				if (i < N / 2) {
					cout << a[M - 1 - i];
				} else {
					cout << a[i - N / 2];
				}
			}
			cout << (j == 5 ? "\n" : " ");
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