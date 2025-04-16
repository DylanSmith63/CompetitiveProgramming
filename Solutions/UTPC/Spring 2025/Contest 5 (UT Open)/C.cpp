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
 
struct SuffixAutomaton {
    struct Node {
        int len = 0, lnk = 0;
        int nxt[26];
    };
    string s;
    vector<Node> t; int last = 0;
    SuffixAutomaton(string s = "") {
        t.pb({0, -1, {}});
        for (char c : s) add(c);
    }
    void add(char c) { s += c; c -= 'a'; 
        int u = last; int v = last = sz(t);
        t.pb({t[u].len + 1, 0, {}});
        while (u >= 0 && !t[u].nxt[c])
            t[u].nxt[c] = v, u = t[u].lnk;
        if (u == -1) return;
        int q = t[u].nxt[c];
        if (t[u].len + 1 == t[q].len)
            { t[v].lnk = q; return; }
        int cpy = sz(t); t.pb(t[q]);
        t[cpy].len = t[u].len + 1;
        while (u >= 0 && t[u].nxt[c] == q)
            t[u].nxt[c] = cpy, u = t[u].lnk;
        t[v].lnk = t[q].lnk = cpy;
    }
};
 
struct Function {
    set<pair<int, int>> left, right;
    int x = INT_MAX; ll y = 0;
    void add(int p, int id) {
        if (p <= x) {
            left.insert({p, id});
            y += p;
        } else {
            right.insert({p, id});
            y += x;
        }
    }
    void rem(int p, int id) {
        if (left.count({p, id})) {
            left.erase({p, id});
            y -= p;
        } else {
            right.erase({p, id});
            y -= x;
        }
    }
    ll query(int p) {
        while (x > p) {
            if (!left.empty() && prev(left.end())->first >= p) {
                auto [k, id] = *prev(left.end());
                y -= (ll)(x - k) * sz(right);
                x = k;
                left.erase({k, id});
                right.insert({k, id});
            } else {
                y -= (ll)(x - p) * sz(right);
                x = p;
            }
        }
        return y;
    }
};
 
void solve() {
    int N, Q; cin >> N >> Q;
    string s; cin >> s;
    SuffixAutomaton sa(s);
    queue<int> q; q.push(0);
    vector<vector<int>> adj(sz(sa.t));
    for (int i = 1; i < sz(sa.t); i++) adj[sa.t[i].lnk].pb(i);
    vector<int> srt;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        srt.pb(u);
        for (int v : adj[u]) {
            q.push(v);
        }
    }
    reverse(all(srt));
    vector<set<int>> ends(sz(sa.t));
    vector<int> pos(N);
    int cur = 0;
    for (int i = 0; i < N; i++) {
        while (!sa.t[cur].nxt[s[i]-'a']) cur = sa.t[cur].lnk;
        cur = sa.t[cur].nxt[s[i]-'a'];
        pos[i] = cur;
        ends[cur].insert(i);
    }
    vector<priority_queue<pair<int, int>>> queries(sz(sa.t));
    for (int q = 0; q < Q; q++) {
        int l, r; cin >> l >> r; l--; r--;
        queries[pos[r]].push({r - l + 1, q});
    }
    vector<Function> funcs(sz(sa.t));
    vector<int> res(Q);
    for (int u : srt) {
        if (!ends[u].empty()) funcs[u].add(*ends[u].begin() + 1, *ends[u].begin());
        for (int v : adj[u]) {
            if (sz(ends[v]) > sz(ends[u])) {
                swap(ends[u], ends[v]);
                swap(funcs[u], funcs[v]);
            }
            set<pair<int, int>>().swap(funcs[v].left);
            set<pair<int, int>>().swap(funcs[v].right);
            for (int k : ends[v]) {
                int pre = ends[u].empty() || *ends[u].begin() > k ? -1 : *prev(ends[u].lower_bound(k));
                if (!ends[u].empty() && *prev(ends[u].end()) > k) {
                    int nxt = *ends[u].lower_bound(k);
                    funcs[u].rem(nxt - pre, nxt);
                    funcs[u].add(nxt - k, nxt);
                }
                ends[u].insert(k);
                funcs[u].add(k - pre, k);
            }
            set<int>().swap(ends[v]);
            if (sz(queries[v]) > sz(queries[u])) {
                swap(queries[v], queries[u]);
            }
            while (!queries[v].empty()) {
                auto p = queries[v].top(); queries[v].pop();
                queries[u].push(p);
            }
            priority_queue<pair<int, int>>().swap(queries[v]);
        }
        while (!queries[u].empty() && queries[u].top().first > sa.t[sa.t[u].lnk].len) {
            auto p = queries[u].top(); queries[u].pop();
            res[p.second] = funcs[u].query(p.first);
        }
    }
    for (int i : res) cout << i << "\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
