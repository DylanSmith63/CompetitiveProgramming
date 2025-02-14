#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int mod = 998244353;

vector<vector<pair<pair<int, int>, int>>> part(vector<int> a) {
    int N = sz(a);
    vector<vector<int>> right(N, vector<int>(30, N));
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < 30; j++) {
            if (a[i] & 1 << j) right[i][j] = i;
            else right[i][j] = (i == N - 1 ? N : right[i + 1][j]);
        }
    }
    vector<vector<pair<pair<int, int>, int>>> res(N);
    for (int i = 0; i < N; i++) {
        vector<pair<int, int>> srt;
        for (int j = 0; j < 30; j++) srt.pb({right[i][j], j});
        sort(all(srt));
        int o = 0;
        if (srt[0].first > i) res[i].pb({{i, srt[0].first - 1}, 0});
        for (int j = 0; j < 30; j++) {
            if (srt[j].first == N) break;
            o |= 1 << srt[j].second;
            if (j == 29 || srt[j].first < srt[j + 1].first) {
                int l = srt[j].first, r = j == 29 ? N - 1 : srt[j + 1].first - 1;
                res[i].pb({{l, r}, o});
            }
        }
    }
    return res;
}

void solve() {
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    vector<vector<pair<pair<int, int>, int>>> left, right;
    right = part(a);
    reverse(all(a));
    left = part(a);
    reverse(all(a));
    reverse(all(left));
    for (int i = 0; i < N; i++) {
        for (auto &p : left[i]) {
            int l = p.first.first, r = p.first.second;
            p.first.first = N - 1 - r;
            p.first.second = N - 1 - l;
        }
    }
    vector<int> cmp = {0};
    for (int i = 0; i < N; i++) {
        for (auto &p : right[i]) cmp.pb(p.second);
    }
    sort(all(cmp));
    for (int i = 0; i < N; i++) {
        for (auto &p : right[i]) p.second = (int)(lower_bound(cmp.begin(), cmp.end(), p.second) - cmp.begin());
        for (auto &p : left[i]) p.second = (int)(lower_bound(cmp.begin(), cmp.end(), p.second) - cmp.begin());
    }
    vector<int> mp(sz(cmp), 0);
    vector<vector<pair<int, int>>> change(N + 1);
    change[0].pb({0, 1});
    change[1].pb({0, mod - 1});
    vector<int> dp(N + 1, 0);
    dp[0] = 1;
    for (int i = 0; i <= N; i++) {
        for (auto &p : change[i]) {
            mp[p.first] += p.second;
            if (mp[p.first] >= mod) mp[p.first] -= mod;
        }
        vector<int> v = {0};
        if (i > 0) {
            for (int j = 0; j < sz(left[i - 1]); j++) {
                if (left[i - 1][j].second > 0) v.pb(left[i - 1][j].second);
            }
            for (int k : v) {
                dp[i] += mp[k];
                if (dp[i] >= mod) dp[i] -= mod;
            }
        }
        int j = 0, cur = 0;
        if (i < N) {
            for (auto &p : right[i]) {
                while (j < sz(v) && v[j] <= p.second) {
                    cur += mp[v[j]];
                    cur %= mod;
                    j++;
                }
                change[p.first.first + 1].pb({p.second, cur});
                if (p.first.second + 2 <= N) change[p.first.second + 2].pb({p.second, (mod - cur) % mod});
            }
        }
    }
    cout << dp[N] << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}