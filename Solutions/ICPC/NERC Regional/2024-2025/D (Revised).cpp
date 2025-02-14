#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

int mod = 998244353;

struct Op {
    int x, l, r, k;
};

void solve() {
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    vector<int> last(30, -1);
    vector<Op> ops;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 30; j++) {
            if (a[i] & 1 << j) last[j] = i;
        }
        vector<pair<int, int>> srt;
        for (int j = 0; j < 30; j++) srt.pb({last[j], j});
        sort(all(srt));
        reverse(all(srt));
        int o = 0;
        if (a[i] == 0) {
            int l = last[srt[0].second] + 1, r = i;
            ops.pb({0, l, r, i + 1});
        }
        for (int j = 0; j < 30; j++) {
            if (last[srt[j].second] == -1) break;
            o = o | 1 << srt[j].second;
            if (j == 29 || last[srt[j].second] > last[srt[j + 1].second]) {
                int l = j == 29 ? 0 : last[srt[j + 1].second] + 1, r = last[srt[j].second];
                ops.pb({o, l, r, i + 1});
            }
        }
    }
    auto cmp = [&](Op a, Op b) {
        return (ll)a.x * 1000000 + a.r < (ll)b.x * 1000000 + b.r;
    };
    sort(all(ops), cmp);
    vector<int> tree(N + 2, 0);
    auto query2 = [&](int r) {
        int res = 0;
        for (int i = r + 1; i; i -= i & -i) {
            res += tree[i];
            if (res >= mod) res -= mod;
        }
        return res;
    };
    auto query = [&](int l, int r) {
        int res = query2(r) - (l == 0 ? 0 : query2(l - 1));
        if (res < 0) res += mod;
        return res;
    };
    auto update = [&](int j, int k) {
        for (int i = j + 1; i < sz(tree); i += i & -i) {
            tree[i] += k;
            if (tree[i] >= mod) tree[i] -= mod;
        }
    };
    update(0, 1);
    for (auto &op : ops) {
        update(op.k, query(op.l, op.r));
    }
    int res = query(N, N);
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}