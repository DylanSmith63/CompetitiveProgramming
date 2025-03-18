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

// kactl lazy seg tree
const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

void solve() {
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    vector<int> left, right;
	int mn = INT_MAX;
    for (int i = 0; i < N; i++) {
    	if (a[i] < mn) {
    		left.pb(i);
    		mn = a[i];
    	}
    }
    int mx = INT_MIN;
    for (int i = N - 1; i >= 0; i--) {
    	if (a[i] > mx) {
    		right.pb(i);
    		mx = a[i];
    	}
    }
    reverse(all(right));
    vector<int> leftVals, rightVals;
    for (int i : left) leftVals.pb(-a[i]);
    for (int i : right) rightVals.pb(-a[i]);
    vector<vector<pair<pair<int, int>, int>>> change(N + 1);
    for (int i = 0; i < N; i++) {
    	int l1 = lower_bound(all(leftVals), -a[i]) - leftVals.begin();
    	if (left[l1] != i && -leftVals[l1] == a[i]) l1++;
    	int r1 = lower_bound(all(left), i + 1) - left.begin() - 1;
    	int l2 = lower_bound(all(right), i) - right.begin();
    	int r2 = lower_bound(all(rightVals), -a[i] + 1) - rightVals.begin() - 1;
    	if (right[r2] != i && -rightVals[r2] == a[i]) r2--;
    	if (l1 <= r1 && l2 <= r2) {
    		change[l1].pb({{l2, r2}, 1});
    		change[r1 + 1].pb({{l2, r2}, -1});
    	}
    }
    Node n(0, N + 1);
    n.set(0, N, 0);
    int res = 1;
    for (int i = 0; i < sz(change); i++) {
    	for (auto &p : change[i]) {
    		n.add(p.first.first, p.first.second + 1, p.second);
    	}
    	res = max(res, n.query(0, N));
    }
    cout << res << "\n";
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