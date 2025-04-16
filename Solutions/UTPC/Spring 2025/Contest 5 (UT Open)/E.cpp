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
 
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; } // + => p on right
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    bool half() const { return y < 0 || (y == 0 && x < 0); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};
 
typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
    if (sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<P> h(sz(pts)+1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(all(pts)))
        for (P p : pts) {
            while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
 
template<class P>
double lineDist(const P& a, const P& b, const P& p) {
    return (double)(b-a).cross(p-a)/(b-a).dist();
}
 
void solve() {
    int N, Q; cin >> N >> Q;
    vector<P> points;
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        points.pb(P{x, y});
    }
    vector<P> hull = convexHull(points);
    int bl = 0;
    for (int i = 0; i < sz(hull); i++) {
        if (hull[i].y < hull[bl].y || hull[i].y == hull[bl].y && hull[i].x < hull[bl].x) bl = i;
    }
    vector<pair<double, vector<int>>> srt;
    for (int d = 0; d < sz(hull); d++) {
        P v = hull[(d + 1) % sz(hull)] - hull[d];
        srt.pb({atan2(v.y, v.x), {0, (d + 1) % sz(hull)}});
    }
    for (int q = 0; q < Q; q++) {
        int a, b, c; cin >> a >> b >> c;
        srt.pb({atan2(a, -b), {1, q, a, b, c}});
        srt.pb({atan2(-a, b), {1, q, a, b, c}});
    }
    for (auto &p : srt) if (p.first < 0) p.first += acos(-1) * 2;
    sort(all(srt));
    P curPoint = hull[bl];
    vector<double> res(Q, 0);
    for (auto &p : srt) {
        auto event = p.second;
        int type = event[0];
        if (type == 0) {
            curPoint = hull[event[1]];
        } else {
            ll a = event[2], b = event[3], c = event[4];
            Point<double> p1, p2;
            if (b == 0) {
                p1 = Point<double>{-(double)c / a, 1.0};
                p2 = Point<double>{-(double)c / a, 2.0};
            } else {
                p1 = Point<double>{1.0, (double)(-c - a) / b};
                p2 = Point<double>{2.0, (double)(-c - 2 * a) / b};
            }
            Point<double> p3 = Point<double>{(double)curPoint.x, (double)curPoint.y};
            res[event[1]] = max(res[event[1]], abs(lineDist(p1, p2, p3)));
        }
    }
    for (double d : res) cout << setprecision(20) << d << "\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
 
    solve();
 
    return 0;
}
