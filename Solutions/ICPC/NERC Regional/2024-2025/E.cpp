#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

struct Segment {
    int l, r;
    double h;
};

struct Deque {
    vector<Segment> a;
    int l, r;
    Deque() {
        a = vector<Segment>(400000);
        l = r = 200000;
    }
    Segment front() { return a[l]; }
    Segment back() { return a[r - 1]; }
    void push_front(Segment s) { a[--l] = s; }
    void push_back(Segment s) { a[r++] = s; }
    void pop_front() { l++; }
    void pop_back() { r--; }
    bool empty() { return l >= r; }
};

void solve() {
    int N; cin >> N;
    vector<int> a(N), b(N - 1);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    for (int i = 0; i < b.size(); i++) cin >> b[i];
    auto getLeftPipe = [&](int i) {
        return i == 0 ? INT_MAX : b[i - 1];
    };
    auto getRightPipe = [&](int i) {
        return i == N - 1 ? INT_MAX : b[i];
    };
    Deque dq, leftDq;
    for (int i = 0; i < N; i++) {
        int j = i;
        while (j + 1 < N && a[j] == a[j + 1] && b[j] <= a[i]) j++;
        leftDq.push_back({i, j, (double)a[i]});
        i = j;
    }
    for (int i = N - 1; i >= 0; i--) {
        if (dq.empty()) {
            assert(!leftDq.empty());
            dq.push_front(leftDq.back());
            leftDq.pop_back();
        }
        assert(dq.back().r == i);
        if (i == 0) {
            cout << setprecision(20) << dq.front().h << "\n";
            return;
        }
        double extra = getLeftPipe(i);
        while (extra > 0.000000001) {
            Segment left = dq.front(); dq.pop_front();
            int hLim = min(getLeftPipe(left.l), getRightPipe(left.r));
            double maxAdd = extra / (left.r - left.l + 1);
            if ((hLim - left.h) > maxAdd) {
                dq.push_front({left.l, left.r, left.h + maxAdd});
                extra = 0;
            } else {
                if (getLeftPipe(left.l) < getRightPipe(left.r)) {
                    assert(!leftDq.empty());
                    Segment tmp = leftDq.back(); leftDq.pop_back();
                    dq.push_front({left.l, left.r, (double)getLeftPipe(left.l)});
                    dq.push_front(tmp);
                } else {
                    assert(!dq.empty());
                    Segment tmp = dq.front(); dq.pop_front();
                    dq.push_front({left.l, tmp.r, (double)getRightPipe(left.r)});
                }
                extra -= (hLim - left.h) * (left.r - left.l + 1);
            }
        }
        Segment right = dq.back(); dq.pop_back();
        if (right.l < right.r) {
            dq.push_back({right.l, i - 1, right.h});
        }
        b[i - 1] = INT_MAX;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}