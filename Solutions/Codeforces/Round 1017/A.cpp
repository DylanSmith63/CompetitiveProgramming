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
    string line; getline(cin, line);
    stringstream ss(line);
    string s, res;
    while (ss >> s) res += s[0];
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    
    string line; getline(cin, line);
    int T = stoi(line);
    for (int t = 0; t < T; t++) {
        solve();
    }

    return 0;
}