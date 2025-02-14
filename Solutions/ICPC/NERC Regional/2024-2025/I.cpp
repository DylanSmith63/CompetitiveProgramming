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
    vector<string> mat(N);
    for (int i = 0; i < N; i++) cin >> mat[i];
    vector<int> srt(N); iota(all(srt), 0);
    vector<int> res(M);
    for (int j = M * 2 - 1; j >= 0; j--) {
        vector<int> z, o;
        for (int i = 0; i < N; i++) {
            if (mat[srt[i]][j % M] == '0') z.pb(srt[i]);
            else o.pb(srt[i]);
        }
        for (int i = 0; i < sz(z); i++) srt[i] = z[i];
        for (int i = 0; i < sz(o); i++) srt[sz(z) + i] = o[i];
        if (j < M) res[j] = srt[N - 1];
    }
    for (int i = 0; i < sz(res); i++) {
        cout << (res[i] + 1) << (i == sz(res) - 1 ? "\n" : " ");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}