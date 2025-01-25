#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

int mod = 998244353;

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

vector<int> factArr = {1}, factInvArr = {1};
int fact(int n) {
    while (sz(factArr) <= n)
        factArr.pb((int)((ll)factArr[sz(factArr) - 1] * sz(factArr) % mod));
    return factArr[n];
}

int factInv(int n) {
    fact(n);
    while (sz(factInvArr) <= n)
        factInvArr.pb(mInv(factArr[sz(factInvArr)]));
    return factInvArr[n];
}

int choose(int n, int k) {
	if (k < 0 || k > n) return 0;
    return (int)((ll)fact(n) * factInv(k) % mod * factInv(n - k) % mod);
}

int catalan(int n, int k = 0) {
    return (ll)choose(2 * n + k, n) * (k + 1) % mod * mInv(n + k + 1) % mod;
}

struct node {
    int cnt, weight, left, right;
    int val, rev;
    int cover, coverSum;
    node(int l, int r) : cnt(1), weight(rng()), left(-1), right(-1), val(l), rev(0), cover(r - l + 1), coverSum(r - l + 1) {}
};

vector<node> tree;

int cnt(int i) { return i == -1 ? 0 : tree[i].cnt; }
int cover(int i) { return i == -1 ? 0 : tree[i].cover; }
int coverSum(int i) { return i == -1 ? 0 : tree[i].coverSum; }

void push(int i) {
    if (tree[i].rev) {
        swap(tree[i].left, tree[i].right);
        if (tree[i].left >= 0) tree[tree[i].left].rev = !tree[tree[i].left].rev;
        if (tree[i].right >= 0) tree[tree[i].right].rev = !tree[tree[i].right].rev;
        tree[i].rev = 0;
    }
}

void updCnt(int i) { 
    tree[i].cnt = 1 + cnt(tree[i].left) + cnt(tree[i].right);
    tree[i].coverSum = cover(i) + coverSum(tree[i].left) + coverSum(tree[i].right);
}
 
void split(int n, int k, int &l, int &r) {
    if (n == -1) { l = r = -1; return; }
    push(n);
    if (cnt(tree[n].left) < k)
        split(tree[n].right, k - cnt(tree[n].left) - 1, tree[n].right, r), l = n;
    else split(tree[n].left, k, l, tree[n].left), r = n;
    updCnt(n);
}

void merge(int l, int r, int &n) {
    if (l == -1 || r == -1) { n = l == -1 ? r : l; return; }
    push(l); push(r);
    if (tree[l].weight > tree[r].weight)
        merge(tree[l].right, r, tree[l].right), n = l;
    else merge(l, tree[r].left, tree[r].left), n = r;
    updCnt(n);
}

void splitVal(int n, int k, int &l, int &r) {
    if (n == -1) { l = r = -1; return; }
    push(n);
    if (tree[n].val <= k)
        splitVal(tree[n].right, k, tree[n].right, r), l = n;
    else splitVal(tree[n].left, k, l, tree[n].left), r = n;
    updCnt(n);
}

void inOrder(int n, vector<int> &v) {
    if (n == -1) return;
    push(n);
    inOrder(tree[n].left, v);
    v.pb(tree[n].val);
    inOrder(tree[n].right, v);
    updCnt(n);
}

void solve() {
    int N; cin >> N;
    vector<int> v(N + 1, 0);
    vector<pair<int, int>> ranges;
    v[0] = N;
    ranges.pb({0, N * 2 + 1});
    ll ways = catalan(N);
    vector<ll> res = {ways};
    vector<int> par(N + 1, -1);
    vector<int> trees(N + 1, -1);
    vector<map<int, int>> mpR(N * 2 + 3);
    vector<int> mpLast(N * 2 + 3, -1);
    auto insert = [&](int k, int l, int r) {
    	for (int i = l + 1; i < sz(mpR); i += i & -i) {
    		mpR[i][r] = k;
    		mpLast[i] = max(mpLast[i], r);
    	}
    };
    auto query = [&](int l, int r) {
    	for (int i = l + 1; i > 0; i -= i & -i) {
    		if (mpLast[i] > r) return mpR[i].lower_bound(r)->second;
    	}
    	return -1;
    };
   	insert(0, 0, N * 2 + 1);
    for (int i = 1; i <= N; i++) {
    	int l, r; cin >> l >> r;
    	ranges.pb({l, r});
    	par[i] = query(l, r);
    	assert(par[i] >= 0);
    	ways *= mInv(catalan(v[par[i]]));
    	ways %= mod;
    	int tmpL, tmpM, tmpR;
    	splitVal(trees[par[i]], l - 1, tmpL, tmpM);
    	splitVal(tmpM, r, tmpM, tmpR);
    	tree.pb(node(l, r));
    	merge(tmpL, sz(tree) - 1, tmpL);
    	merge(tmpL, tmpR, trees[par[i]]);
    	v[i] = (r - l - 1 - coverSum(tmpM)) / 2;
    	ways *= catalan(v[i]);
    	ways %= mod;
    	v[par[i]] -= v[i] + 1;
    	trees[i] = tmpM;
    	ways *= catalan(v[par[i]]);
    	ways %= mod;
    	res.pb(ways);
    	insert(i, l, r);
    }
    for (int i = 0; i < sz(res); i++) {
    	cout << res[i] << (i == sz(res) - 1 ? "\n" : " ");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }

    return 0;
}