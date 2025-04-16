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
    vector<string> res(15);
    for (int i = 0; i < 25; i++) res[0] += ' ';
    for (int i = 1; i < 15; i++) res[i] = res[0];
    res[0][0] = res[14][0] = res[0][24] = res[14][24] = 'o';
    for (int i = 1; i < 14; i++) res[i][0] = res[i][24] = '|';
    for (int i = 1; i < 24; i++) res[0][i] = res[14][i] = '-';
    for (int i = 0; i < N; i++) {
        int r = -1, c = -1;
        while (r == -1 || res[r][c] != ' ' || res[r][c + 1] != ' ' || res[r][c + 2] != ' ') {
            r = rng() % 13 + 1;
            c = rng() % 21 + 1;
        }
        if (rng() % 2) {
            res[r][c] = res[r][c + 2] = '>';
            res[r][c + 1] = '<';
        } else {
            res[r][c] = res[r][c + 2] = '<';
            res[r][c + 1] = '>';
        }
    }
    for (string s : res) cout << s << "\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
