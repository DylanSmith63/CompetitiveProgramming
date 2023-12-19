template<class T>
struct PriorityQueue {
    vector<T> v;
    PriorityQueue() { v = vector<T>(1); }
    void push(T x) {
        v.pb(x); int n = sz(v) - 1;
        while (n > 1 && v[n >> 1] < v[n]) swap(v[n >> 1], v[n]), n >>= 1;
    }
    bool empty() { return sz(v) == 1; }
    T top() { return v[1]; }
    T pop() {
        int x = top(); swap(v[1], v[sz(v) - 1]); v.erase(v.end() - 1); int n = 1;
        while (n * 2 + 1 < sz(v) && max(v[n * 2], v[n * 2 + 1]) > v[n]) {
            if (v[n * 2] > v[n * 2 + 1]) { swap(v[n], v[n * 2]); n *= 2; }
            else { swap(v[n], v[n * 2 + 1]); n = n * 2 + 1; } }
        if (n * 2 < sz(v) && v[n * 2] > v[n]) { swap(v[n], v[n * 2]); n *= 2; }
        return x;
    }
};
#define priority_queue PriorityQueue