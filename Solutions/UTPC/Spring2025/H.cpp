#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
typedef pair<int, int> pii;
typedef vector<int> vi;
 
mt19937 rng;
 
// kactl
vi num, st;
vector<vector<pii>> ed;
int Time;
vector<int> bridges;
 
template<class F>
int dfs(int at, int par, F& f) {
    int me = num[at] = ++Time, top = me;
    for (auto [y, e] : ed[at]) if (e != par) {
        if (num[y]) {
            top = min(top, num[y]);
            if (num[y] < me)
                st.push_back(e);
        } else {
            int si = sz(st);
            int up = dfs(y, e, f);
            top = min(top, up);
            if (up == me) {
                st.push_back(e);
                f(vi(st.begin() + si, st.end()));
                st.resize(si);
            }
            else if (up < me) st.push_back(e);
            else {
                bridges.pb(e);
            }
        }
    }
    return top;
}
 
template<class F>
void bicomps(F f) {
    num.assign(sz(ed), 0);
    rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
}
 
void solve() {
    int N, M; cin >> N >> M;
    vector<ll> ids;
    vector<vector<int>> adj(N);
    ed = vector<vector<pair<int, int>>>(N);
    for (int i = 0; i < M; i++) {
        ll id; int u, v; cin >> id >> u >> v;
        ids.pb(id);
        ed[u].pb({v, i});
        ed[v].pb({u, i});
        adj[u].pb(v);
        adj[v].pb(u);
    }
    bicomps([](const vi &x){});
    vector<ll> res;
    for (int i : bridges) res.pb(ids[i]);
    sort(all(res));
    if (res.empty()) {
        cout << -1 << "\n";
    } else {
        for (int i = 0; i < sz(res); i++) {
            cout << res[i] << (i == sz(res) - 1 ? "\n" : " ");
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
