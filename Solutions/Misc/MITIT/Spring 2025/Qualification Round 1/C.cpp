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
    string s; cin >> s;
    priority_queue<int> pq;
    for (int i = 1; i <= N * 2; i++) pq.push(-i);
    vector<pair<int, int>> res(N);
    for (int i = 0; i < N; i++) {
        int a = -pq.top(); pq.pop();
        int b = -pq.top(); pq.pop();
        if ((a + b) % 2 != (s[i] == 'E' ? 0 : 1)) {
            if (pq.empty()) {
                cout << "NO\n";
                return;
            }
            int c = -pq.top(); pq.pop();
            res[i] = {a, c};
            pq.push(-b);
        } else {
            res[i] = {a, b};
        }
    }
    cout << "YES\n";
    for (int i = 0; i < N; i++) {
        cout << res[i].first << " " << res[i].second << "\n";
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