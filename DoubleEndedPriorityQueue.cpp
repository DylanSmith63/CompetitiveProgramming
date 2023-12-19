template<class T>
struct DoubleEndedPriorityQueue {
    priority_queue<T> mnPQ, mxPQ, rmnPQ, rmxPQ;
    void push(T x) { mnPQ.push(-x); mxPQ.push(x); }
    void clear() {
        while (!rmnPQ.empty() && mnPQ.top() == rmnPQ.top()) mnPQ.pop(), rmnPQ.pop();
        while (!rmxPQ.empty() && mxPQ.top() == rmxPQ.top()) mxPQ.pop(), rmxPQ.pop();
    }
    T min() { clear(); return -mnPQ.top(); }
    T max() { clear(); return mxPQ.top(); }
    T popMin() { clear(); T x = min(); mnPQ.pop(); rmxPQ.push(x); return x; }
    T popMax() { clear(); T x = max(); mxPQ.pop(); rmnPQ.push(-x); return x; }
};