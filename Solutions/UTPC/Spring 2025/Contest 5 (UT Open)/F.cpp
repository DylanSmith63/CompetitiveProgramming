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
 
int mod = 1e9+7;
 
ll exGCD(ll a, ll b, ll &x, ll &y) {
    if (a == 0) { x = 0; y = 1; return b; }
    ll g = exGCD(b % a, a, x, y);
    ll t = x; x = y - b / a * x; y = t;
    return g;
}
 
int mInv(int n) {
    ll x, y, g = exGCD(n, mod, x, y);
    if (g != 1) return 0;
    return (x % mod + mod) % mod;
}
 
vector<vector<ll>> matMult(vector<vector<ll>> &A, vector<vector<ll>> &B) {
    int N = sz(A), M = sz(B), K = sz(B[0]);
    vector<vector<__int128>> tmp(N, vector<__int128>(K, 0));
    vector<vector<ll>> C(N, vector<ll>(K, 0));
    for (int i = 0; i < N; i++) for (int j = 0; j < K; j++) {
        for (int k = 0; k < M; k++) tmp[i][j] += A[i][k] * B[k][j];
        C[i][j] = tmp[i][j] % mod; }
    return C;
}
 
vector<vector<ll>> matPow(vector<vector<ll>> mat, ll p) {
    vector<vector<ll>> res(sz(mat), vector<ll>(sz(mat), 0));
    for (int i = 0; i < sz(mat); i++) res[i][i] = 1;
    while (p > 0) {
        if (p & 1) res = matMult(res, mat);
        mat = matMult(mat, mat);
        p >>= 1; }
    return res;
}
 
void solve() {
    int N, M, K; cin >> N >> M >> K;
    vector<vector<pair<int, int>>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v, t; cin >> u >> v >> t;
        u--; v--;
        if (u != N - 1) adj[u].pb({v, t});
        if (v != N - 1) adj[v].pb({u, t});
    }
    vector<vector<ll>> mat(N * 5, vector<ll>(N * 5, 0));
    for (int u = 0; u < N; u++) {
        if (adj[u].empty()) {
            mat[u * 5][u * 5] = 1;
            continue;
        }
        vector<vector<int>> group(5);
        for (auto &p : adj[u]) {
            int v = p.first, t = p.second;
            group[t - 1].pb(v);
        }
        int sum = 0;
        for (int t = 4; t >= 0; t--) {
            if (t + 1 < 5 && sum) {
                mat[u * 5 + t][u * 5 + t + 1] = (ll)sum * mInv(sum + sz(group[t])) % mod;
            }
            sum += sz(group[t]);
            for (int v : group[t]) {
                mat[u * 5 + t][v * 5] += mInv(sum);
                mat[u * 5 + t][v * 5] %= mod;
            }
        }
    }
    vector<vector<ll>> v(1, vector<ll>(N * 5, 0));
    v[0][0] = 1;
    mat = matPow(mat, K);
    v = matMult(v, mat);
    cout << v[0][(N - 1) * 5] << "\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
