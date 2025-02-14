#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

int find(vector<int> &group, int i) {
    return group[i] == i ? i : group[i] = find(group, group[i]);
}

void solve() {
    int N, K, Q; cin >> N >> K >> Q;
    vector<string> mat(N);
    for (int i = 0; i < N; i++) cin >> mat[i];
    vector<bool> vis(K, 0);
    vector<int> group(N); iota(all(group), 0);
    vector<int> cnt(N, 1);
    int mxCnt = 1;
    for (int q = 0; q < Q; q++) {
        int type; cin >> type;
        if (type == 1) {
            int j; cin >> j; j--;
            if (!vis[j]) {
                vector<vector<int>> srt(10);
                for (int i = 0; i < N; i++) srt[mat[i][j] - 'a'].pb(i);
                for (int k = 0; k < 10; k++) {
                    for (int i = 1; i < sz(srt[k]); i++) {
                        int u = srt[k][i - 1], v = srt[k][i];
                        int g1 = find(group, u), g2 = find(group, v);
                        if (g1 != g2) {
                            group[g2] = g1;
                            cnt[g1] += cnt[g2];
                            mxCnt = max(mxCnt, cnt[g1]);
                        }
                    }
                }
                vis[j] = 1;
            }
        } else if (type == 2) {
            int i; cin >> i; i--;
            int g = find(group, i);
            cout << cnt[g] << "\n";
        } else {
            cout << mxCnt << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}