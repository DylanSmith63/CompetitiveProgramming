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

int mod = 1000000007;

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

vector<vector<vector<ll>>> mats;
void prec() {
	vector<vector<ll>> mat(7, vector<ll>(7, 0));
	for (int i = 0; i < 6; i++) mat[i][i + 1] = 1;
	mat[0][0] = 2;
	mat[1][0] = 2;
	mat[2][0] = 6;
	mat[3][0] = 1;
	mat[4][0] = 6;
	mat[5][0] = 2;
	mat[6][0] = 2;
	mats = vector<vector<vector<ll>>>(60);
	for (int i = 0; i < 60; i++) {
		mats[i] = mat;
		mat = matMult(mat, mat);
	}
}

ll part(ll n) {
	vector<vector<ll>> v(1, vector<ll>(7, 0));
	v[0][0] = 1;
	for (int j = 0; j < 60; j++) {
		if (n & 1LL << j) v = matMult(v, mats[j]);
	}
	return v[0][0];
}

void solve() {
	ll N; cin >> N;
	ll res = 0;
	for (ll i = 0; i < 4; i++) {
		for (ll j = max(i, N - 4); j < N; j++) {
			res += part(j - i);
			res %= mod;
		}
	}
	res *= 24;
	res %= mod;
	cout << res << "\n";
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    prec();
    int T; cin >> T;
    for (int t = 0; t < T; t++) solve();

    return 0;
}