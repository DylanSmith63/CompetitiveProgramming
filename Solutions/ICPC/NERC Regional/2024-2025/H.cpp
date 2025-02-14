#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)
#define rep(i, a, b) for(int i = a; i < (b); ++i)

mt19937 rng;

// kactl

const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
    struct edge {
        int from, to, rev;
        ll cap, cost, flow;
    };
    int N;
    vector<vector<edge>> ed;
    vi seen;
    vector<ll> dist, pi;
    vector<edge*> par;

    MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

    void addEdge(int from, int to, ll cap, ll cost) {
        if (from == to) return;
        ed[from].push_back(edge{ from,to,sz(ed[to]),cap,cost,0 });
        ed[to].push_back(edge{ to,from,sz(ed[from])-1,0,-cost,0 });
    }

    void path(int s) {
        fill(all(seen), 0);
        fill(all(dist), INF);
        dist[s] = 0; ll di;

        __gnu_pbds::priority_queue<pair<ll, int>> q;
        vector<decltype(q)::point_iterator> its(N);
        q.push({ 0, s });

        while (!q.empty()) {
            s = q.top().second; q.pop();
            seen[s] = 1; di = dist[s] + pi[s];
            for (edge& e : ed[s]) if (!seen[e.to]) {
                ll val = di - pi[e.to] + e.cost;
                if (e.cap - e.flow > 0 && val < dist[e.to]) {
                    dist[e.to] = val;
                    par[e.to] = &e;
                    if (its[e.to] == q.end())
                        its[e.to] = q.push({ -dist[e.to], e.to });
                    else
                        q.modify(its[e.to], { -dist[e.to], e.to });
                }
            }
        }
        rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
    }

    pair<ll, ll> maxflow(int s, int t) {
        ll totflow = 0, totcost = 0;
        while (path(s), seen[t]) {
            ll fl = INF;
            for (edge* x = par[t]; x; x = par[x->from])
                fl = min(fl, x->cap - x->flow);

            totflow += fl;
            for (edge* x = par[t]; x; x = par[x->from]) {
                x->flow += fl;
                ed[x->to][x->rev].flow -= fl;
            }
        }
        rep(i,0,N) for(edge& e : ed[i]) totcost += e.cost * e.flow;
        return {totflow, totcost/2};
    }

    // If some costs can be negative, call this before maxflow:
    void setpi(int s) { // (otherwise, leave this out)
        fill(all(pi), INF); pi[s] = 0;
        int it = N, ch = 1; ll v;
        while (ch-- && it--)
            rep(i,0,N) if (pi[i] != INF)
              for (edge& e : ed[i]) if (e.cap)
                  if ((v = pi[i] + e.cost) < pi[e.to])
                      pi[e.to] = v, ch = 1;
        assert(it >= 0); // negative cost cycle
    }
};

void solve() {
    int N, M; cin >> N >> M;
    vector<int> p(M);
    for (int i = 0; i < p.size(); i++) cin >> p[i], p[i]--;
    vector<vector<int>> a(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> a[i][j];
        }
    }
    MCMF f(M + N * M + 4);
    f.addEdge(M + N * M + 2, 1, INF, 0);
    int tot = 0;
    auto addDemandEdge = [&](int u, int v, int lo, int hi, int cost) {
        assert(0 <= u && u < M + N * M + 2 && 0 <= v && v < M + N * M + 2);
        f.addEdge(0, 1 + v, lo, cost);
        f.addEdge(1 + u, M + N * M + 3, lo, 0);
        f.addEdge(1 + u, 1 + v, hi - lo, cost);
        tot += lo;
    };
    int curMx = 0;
    for (int i = 0; i < M; i++) {
        if (i == 0 || p[i] > p[i - 1]) curMx++;
        addDemandEdge(0, 1 + i, 1, 1, 0);
        for (int j = 0; j < N; j++) {
            addDemandEdge(1 + i, 1 + M + j * M + i, 0, 1, -a[j][i]);
            int nxt = i < M - 1 ? 1 + M + j * M + i + 1 : 1 + M + N * M;
            addDemandEdge(1 + M + j * M + i, nxt, j == p[i] ? curMx : 0, j < p[i] ? curMx - 1 : curMx, 0);
        }
    }
    f.setpi(0);
    auto flow = f.maxflow(0, M + N * M + 3);
    if (flow.first < tot) {
        cout << -1 << "\n";
        return;
    }
    vector<int> res(M, -1);
    for (int i = 0; i < M; i++) {
        for (auto e : f.ed[2 + i]) {
            if (e.flow == 1) res[i] = (e.to - i - M - 2) / M;
        }
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